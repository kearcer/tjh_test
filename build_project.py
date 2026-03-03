#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
TJH Test Project Builder
A unified build system for managing and compiling C++ examples.
Supports category selection, version switching, and VSCode debugging.
"""

import os
import sys
import json
import subprocess
import re
import tkinter as tk
from tkinter import ttk, messagebox
from pathlib import Path
from typing import Dict, List, Optional, Tuple

class ProjectBuilder:
    def __init__(self, project_root: str):
        self.project_root = Path(project_root)
        self.config_path = self.project_root / "config.json"
        self.config = self._load_config()
        self.build_dir = self.project_root / self.config.get("build_dir", "build")
        self.output_dir = self.project_root / self.config.get("output_dir", "bin")
        
    def _load_config(self) -> dict:
        """Load configuration from config.json"""
        if not self.config_path.exists():
            raise FileNotFoundError(f"Configuration file not found: {self.config_path}")
        with open(self.config_path, 'r', encoding='utf-8') as f:
            return json.load(f)
    
    def _sanitize_target_name(self, name: str) -> str:
        """Convert name to valid CMake target name (ASCII only, no special chars)"""
        # Replace Chinese/special chars with underscores
        # Keep only alphanumeric and underscores
        sanitized = re.sub(r'[^a-zA-Z0-9_]', '_', name)
        # Remove leading digits
        if sanitized and sanitized[0].isdigit():
            sanitized = 'target_' + sanitized
        # Ensure not empty
        if not sanitized:
            sanitized = 'target'
        return sanitized
    
    def get_categories(self) -> Dict[str, dict]:
        """Get all available categories"""
        return self.config.get("categories", {})
    
    def get_versions(self, category: str) -> Dict[str, dict]:
        """Get all available versions for a category"""
        categories = self.get_categories()
        if category in categories:
            return categories[category].get("versions", {})
        return {}
    
    def get_examples(self, category: str) -> List[Tuple[str, str, List[str]]]:
        """
        Get all examples in a category.
        Returns list of tuples: (example_name, example_path, source_files)
        """
        categories = self.get_categories()
        if category not in categories:
            return []
        
        source_dir = self.project_root / categories[category].get("source_dir", "")
        if not source_dir.exists():
            return []
        
        examples = []
        
        # Check for subdirectories (each subdirectory is an example)
        for item in sorted(source_dir.iterdir()):
            if item.is_dir():
                # Find all cpp files in this directory
                cpp_files = list(item.glob("*.cpp")) + list(item.glob("**/*.cpp"))
                if cpp_files:
                    relative_path = item.relative_to(self.project_root)
                    examples.append((
                        item.name,
                        str(relative_path),
                        [str(f.relative_to(self.project_root)) for f in cpp_files]
                    ))
            elif item.suffix == ".cpp":
                # Single cpp file as an example
                relative_path = item.relative_to(self.project_root)
                examples.append((
                    item.stem,
                    str(relative_path.parent),
                    [str(relative_path)]
                ))
        
        return examples
    
    def generate_cmake(self, category: str, version: str, example_name: str, 
                       example_path: str, source_files: List[str]) -> str:
        """Generate CMakeLists.txt content for the selected example"""
        categories = self.get_categories()
        cat_config = categories.get(category, {})
        ver_config = cat_config.get("versions", {}).get(version, {})
        
        cmake_version = self.config.get("cmake_version", "3.10")
        cpp_standard = self.config.get("cpp_standard", 17)
        
        # Sanitize target name for CMake (no Chinese chars, no special chars)
        target_name = self._sanitize_target_name(example_name)
        
        # Normalize paths for CMake
        source_files_cmake = [f.replace("\\", "/") for f in source_files]
        
        cmake_content = f'''cmake_minimum_required(VERSION {cmake_version})
project({target_name})

set(CMAKE_CXX_STANDARD {cpp_standard})
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Build type
set(CMAKE_BUILD_TYPE Debug)

# Enable debug symbols (MSVC uses /Zi, GCC/Clang uses -g)
if(MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "${{CMAKE_CXX_FLAGS_DEBUG}} /Zi")
    set(CMAKE_C_FLAGS_DEBUG "${{CMAKE_C_FLAGS_DEBUG}} /Zi")
else()
    set(CMAKE_CXX_FLAGS_DEBUG "${{CMAKE_CXX_FLAGS_DEBUG}} -g")
    set(CMAKE_C_FLAGS_DEBUG "${{CMAKE_C_FLAGS_DEBUG}} -g")
endif()

'''
        
        # Add OpenCV if it's an opencv category
        if category == "opencv" and "opencv_dir" in ver_config:
            opencv_dir = ver_config["opencv_dir"].replace("\\", "/")
            cmake_content += f'''# OpenCV Configuration
set(OpenCV_DIR "{opencv_dir}")
find_package(OpenCV REQUIRED)
include_directories(${{OpenCV_INCLUDE_DIRS}})

'''
        
        # Add FFmpeg if it's a ffmpeg category
        if category == "ffmpeg":
            if ver_config.get("include_dirs"):
                for inc_dir in ver_config["include_dirs"]:
                    cmake_content += f'include_directories("{inc_dir.replace(chr(92), "/")}")\n'
            if ver_config.get("lib_dirs"):
                for lib_dir in ver_config["lib_dirs"]:
                    cmake_content += f'link_directories("{lib_dir.replace(chr(92), "/")}")\n'
            cmake_content += "\n"
        
        # Add custom include directories
        if ver_config.get("include_dirs"):
            for inc_dir in ver_config["include_dirs"]:
                cmake_content += f'include_directories("{inc_dir.replace(chr(92), "/")}")\n'
        
        # Add custom library directories
        if ver_config.get("lib_dirs"):
            for lib_dir in ver_config["lib_dirs"]:
                cmake_content += f'link_directories("{lib_dir.replace(chr(92), "/")}")\n'
        
        cmake_content += "\n"
        
        # Add source files with absolute paths from project root
        project_root_cmake = str(self.project_root).replace("\\", "/")
        sources_str = "\n    ".join(f'"{project_root_cmake}/{f}"' for f in source_files_cmake)
        cmake_content += f'''# Source files
set(SOURCES
    {sources_str}
)

# Executable
add_executable(${{PROJECT_NAME}} ${{SOURCES}})

# Compile options for debugging (MSVC vs GCC/Clang)
if(MSVC)
    target_compile_options(${{PROJECT_NAME}} PRIVATE /Zi /Od)
else()
    target_compile_options(${{PROJECT_NAME}} PRIVATE -g)
endif()

'''
        
        # Link libraries
        libs_to_link = []
        if category == "opencv":
            libs_to_link.append("${OpenCV_LIBS}")
        
        if ver_config.get("libs"):
            libs_to_link.extend(ver_config["libs"])
        
        if libs_to_link:
            cmake_content += f'''# Link libraries
target_link_libraries(${{PROJECT_NAME}} {" ".join(libs_to_link)})
'''
        
        return cmake_content
    
    def build_example(self, category: str, version: str, example_name: str,
                      example_path: str, source_files: List[str]) -> Tuple[bool, str, str]:
        """
        Build the selected example.
        Returns: (success, exe_path, message)
        """
        # Sanitize target name for exe lookup
        target_name = self._sanitize_target_name(example_name)
        
        # Create build directory for this example (use sanitized name for path)
        example_build_dir = self.build_dir / category / target_name
        example_build_dir.mkdir(parents=True, exist_ok=True)
        
        # Generate CMakeLists.txt
        cmake_content = self.generate_cmake(category, version, example_name, 
                                           example_path, source_files)
        cmake_file = example_build_dir / "CMakeLists.txt"
        with open(cmake_file, 'w', encoding='utf-8') as f:
            f.write(cmake_content)
        
        # Create symbolic link or copy mechanism for source access
        # CMake will use absolute paths, so no need for copying
        
        try:
            # Run CMake configure
            generator = self.config.get("global_settings", {}).get("generator", "Visual Studio 17 2022")
            cmake_flags = self.config.get("global_settings", {}).get("cmake_flags", "")
            
            # For Windows with Visual Studio
            configure_cmd = [
                "cmake",
                f"-G{generator}",
                "-A", "x64",
                cmake_flags,
                f"-S{self.project_root}",
                f"-B{example_build_dir}"
            ]
            
            # Write a temporary CMakeLists.txt in project root
            temp_cmake = self.project_root / "CMakeLists_temp.txt"
            with open(temp_cmake, 'w', encoding='utf-8') as f:
                f.write(cmake_content)
            
            # Actually, let's use the build directory approach
            configure_cmd = [
                "cmake",
                f"-G{generator}",
                "-A", "x64",
                f"-S{example_build_dir}",
                f"-B{example_build_dir}"
            ]
            
            result = subprocess.run(
                configure_cmd,
                cwd=str(example_build_dir),
                capture_output=True,
                text=True,
                encoding='utf-8',
                errors='replace'
            )
            
            if result.returncode != 0:
                return False, "", f"CMake configure failed:\n{result.stderr}\n{result.stdout}"
            
            # Run CMake build
            build_cmd = [
                "cmake",
                "--build", str(example_build_dir),
                "--config", "Debug"
            ]
            
            result = subprocess.run(
                build_cmd,
                cwd=str(example_build_dir),
                capture_output=True,
                text=True,
                encoding='utf-8',
                errors='replace'
            )
            
            if result.returncode != 0:
                return False, "", f"Build failed:\n{result.stderr}\n{result.stdout}"
            
            # Find the executable (use sanitized target name)
            exe_path = example_build_dir / "Debug" / f"{target_name}.exe"
            if not exe_path.exists():
                # Try other possible locations
                possible_paths = [
                    example_build_dir / f"{target_name}.exe",
                    example_build_dir / "Release" / f"{target_name}.exe",
                ]
                for p in possible_paths:
                    if p.exists():
                        exe_path = p
                        break
            
            if exe_path.exists():
                return True, str(exe_path), f"Build successful!\nTarget: {target_name}"
            else:
                return True, str(example_build_dir / "Debug" / f"{target_name}.exe"), \
                       f"Build completed but exe not found at expected location.\nCheck: {example_build_dir}"
            
        except Exception as e:
            return False, "", f"Build error: {str(e)}"
    
    def generate_vscode_launch(self, exe_path: str, example_name: str, working_dir: str) -> dict:
        """Generate VSCode launch configuration"""
        return {
            "name": f"Debug {example_name}",
            "type": "cppvsdbg",
            "request": "launch",
            "program": exe_path.replace("/", "\\"),
            "args": [],
            "stopAtEntry": False,
            "cwd": working_dir.replace("/", "\\"),
            "environment": [],
            "console": "integratedTerminal"
        }
    
    def update_vscode_launch(self, exe_path: str, example_name: str, working_dir: str):
        """Update .vscode/launch.json with the new configuration"""
        vscode_dir = self.project_root / ".vscode"
        vscode_dir.mkdir(exist_ok=True)
        launch_file = vscode_dir / "launch.json"
        
        new_config = self.generate_vscode_launch(exe_path, example_name, working_dir)
        
        if launch_file.exists():
            with open(launch_file, 'r', encoding='utf-8') as f:
                try:
                    launch_data = json.load(f)
                except json.JSONDecodeError:
                    launch_data = {"version": "0.2.0", "configurations": []}
        else:
            launch_data = {"version": "0.2.0", "configurations": []}
        
        # Remove existing config with same name
        launch_data["configurations"] = [
            c for c in launch_data["configurations"] 
            if c.get("name") != new_config["name"]
        ]
        
        # Add new config at the beginning
        launch_data["configurations"].insert(0, new_config)
        
        with open(launch_file, 'w', encoding='utf-8') as f:
            json.dump(launch_data, f, indent=4, ensure_ascii=False)
        
        return new_config["name"]


class BuilderGUI:
    def __init__(self, builder: ProjectBuilder):
        self.builder = builder
        self.root = tk.Tk()
        self.root.title("TJH Test Project Builder")
        self.root.geometry("800x600")
        self.root.resizable(True, True)
        
        self.selected_category = tk.StringVar()
        self.selected_version = tk.StringVar()
        self.selected_example = None
        
        self._create_widgets()
        
    def _create_widgets(self):
        # Main frame with padding
        main_frame = ttk.Frame(self.root, padding="10")
        main_frame.grid(row=0, column=0, sticky="nsew")
        
        self.root.columnconfigure(0, weight=1)
        self.root.rowconfigure(0, weight=1)
        main_frame.columnconfigure(1, weight=1)
        main_frame.rowconfigure(3, weight=1)
        
        # Category selection
        ttk.Label(main_frame, text="分类 (Category):", font=('Arial', 10, 'bold')).grid(
            row=0, column=0, sticky="w", pady=(0, 5))
        
        category_frame = ttk.Frame(main_frame)
        category_frame.grid(row=0, column=1, sticky="ew", pady=(0, 5))
        
        self.category_combo = ttk.Combobox(category_frame, textvariable=self.selected_category,
                                           state="readonly", width=40)
        categories = self.builder.get_categories()
        category_display = [f"{k} - {v.get('name', k)}" for k, v in categories.items()]
        self.category_combo['values'] = category_display
        self.category_combo.grid(row=0, column=0, sticky="w")
        self.category_combo.bind('<<ComboboxSelected>>', self._on_category_change)
        
        # Version selection
        ttk.Label(main_frame, text="版本 (Version):", font=('Arial', 10, 'bold')).grid(
            row=1, column=0, sticky="w", pady=(0, 5))
        
        version_frame = ttk.Frame(main_frame)
        version_frame.grid(row=1, column=1, sticky="ew", pady=(0, 5))
        
        self.version_combo = ttk.Combobox(version_frame, textvariable=self.selected_version,
                                          state="readonly", width=40)
        self.version_combo.grid(row=0, column=0, sticky="w")
        self.version_combo.bind('<<ComboboxSelected>>', self._on_version_change)
        
        # Description
        self.desc_label = ttk.Label(main_frame, text="", font=('Arial', 9), foreground='gray')
        self.desc_label.grid(row=2, column=0, columnspan=2, sticky="w", pady=(0, 10))
        
        # Examples list
        ttk.Label(main_frame, text="示例 (Examples):", font=('Arial', 10, 'bold')).grid(
            row=3, column=0, sticky="nw", pady=(0, 5))
        
        # Listbox with scrollbar
        list_frame = ttk.Frame(main_frame)
        list_frame.grid(row=3, column=1, sticky="nsew", pady=(0, 5))
        list_frame.columnconfigure(0, weight=1)
        list_frame.rowconfigure(0, weight=1)
        
        self.example_listbox = tk.Listbox(list_frame, font=('Consolas', 10), 
                                          selectmode=tk.SINGLE, height=15)
        self.example_listbox.grid(row=0, column=0, sticky="nsew")
        
        scrollbar = ttk.Scrollbar(list_frame, orient="vertical", 
                                  command=self.example_listbox.yview)
        scrollbar.grid(row=0, column=1, sticky="ns")
        self.example_listbox.configure(yscrollcommand=scrollbar.set)
        
        self.example_listbox.bind('<<ListboxSelect>>', self._on_example_select)
        self.example_listbox.bind('<Double-1>', self._on_build_click)
        
        # Source files display
        ttk.Label(main_frame, text="源文件:", font=('Arial', 9)).grid(
            row=4, column=0, sticky="nw", pady=(5, 0))
        
        self.source_text = tk.Text(main_frame, height=4, font=('Consolas', 9), 
                                   state='disabled', bg='#f5f5f5')
        self.source_text.grid(row=4, column=1, sticky="ew", pady=(5, 0))
        
        # Buttons
        button_frame = ttk.Frame(main_frame)
        button_frame.grid(row=5, column=0, columnspan=2, pady=(15, 0))
        
        self.build_btn = ttk.Button(button_frame, text="🔨 编译 (Build)", 
                                    command=self._on_build_click, width=20)
        self.build_btn.grid(row=0, column=0, padx=5)
        
        self.run_btn = ttk.Button(button_frame, text="▶ 运行 (Run)", 
                                  command=self._on_run_click, width=20)
        self.run_btn.grid(row=0, column=1, padx=5)
        
        self.debug_btn = ttk.Button(button_frame, text="🐛 调试 (Debug in VSCode)", 
                                    command=self._on_debug_click, width=20)
        self.debug_btn.grid(row=0, column=2, padx=5)
        
        # Status bar
        self.status_var = tk.StringVar(value="请选择一个分类...")
        self.status_bar = ttk.Label(main_frame, textvariable=self.status_var, 
                                    relief=tk.SUNKEN, anchor=tk.W)
        self.status_bar.grid(row=6, column=0, columnspan=2, sticky="ew", pady=(10, 0))
        
        # Store current example data
        self.current_examples = []
        self.last_built_exe = None
        
    def _get_category_key(self) -> Optional[str]:
        """Extract category key from combo selection"""
        selection = self.selected_category.get()
        if selection:
            return selection.split(" - ")[0]
        return None
    
    def _on_category_change(self, event=None):
        """Handle category selection change"""
        category = self._get_category_key()
        if not category:
            return
        
        # Update description
        categories = self.builder.get_categories()
        desc = categories.get(category, {}).get("description", "")
        self.desc_label.config(text=desc)
        
        # Update version combo
        versions = self.builder.get_versions(category)
        self.version_combo['values'] = list(versions.keys())
        default_ver = categories.get(category, {}).get("default_version", "")
        if default_ver in versions:
            self.selected_version.set(default_ver)
        elif versions:
            self.selected_version.set(list(versions.keys())[0])
        
        # Update examples list
        self._update_examples_list()
    
    def _on_version_change(self, event=None):
        """Handle version selection change"""
        self.status_var.set(f"版本已切换到: {self.selected_version.get()}")
    
    def _update_examples_list(self):
        """Update the examples listbox"""
        category = self._get_category_key()
        if not category:
            return
        
        self.example_listbox.delete(0, tk.END)
        self.current_examples = self.builder.get_examples(category)
        
        for name, path, files in self.current_examples:
            self.example_listbox.insert(tk.END, f"{name}")
        
        self.status_var.set(f"找到 {len(self.current_examples)} 个示例")
    
    def _on_example_select(self, event=None):
        """Handle example selection"""
        selection = self.example_listbox.curselection()
        if not selection:
            return
        
        idx = selection[0]
        if idx < len(self.current_examples):
            name, path, files = self.current_examples[idx]
            self.selected_example = (name, path, files)
            
            # Update source files display
            self.source_text.config(state='normal')
            self.source_text.delete('1.0', tk.END)
            self.source_text.insert('1.0', '\n'.join(files))
            self.source_text.config(state='disabled')
            
            self.status_var.set(f"已选择: {name} ({len(files)} 个源文件)")
    
    def _on_build_click(self, event=None):
        """Handle build button click"""
        if not self.selected_example:
            messagebox.showwarning("警告", "请先选择一个示例!")
            return
        
        category = self._get_category_key()
        version = self.selected_version.get()
        name, path, files = self.selected_example
        
        self.status_var.set(f"正在编译 {name}...")
        self.root.update()
        
        success, exe_path, message = self.builder.build_example(
            category, version, name, path, files
        )
        
        if success:
            self.last_built_exe = exe_path
            self.status_var.set(f"编译成功: {exe_path}")
            messagebox.showinfo("编译成功", f"可执行文件: {exe_path}")
        else:
            self.status_var.set("编译失败")
            messagebox.showerror("编译失败", message)
    
    def _on_run_click(self):
        """Handle run button click"""
        if not self.last_built_exe:
            messagebox.showwarning("警告", "请先编译示例!")
            return
        
        if not os.path.exists(self.last_built_exe):
            messagebox.showerror("错误", f"可执行文件不存在: {self.last_built_exe}")
            return
        
        try:
            # Run in a new terminal
            subprocess.Popen(
                ['cmd', '/c', 'start', 'cmd', '/k', self.last_built_exe],
                cwd=os.path.dirname(self.last_built_exe)
            )
            self.status_var.set(f"正在运行: {self.last_built_exe}")
        except Exception as e:
            messagebox.showerror("运行错误", str(e))
    
    def _on_debug_click(self):
        """Handle debug button click - set up VSCode debugging"""
        if not self.selected_example:
            messagebox.showwarning("警告", "请先选择一个示例!")
            return
        
        category = self._get_category_key()
        name, path, files = self.selected_example
        
        # Sanitize target name for exe path
        target_name = self.builder._sanitize_target_name(name)
        
        # Determine exe path
        exe_path = self.builder.build_dir / category / target_name / "Debug" / f"{target_name}.exe"
        working_dir = str(self.builder.project_root / path)
        
        # Update VSCode launch.json
        config_name = self.builder.update_vscode_launch(
            str(exe_path), name, working_dir
        )
        
        self.status_var.set(f"已更新VSCode调试配置: {config_name}")
        messagebox.showinfo(
            "调试配置已更新",
            f"已在 .vscode/launch.json 中添加/更新调试配置:\n{config_name}\n\n"
            f"请在VSCode中:\n"
            f"1. 先点击'编译'按钮编译项目\n"
            f"2. 按F5或使用调试面板启动调试\n"
            f"3. 选择配置: {config_name}"
        )
    
    def run(self):
        """Start the GUI"""
        self.root.mainloop()


def main():
    # Get project root (directory containing this script)
    script_dir = Path(__file__).parent.resolve()
    
    try:
        builder = ProjectBuilder(str(script_dir))
        gui = BuilderGUI(builder)
        gui.run()
    except FileNotFoundError as e:
        print(f"Error: {e}")
        input("Press Enter to exit...")
        sys.exit(1)
    except Exception as e:
        print(f"Unexpected error: {e}")
        import traceback
        traceback.print_exc()
        input("Press Enter to exit...")
        sys.exit(1)


if __name__ == "__main__":
    main()

# TJH Test Project - 统一构建系统

## 项目结构

```
tjh_test/
├── build_project.py      # 主构建脚本(Python GUI)
├── build_and_run.bat     # 快速启动批处理脚本
├── config.json           # 项目配置文件
├── build/                # 构建输出目录
│   ├── opencv/           # OpenCV示例构建
│   ├── ffmpeg/           # FFmpeg示例构建
│   └── ...
├── .vscode/              # VSCode配置
│   ├── launch.json       # 调试配置
│   ├── tasks.json        # 任务配置
│   └── c_cpp_properties.json  # C++智能感知配置
│
├── opencv_test/          # OpenCV相关示例
├── ffmpegbox/            # FFmpeg相关示例
├── static_test/          # C++基础语法和算法测试
├── testbox/              # 算法练习(LeetCode/牛客)
├── otherdll/             # 其他第三方库示例
└── armbox/               # ARM平台相关示例
```

## 快速开始

### 方法1: 双击运行
直接双击 `build_and_run.bat` 启动构建工具。

### 方法2: Python运行
```bash
python build_project.py
```

### 方法3: VSCode任务
在VSCode中按 `Ctrl+Shift+P`，输入 `Run Task`，选择 `Build with Python Builder`。

## 使用步骤

1. **选择分类 (Category)**
   - opencv: OpenCV图像处理示例
   - ffmpeg: FFmpeg音视频处理示例
   - static_test: C++基础语法和算法测试
   - testbox: 算法练习和题目
   - otherdll: 其他第三方库示例
   - armbox: ARM平台相关示例

2. **选择版本 (Version)**
   - 不同分类可能有不同版本的依赖库
   - 例如OpenCV可以选择4.5.0或4.8.0

3. **选择示例 (Example)**
   - 双击示例名称或点击"编译"按钮进行编译

4. **运行或调试**
   - 点击"运行"直接运行可执行文件
   - 点击"调试"配置VSCode调试环境，然后按F5启动调试

## 配置说明

### config.json
主配置文件，包含：
- `categories`: 示例分类定义
- `versions`: 每个分类的版本配置(库路径等)
- `global_settings`: 全局CMake设置

### 添加新分类
在 `config.json` 的 `categories` 中添加：
```json
"new_category": {
    "name": "分类显示名称",
    "description": "分类描述",
    "source_dir": "源代码目录名",
    "versions": {
        "1.0": {
            "include_dirs": ["头文件目录"],
            "lib_dirs": ["库文件目录"],
            "libs": ["需要链接的库"]
        }
    },
    "default_version": "1.0"
}
```

### 添加新版本
在对应分类的 `versions` 中添加新版本配置即可。

## VSCode调试

1. 使用Python构建工具选择并编译示例
2. 点击"调试"按钮更新launch.json
3. 在VSCode中按F5启动调试
4. 在"运行和调试"面板中选择对应的调试配置

## 依赖要求

- Python 3.x (带tkinter)
- CMake 3.10+
- Visual Studio 2022 (或其他C++编译器)
- 对应分类所需的库(OpenCV, FFmpeg等)

## 故障排除

### 编译失败
- 检查 `config.json` 中的库路径是否正确
- 确保已安装所需的依赖库
- 查看构建目录中的CMakeError.log

### 找不到可执行文件
- 检查 `build/<category>/<example>/Debug/` 目录
- 确保编译成功完成

### VSCode调试问题
- 确保已安装C/C++扩展
- 检查 `.vscode/launch.json` 中的路径是否正确

#!/bin/bash
# TJH Test Project - 统一构建脚本
# 用于Linux/Mac环境，或Git Bash

# 使用方法:
# ./build.sh                    # 启动Python GUI
# ./build.sh clean              # 清理构建目录
# ./build.sh <category> <name>  # 直接编译指定示例

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="${PROJECT_ROOT}/build"

# 清理构建目录
clean_build() {
    echo "Cleaning build directory..."
    rm -rf "${BUILD_DIR}"
    echo "Done."
}

# 启动Python GUI
launch_gui() {
    python3 "${PROJECT_ROOT}/build_project.py" || python "${PROJECT_ROOT}/build_project.py"
}

# 直接编译指定示例
build_example() {
    local category=$1
    local example=$2
    local example_build_dir="${BUILD_DIR}/${category}/${example}"
    
    echo "Building ${category}/${example}..."
    mkdir -p "${example_build_dir}"
    
    cd "${example_build_dir}"
    cmake -DCMAKE_BUILD_TYPE=Debug "${example_build_dir}"
    cmake --build . --config Debug
    
    echo "Build complete. Executable at: ${example_build_dir}/Debug/${example}"
}

# 主逻辑
case "${1}" in
    clean)
        clean_build
        ;;
    "")
        launch_gui
        ;;
    *)
        if [ -n "${2}" ]; then
            build_example "${1}" "${2}"
        else
            echo "Usage: $0 [clean | <category> <example_name>]"
            echo "       $0              # Launch GUI"
            echo "       $0 clean        # Clean build directory"
            echo "       $0 opencv test1 # Build opencv/test1"
        fi
        ;;
esac
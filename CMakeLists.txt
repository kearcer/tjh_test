# 设置CMake最低版本要求
cmake_minimum_required(VERSION 3.10)

# 设置项目名称和版本
project(testbox)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 设置编译类型为Debug
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++")

# 添加可执行目标
# add_executable(main ./ffmpegbox/test1/source/main.cpp)
add_executable(main ./testbox/test.cpp)
# add_executable(main ./test49_Create_A_Map_Using_Three_Ways/src/main.cpp)

# 为目标添加-g选项
target_compile_options(main PRIVATE -g)

#链接上一些动态链接so
# target_link_libraries(main avcodec avformat avutil swscale)
set(CMAKE_EXE_LINKER_FLAGS "-Wl,-Bdynamic -ldl")

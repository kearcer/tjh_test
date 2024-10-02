cmake_minimum_required(VERSION 3.10)
project(testbox)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 指定OpenCV所在的目录
set(OpenCV_DIR "C:\\WorkSpace\\my_tool\\opencv\\build\\")

include_directories(C:\\WorkSpace\\my_tool\\mediainfolib\\include\\)

# 查找需要的包
find_package(OpenCV REQUIRED)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++")

link_directories(C:\\WorkSpace\\my_tool\\mediainfolib\\lib\\)

add_executable(main ./otherdll/1_media_info/main.cpp)

target_compile_options(main PRIVATE -g)

# 链接OpenCV
target_link_libraries(main ${OpenCV_LIBS} MediaInfo.lib MediaInfo-Static.lib ZenLib.lib)

set(CMAKE_EXE_LINKER_FLAGS "-Wl,-Bdynamic -ldl")

cmake_minimum_required(VERSION 3.10)
project(testbox)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 指定OpenCV所在的目录
set(OpenCV_DIR "C:\\WorkSpace\\my_tool\\opencv_480\\opencv\\build\\")

# 查找需要的包
find_package(OpenCV REQUIRED)
set(CMAKE_BUILD_TYPE Release)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++")

add_executable(main ./static_test/test51_Paser_xlf/main.cpp)

target_compile_options(main PRIVATE)

# 链接OpenCV和zbar
target_link_libraries(main ${OpenCV_LIBS} )
# set(CMAKE_EXE_LINKER_FLAGS "-Wl,-Bdynamic -ldl")
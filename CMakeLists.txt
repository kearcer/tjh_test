cmake_minimum_required(VERSION 3.10)
project(testbox)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(ZBAR_INC_DIR "C:\\WorkSpace\\my_tool\\ZBarlib\\include\\")
set(ZXING_INC_DIR "C:\\WorkSpace\\my_tool\\ZXinglib\\src\\")
set(ZXING_STB_INC_DIR "C:\\WorkSpace\\my_tool\\ZXinglib\\stb-src\\")

set(ZBAR_LIB_DIR "C:\\WorkSpace\\my_tool\\ZBarlib\\lib\\")
# set(ZXING_LIB_DIR "C:\\WorkSpace\\my_tool\\zxing-cpp.Debug\\core\\Debug\\") 
set(ZXING_LIB_DIR "C:\\WorkSpace\\my_tool\\zxing-cpp.release\\core\\Release\\")

# 指定OpenCV所在的目录
set(OpenCV_DIR "C:\\WorkSpace\\my_tool\\opencv_480\\opencv\\build\\")

# 查找需要的包
find_package(OpenCV REQUIRED)
set(CMAKE_BUILD_TYPE Release)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++")

# 添加 zbar 头文件路径
include_directories(${ZBAR_INC_DIR} ${ZXING_INC_DIR} ${ZXING_STB_INC_DIR})
 
# 添加 zbar 库文件路径
link_directories(${ZBAR_LIB_DIR} ${ZXING_LIB_DIR})

# opencv
# add_executable(main ./opencv_test/8_bar_QR_code_detection/main.cpp)
# zbar
# add_executable(main ./opencv_test/9_Zbar_code_detection/main.cpp)
# raw
# add_executable(main ./opencv_test/7_bar_code_detection/main.cpp)
# zxing
add_executable(main ./opencv_test/10_ZXing_code_detection/main.cpp)

target_compile_options(main PRIVATE)

# 链接OpenCV和zbar
target_link_libraries(main ${OpenCV_LIBS} libzbar64-0.lib ${ZXING_LIB_DIR}\\ZXing.lib)
# set(CMAKE_EXE_LINKER_FLAGS "-Wl,-Bdynamic -ldl")
#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    printf("i get this points\n");
    // 图片文件路径
    std::string image_path = "path_to_your_image.jpg";

    // 读取图像
    cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);

    // 检查图像是否成功加载
    if(img.empty()) {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }

    // 创建一个窗口
    cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE);

    // 在窗口中显示图像
    cv::imshow("Display window", img);

    // 等待按键事件
    cv::waitKey(0);

    return 0;
}

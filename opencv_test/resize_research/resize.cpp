#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    std::string imagePath = "C:\\WorkSpace\\mytest\\tjh_test\\opencv_test\\resize_research\\testfile2.png";

    cv::Mat img = cv::imread(imagePath, cv::IMREAD_COLOR);

    if (img.empty()) {
        std::cout << "Could not read the image: " << imagePath << std::endl;
        return 1;
    }

    cv::Mat resizedImg;

    int width = 16; // 新宽度
    int height = 16; // 新高度

    cv::resize(img, resizedImg, cv::Size(width, height), 0, 0, cv::INTER_NEAREST);
    cv::imwrite("resize.png", resizedImg);

    cv::imwrite("original.png", img);

    // cv::imshow("Resized Image", resizedImg);

    // cv::waitKey(0);

    return 0;
}

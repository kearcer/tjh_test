// An highlighted block
// m_otsu.cpp : 定义控制台应用程序的入口点。
//
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/core/core.hpp> 
#include <iostream>
using namespace cv;
using namespace std;
//***************Otsu算法通过求类间方差极大值求自适应阈值******************
int otsu(cv::Mat img);

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int otsu(cv::Mat img);

int main(int argc, char* argv[])
{
    // 读取图像
    const char* Image1Name = "C:\\WorkSpace\\mytest\\tjh_test\\opencv_test\\3_otsu_improve\\6.png";
    Mat image = imread(Image1Name, IMREAD_GRAYSCALE);
    
    if (image.empty()) {
        cout << "Could not open or find the image" << endl;
        return -1;
    }

    // Resize image to 800x800
    resize(image, image, Size(800, 800));

    imwrite("./input_Image.png", image);

    // 计算直方图
    int histSize = 256; // 直方图的bin数量
    float range[] = {0, 256};
    const float* histRange = {range};
    bool uniform = true, accumulate = false;
    Mat hist;

    calcHist(&image, 1, 0, Mat(), hist, 1, &histSize, &histRange, uniform, accumulate);

    // 显示直方图
    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound((double)hist_w/histSize);
    Mat histImage(hist_h + 50, hist_w, CV_8UC3, Scalar(0,0,0));

    // 归一化直方图
    normalize(hist, hist, 0, histImage.rows - 50, NORM_MINMAX, -1, Mat());

    // 绘制直方图
    for (int i = 1; i < histSize; i++) {
        line(histImage,
             Point(bin_w*(i-1), hist_h - cvRound(hist.at<float>(i-1))),
             Point(bin_w*i, hist_h - cvRound(hist.at<float>(i))),
             Scalar(255, 0, 0), 2, 8, 0);
    }

    // 添加坐标轴
    line(histImage, Point(0, hist_h), Point(hist_w, hist_h), Scalar(255, 255, 255), 2, 8, 0);
    line(histImage, Point(0, 0), Point(0, hist_h), Scalar(255, 255, 255), 2, 8, 0);

    // 添加刻度和标签
    for (int i = 0; i < histSize; i += 16) {
        line(histImage, Point(bin_w*i, hist_h), Point(bin_w*i, hist_h + 5), Scalar(255, 255, 255), 2, 8, 0);
        putText(histImage, to_string(i), Point(bin_w*i - 10, hist_h + 20), FONT_HERSHEY_SIMPLEX, 0.3, Scalar(255, 255, 255), 1, 8, false);
    }

    for (int i = 0; i < hist_h; i += 50) {
        line(histImage, Point(0, hist_h - i), Point(-5, hist_h - i), Scalar(255, 255, 255), 2, 8, 0);
        putText(histImage, to_string(i), Point(-30, hist_h - i + 5), FONT_HERSHEY_SIMPLEX, 0.3, Scalar(255, 255, 255), 1, 8, false);
    }

    imshow("Histogram", histImage);

    // 应用大津算法找到最佳阈值
    int thresholdValue = otsu(image);
    printf("Interclass variance: %d\n", thresholdValue);

    // 使用计算出的阈值对图片进行阈值处理
    Mat imageOutput, imageOtsu;
    threshold(image, imageOutput, 32, 255, THRESH_BINARY);

    // 使用OpenCV的OTSU算法作为对比
    threshold(image, imageOtsu, 0, 255, THRESH_OTSU);

    imwrite("./Output_Image.png", imageOutput);
    imshow("Output Image", imageOutput);
    imwrite("./Opencv_Otsu.png", imageOtsu);
    imshow("Opencv Otsu", imageOtsu);

    waitKey(0);
    return 0;
}

int otsu(cv::Mat img)
{
    if (img.channels() > 1) {
        cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
    }

    int pixsize = img.total();    // 图像的总像素数
    int pixsi = 256;              // 灰度级数（0-255）
    int nThresh = 0;
    std::vector<float> fStdHistogram(pixsi, 0); // 图像直方图，256个点
    std::vector<float> fGrayAccu(pixsi, 0);
    std::vector<float> fGrayAve(pixsi, 0);
    float fAverage = 0;

    // 构建直方图
    for (int i = 0; i < img.rows; ++i) {
        for (int j = 0; j < img.cols; ++j) {
            fStdHistogram[img.at<uchar>(i, j)] += 1.0;
        }
    }

    // 标准化直方图
    for (int i = 0; i < pixsi; ++i) {
        fStdHistogram[i] /= pixsize;
    }

    // 计算累积直方图和加权累积直方图
    for (int i = 0; i < pixsi; ++i) {
        for (int j = 0; j <= i; ++j) {
            fGrayAccu[i] += fStdHistogram[j];
            fGrayAve[i] += j * fStdHistogram[j];
        }
        fAverage += i * fStdHistogram[i];
    }

    // 计算阈值
    float fMax = 0;
    for (int i = 0; i < pixsi; ++i) {
        if (fGrayAccu[i] == 0 || fGrayAccu[i] == 1) continue;  // 避免除以0
        float fTemp = (fAverage * fGrayAccu[i] - fGrayAve[i]);
        fTemp = fTemp * fTemp / (fGrayAccu[i] * (1 - fGrayAccu[i]));
        if (fTemp > fMax) {
            fMax = fTemp;
            nThresh = i;
        }
    }

    return nThresh;
}

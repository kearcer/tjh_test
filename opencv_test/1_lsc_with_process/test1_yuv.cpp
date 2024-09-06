#include <opencv2/opencv.hpp>
#include <iostream>
#include <thread>
#include <vector>
#include <fstream>
#include <chrono>

static constexpr uint32_t GRID_CORRECTION_SIZE = 3;
static constexpr float YUV_SCALE_RATE = 0.8f;
const constexpr double DOUBLE_EPSINONTHR = 0.00001;

class ShadingCorrection {
public:
    ShadingCorrection(float calibGridHeight, float calibGridWidth);

    bool CalcMaskBGR(cv::Mat& src, cv::Mat& mask, cv::Scalar& global_mean);
    bool ApplyMaskToImage(cv::Mat& src, cv::Mat& mask, cv::Mat& dst);
    bool GenerateInvertedMask(const cv::Mat& originalMask, const cv::Scalar& originalGlobalMean, cv::Mat& invertedMask);
    bool RecoverOriginalMask(const cv::Mat& mask, const cv::Scalar& mean, cv::Mat& src);
    bool CalcMaskYUV(cv::Mat& src, cv::Mat& mask, cv::Scalar& global_mean);

private:
    cv::Mat mOptimizeMask;
    float mCalibGridHeight;
    float mCalibGridWidth;
};

ShadingCorrection::ShadingCorrection(float calibGridHeight, float calibGridWidth) 
    : mCalibGridHeight(calibGridHeight), mCalibGridWidth(calibGridWidth) {}


bool ShadingCorrection::CalcMaskYUV(cv::Mat& src, cv::Mat& mask, cv::Scalar& global_mean) {
    // Get total mean
    float sum = 0;
    for (int32_t i = 0; i < src.rows; i++) {
        for (int32_t j = 0; j < src.cols; j += 2) {
            uchar y1 = src.at<cv::Vec2b>(i, j)[0];
            uchar y2 = src.at<cv::Vec2b>(i, j + 1)[0];
            sum += (y1 + y2);
        }
    }

    float totalMean = sum / (src.rows * src.cols) * YUV_SCALE_RATE;
    global_mean = cv::Scalar(totalMean, 0, 0);
    mask = cv::Mat(src.rows, src.cols, CV_16FC2);
    mask.forEach<cv::Vec<cv::float16_t, 2>>([&](cv::Vec<cv::float16_t, 2>& pixel, const int32_t* position) -> void {
        float value = static_cast<float>(src.at<cv::Vec2b>(position[0], position[1])[0]);
        if (value > DOUBLE_EPSINONTHR) {
            pixel[0] = cv::saturate_cast<cv::float16_t>(totalMean / value);
        } else {
            pixel[0] = cv::saturate_cast<cv::float16_t>(totalMean);
        }
        pixel[1] = cv::saturate_cast<cv::float16_t>(1);
    });
    return true;
}

bool ShadingCorrection::CalcMaskBGR(cv::Mat& src, cv::Mat& mask, cv::Scalar& global_mean) {
    // 计算全局均值，用于后续遮罩计算
    global_mean = cv::mean(src);

    // 计算图像可以被分割成的网格块数（行数和列数）
    int32_t sub_height_cnt = static_cast<int32_t>(std::floor(src.rows / mCalibGridHeight));
    int32_t sub_width_cnt = static_cast<int32_t>(std::floor(src.cols / mCalibGridWidth));

    // 如果图像的尺寸不能被网格尺寸整除，则增加一个网格块数以包含剩余部分
    if (std::fmod(src.rows, mCalibGridHeight) != 0) sub_height_cnt++;
    if (std::fmod(src.cols, mCalibGridWidth) != 0) sub_width_cnt++;

    // 初始化遮罩矩阵，大小与输入图像相同，类型为CV_32FC3，初始值为1
    mask = cv::Mat::ones(src.rows, src.cols, CV_16FC3);

    // 遍历每个网格块
    for (int i = 0; i < sub_height_cnt; ++i) {
        for (int j = 0; j < sub_width_cnt; ++j) {
            // 计算每个网格块在原始图像中的位置范围
            int32_t row_min = i * mCalibGridHeight;
            int32_t col_min = j * mCalibGridWidth;

            int32_t row_max = (i + 1) * mCalibGridHeight;
            int32_t col_max = (j + 1) * mCalibGridWidth;

            // 确保网格块不超出图像边界
            if (row_max > src.rows) row_max = src.rows;
            if (col_max > src.cols) col_max = src.cols;

            // 提取该网格块对应的图像区域
            cv::Mat imageROI = src(cv::Range(row_min, row_max), cv::Range(col_min, col_max));
            // 计算该图像区域的局部均值
            cv::Scalar local_mean = cv::mean(imageROI);

            for (int c = 0; c < 3; ++c) {
                if (local_mean[c] < 1) {
                    local_mean[c] = 1;
                }
            }

            // 计算遮罩值并设置到遮罩矩阵的对应位置
            mask(cv::Range(row_min, row_max), cv::Range(col_min, col_max)).setTo(
                cv::Scalar(global_mean.val[0] / (local_mean.val[0] + 1e-5),
                           global_mean.val[1] / (local_mean.val[1] + 1e-5),
                           global_mean.val[2] / (local_mean.val[2] + 1e-5)
                )
            );
        }
    }
    // 返回true表示遮罩计算成功
    return true;
}

bool ShadingCorrection::ApplyMaskToImage(cv::Mat& src, cv::Mat& mask, cv::Mat& dst) {
    if (src.empty() || mask.empty() || src.size() != mask.size() /*|| src.type() != mask.type()*/) {
        std::cerr << "Source or mask is not valid:" << std::endl;
        std::cerr << "Source empty: " << src.empty() << std::endl;
        std::cerr << "Mask empty: " << mask.empty() << std::endl;
        std::cerr << "Sizes different: " << (src.size() != mask.size()) << " (src: " << src.size() << ", mask: " << mask.size() << ")" << std::endl;
        std::cerr << "Types different: " << (src.type() != mask.type()) << " (src: " << src.type() << ", mask: " << mask.type() << ")" << std::endl;
        return false;
    }
    // 确保 src 的像素值不小于1
    cv::Mat correctedSrc = src.clone();
    correctedSrc.forEach<cv::Vec3b>([](cv::Vec3b &pixel, const int * position) -> void {
        for (int c = 0; c < 3; ++c) {
            if (pixel[c] < 1) pixel[c] = 1;
        }
    });

    if (correctedSrc.type() != mask.type()) {
        // 将src转换为与mask相同的类型
        cv::Mat convertedMask;
        correctedSrc.convertTo(convertedMask, mask.type());
        correctedSrc = convertedMask;
    }

    dst.create(correctedSrc.size(), correctedSrc.type());
    
    cv::multiply(correctedSrc, mask, dst, 1.0, dst.type());
    return true;
}

void invertImage(const cv::Mat& inputImage, cv::Mat& invertedImage) {
    // invertedImage = cv::Mat(inputImage.size(), inputImage.type());

    // 对每个像素进行255 - 原始值操作
    for (int i = 0; i < inputImage.rows; ++i) {
        for (int j = 0; j < inputImage.cols; ++j) {
            cv::Vec3b pixel = inputImage.at<cv::Vec3b>(i, j);
            invertedImage.at<cv::Vec3b>(i, j) = cv::Vec3b(255 - pixel[0], 255 - pixel[1], 255 - pixel[2]);
        }
    }
}

bool ShadingCorrection::GenerateInvertedMask(const cv::Mat& originalMask, const cv::Scalar& originalGlobalMean, cv::Mat& invertedMask) {
    if (originalMask.empty()) {
        std::cerr << "Original mask is empty." << std::endl;
        return false;
    }

    invertedMask = originalMask.clone(); // 克隆原始遮罩以保留其尺寸和类型

    // std::cout << "---------------------------------------" << std::endl;
    // std::cout << "originalMask:" << originalMask << std::endl;

    // 遍历原始遮罩中的每个像素点
    for (int i = 0; i < originalMask.rows; ++i) {
        for (int j = 0; j < originalMask.cols; ++j) {
            for (int c = 0; c < 3; ++c) {  // 对于每个通道
                float originalValue = originalMask.at<cv::Vec3f>(i, j)[c];
                if (originalValue == 0) continue;  // 防止除以零

                float divisor = originalGlobalMean[c] / originalValue;
                if(divisor > 254) divisor = 254;
                float result = (255 - originalGlobalMean[c]) / (255 - divisor);
                invertedMask.at<cv::Vec3f>(i, j)[c] = result;
            }
        }
    }
    // std::cout << "---------------------------------------" << std::endl;
    // std::cout << "invertedMask:" << invertedMask << std::endl;

    return true;
}

bool ShadingCorrection::RecoverOriginalMask(const cv::Mat& mask, const cv::Scalar& mean, cv::Mat& src) {
    if (mask.empty()) {
        std::cerr << "Processed mask is empty." << std::endl;
        return false;
    }

    src = mask.clone();  // 克隆处理过的遮罩以保留其尺寸和类型

    // 遍历处理过的遮罩中的每个像素点
    for (int i = 0; i < mask.rows; ++i) {
        for (int j = 0; j < mask.cols; ++j) {
            for (int c = 0; c < 3; ++c) {  // 对于每个通道
                float processedValue = mask.at<cv::Vec3f>(i, j)[c];
                float originalValue = mean[c] * 255 / (255 * processedValue - 255 + mean[c]);
                if (originalValue < 0) originalValue = 0;     // 保证像素值非负
                if (originalValue > 255) originalValue = 255; // 保证像素值不超过255
                src.at<cv::Vec3f>(i, j)[c] = originalValue;
            }
        }
    }
    return true;
}

int main() {
    uint32_t maskBufLen_out = 0;
    int32_t width = 4;
    int32_t height = 4;
    int32_t type = CV_8UC2;

    std::ifstream file("./yuvtestfile.yuv", std::ios::binary);
    if (!file) {
        std::cerr << "Unable to open the YUV file" << std::endl;
        return -1;
    }
    size_t size = width * height * 2;
    std::vector<unsigned char> buffer(size);
    file.read(reinterpret_cast<char*>(buffer.data()), size);
    cv::Mat image = cv::Mat(height, width, type, buffer.data());

    cv::Mat mask;
    ShadingCorrection corrector(2, 2);  // Example grid sizes
    cv::Scalar global_mean;
    
    corrector.CalcMaskYUV(image, mask, global_mean);
    std::cout << "global_mean:" << global_mean.val[0] << std::endl;
    std::cout << "image:" << image << std::endl;
    std::cout << "mask:" << mask << std::endl;

    return 0;
}


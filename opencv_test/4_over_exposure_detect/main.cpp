#include <opencv2/opencv.hpp>

class OverExposure {
public:
    OverExposure(uint8_t threshold = 128, uint8_t r = 255, uint8_t g = 255, uint8_t b = 255)
        : mThreshold(threshold), mR(r), mG(g), mB(b) {}

    void setThreshold(uint8_t threshold) { mThreshold = threshold; }
    void setColor(uint8_t r, uint8_t g, uint8_t b) { mR = r; mG = g; mB = b; }

    cv::Mat createMask(const cv::Mat& src, bool isColor);
    cv::Mat applyMask(const cv::Mat& src, const cv::Mat& mask, bool isColor);

private:
    uint8_t mThreshold;
    uint8_t mR, mG, mB;
};

cv::Mat OverExposure::createMask(const cv::Mat& src, bool isColor) {
    cv::Mat gray;
    if (isColor) {
        cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    } else {
        gray = src;
    }
    cv::Mat mask = gray >= mThreshold;  // Generate mask
    return mask;
}

cv::Mat OverExposure::applyMask(const cv::Mat& src, const cv::Mat& mask, bool isColor) {
    cv::Mat result;
    if (isColor) {
        result = src.clone();
    } else {
        cv::cvtColor(src, result, cv::COLOR_GRAY2BGR);  // Convert grayscale to BGR
    }

    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            if (mask.at<uint8_t>(y, x)) {  // Apply color where mask is true
                result.at<cv::Vec3b>(y, x) = cv::Vec3b(mB, mG, mR);
            }
        }
    }
    return result;
}

int main() {
    cv::Mat colorSrc = cv::imread("C:\\WorkSpace\\mytest\\tjh_test\\opencv_test\\4_over_exposure_detect\\1280x720_0.jpg");
    cv::Mat graySrc = cv::imread("C:\\WorkSpace\\mytest\\tjh_test\\opencv_test\\4_over_exposure_detect\\1280x720_gray.jpg", cv::IMREAD_GRAYSCALE);

    OverExposure oe(200, 255, 0, 0);

    if (!colorSrc.empty()) {
        cv::Mat colorMask = oe.createMask(colorSrc, true);
        cv::Mat colorResult = oe.applyMask(colorSrc, colorMask, true);
        cv::imwrite("color_output.jpg", colorResult);
    }

    if (!graySrc.empty()) {
        cv::Mat grayMask = oe.createMask(graySrc, false);
        cv::Mat grayResult = oe.applyMask(graySrc, grayMask, false);
        cv::imwrite("gray_output.jpg", grayResult);
    }

    return 0;
}

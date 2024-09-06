#include <opencv2/opencv.hpp>

class OverExposure {
public:
    OverExposure(uint8_t threshold = 128, uint8_t r = 255, uint8_t g = 255, uint8_t b = 255)
        : mThreshold(threshold), mR(r), mG(g), mB(b) {}

    void setThreshold(uint8_t threshold) {
        mThreshold = threshold;
    }

    void setColor(uint8_t r, uint8_t g, uint8_t b) {
        mR = r;
        mG = g;
        mB = b;
    }

    cv::Mat runGray(cv::Mat src) {
        // Assuming src is already a grayscale image
        cv::Mat result;
        cv::cvtColor(src, result, cv::COLOR_GRAY2BGR);
        for (int y = 0; y < result.rows; y++) {
            for (int x = 0; x < result.cols; x++) {
                cv::Vec3b& pixel = result.at<cv::Vec3b>(y, x);
                int gray = pixel[0];  // Since all channels are the same in a gray converted to BGR
                if (gray >= mThreshold) {
                    pixel[0] = mB;
                    pixel[1] = mG;
                    pixel[2] = mR;
                }
            }
        }
        return result;
    }

    cv::Mat runBGR(cv::Mat src) {
        cv::Mat result = src.clone();
        for (int y = 0; y < result.rows; y++) {
            for (int x = 0; x < result.cols; x++) {
                cv::Vec3b& pixel = result.at<cv::Vec3b>(y, x);
                int gray = pixel[0] * 0.114 + pixel[1] * 0.587 + pixel[2] * 0.299;
                if (gray >= mThreshold) {
                    pixel[0] = mB;
                    pixel[1] = mG;
                    pixel[2] = mR;
                }
            }
        }
        return result;
    }

private:
    uint8_t mThreshold;
    uint8_t mR, mG, mB;
};

int main() {
    // Load a color image
    cv::Mat colorSrc = cv::imread("C:\\WorkSpace\\mytest\\tjh_test\\opencv_test\\4_over_exposure_detect\\1280x720_0.jpg"); // Replace with your color image path
    // Load a grayscale image
    cv::Mat graySrc = cv::imread("C:\\WorkSpace\\mytest\\tjh_test\\opencv_test\\4_over_exposure_detect\\1280x720_gray.jpg", cv::IMREAD_GRAYSCALE); // Replace with your grayscale image path

    // Create an OverExposure object
    OverExposure oe(200, 255, 0, 0);  // Set threshold and replacement color

    // Process the color image if it is loaded
    if (!colorSrc.empty()) {
        cv::Mat colorResult = oe.runBGR(colorSrc);
        cv::imwrite("color_output.jpg", colorResult);  // Output color image path
    }

    // Process the grayscale image if it is loaded
    if (!graySrc.empty()) {
        cv::Mat grayResult = oe.runGray(graySrc);
        cv::imwrite("gray_output.jpg", grayResult);  // Output grayscale image path
    }

    return 0;
}

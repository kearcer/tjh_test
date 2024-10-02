/*
 * @Author: Jiahui Tang jiahui.tang@leica-microsystems.com
 * @Date: 2024-09-23 09:18:38
 * @LastEditors: Jiahui Tang jiahui.tang@leica-microsystems.com
 * @LastEditTime: 2024-09-23 09:19:40
 * @FilePath: \tjh_test\static_test\test52_Metadata_Generate\swc_data.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置:
 * https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef SWC_DATA_H
#define SWC_DATA_H

#include <memory>
#include <opencv2/opencv.hpp>
#include <string>

#if defined(WIN32) && defined(BUILD_SHARED_LIB)
#define CAMERA_API __declspec(dllexport)
#elif defined(WIN32)
#define CAMERA_API __declspec(dllimport)
#elif defined(__linux__) && defined(BUILD_SHARED_LIB)
#define CAMERA_API __attribute__((visibility("default")))
#else
#define CAMERA_API
#endif

namespace smt_sdk {
namespace swc_data {

class LASXDataConverter {
   public:
    /**
     * @brief Create an instance of ImageProcessor.
     * @return shared pointer to an ImageProcessor instance.
     **************************************************************************/
    CAMERA_API static std::shared_ptr<ImageProcessor> Create();

    /**
     * @brief Load and parse the project configuration file or directory.
     * @param[in] path Path to the project folder or xlef configuration file.
     * @return true if the configuration is loaded successfully, false otherwise.
     **************************************************************************/
    CAMERA_API virtual bool LoadProjectConfiguration(const std::string& path) = 0;

    /**
     * @brief Process and possibly convert the image to a supported format.
     * @param[in] imagePath Path to the image file.
     * @return true if the image is processed successfully, false otherwise.
     **************************************************************************/
    CAMERA_API virtual bool ProcessImage(const std::string& imagePath) = 0;

    /**
     * @brief Generate metadata file based on extracted or provided metadata.
     * @param[in] metadata Information extracted from the image or provided externally.
     * @param[out] outputPath Path where the metadata file will be saved.
     * @return true if the metadata file is generated successfully, false otherwise.
     **************************************************************************/
    CAMERA_API virtual bool GenerateMetadata(const std::string& metadata, const std::string& outputPath) = 0;

    /**
     * @brief Decode the image to extract metadata like resolution, color depth, and capture time.
     * @param[in] image Data of the image or path to the image file.
     * @return a string containing the extracted metadata.
     **************************************************************************/
    CAMERA_API virtual std::string DecodeImage(const cv::Mat& image) = 0;

    /**
     * @brief Get a brief description of the current configuration and processing status.
     * @return String describing the current status.
     **************************************************************************/
    CAMERA_API virtual std::string GetStatusDescription() = 0;
};

}  // namespace swc_data
}  // namespace smt_sdk

#endif  // CAMERA_DATA_PROCESSING_H

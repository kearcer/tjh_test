/*
 * @Author: Jiahui Tang jiahui.tang@leica-microsystems.com
 * @Date: 2024-09-22 22:31:22
 * @LastEditors: Jiahui Tang jiahui.tang@leica-microsystems.com
 * @LastEditTime: 2024-09-25 16:24:02
 * @FilePath: \tjh_test\static_test\test52_Metadata_Generate\main.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置:
 * https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
// LASXConverter.h

#ifndef LASX_CONVERTER_H
#define LASX_CONVERTER_H

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>


#if defined(WIN32) && defined(BUILD_SHARED_LIB)
#define SWC_DATA_API __declspec(dllexport)
#elif defined(WIN32)
#define SWC_DATA_API __declspec(dllimport)
#elif defined(__linux__) && defined(BUILD_SHARED_LIB)
#define SWC_DATA_API __attribute__((visibility("default")))
#else
#define SWC_DATA_API
#endif

namespace smt_sdk {
namespace swc_data {
// Supported image List
enum class EnersightSupportFormat {
    BMP,
    JPG,
    PNG,
    TIF,
};

// Metadata struct
struct Metadata {
    std::string appVersion;
    int bitDepth;
    double blueGain;
    std::string calibrationInfo;
    std::string calibrationName;
    std::string camera;
    std::string cameraMode;
    std::string createdTime;
    std::string device;
    std::string deviceSerialNumber;
    std::string digitalZoom;
    long exposure;
    std::string filterTurret;
    std::string format;
    int gain;
    double gamma;
    bool grayscale;
    double greenGain;
    bool hdr;
    int height;
    std::string light;
    std::string lightIntensity;
    std::string magnification;
    std::string modifiedTime;
    bool negative;
    int noiseReduction;
    std::string nosepiece;
    std::string others;
    double pix2mic;
    double redGain;
    int saturation;
    std::string serialNumber;
    int sharpness;
    std::string version;
    int width;
};

class LASXConverter {
   public:
    virtual ~LASXConverter() = default;
    /**
     * @brief 
     * @return return the instance fo LASXConverter
     **************************************************************************/
    SWC_DATA_API static std::shared_ptr<LASXConverter> Create();

    /**
     * @brief Initialize resources and metadata structures
     **************************************************************************/
    virtual void initialize() = 0;

    /**
     * @brief Load the .xlef file and extract image paths and xlif path
     * @param[in] xlefPath Path to the .xlef file
     * @param[out] imagePaths Paths to images extracted from the .xlef file
     * @param[out] metadataPath Path to the metadata file
     * @return true if file is successfully loaded, false otherwise
     **************************************************************************/
    virtual bool loadFile(const std::string& xlefPath, std::vector<std::string>& imagePaths, std::string& xlifPath) = 0;

    /**
     * @brief Convert images to supported formats if necessary
     * @param[in] imagePaths Paths to images to be converted
     * @return Paths to converted images
     **************************************************************************/
    virtual std::vector<cv::Mat> transferImages(const std::vector<std::string>& imagePaths) = 0;

    /**
     * @brief Parse metadata from an .xlif file
     * @param[in] xlifPath Path to the .xlif file
     * @return Metadata structure containing parsed metadata
     **************************************************************************/
    virtual Metadata parseMetadata(const std::string& xlifPath) = 0;

    /**
     * @brief Decode images to extract metadata
     * @param[in] imagePaths Paths to images to decode
     * @return Metadata structure containing extracted information
     **************************************************************************/
    virtual Metadata decodeImages(const std::vector<std::string>& imagePaths) = 0;

    /**
     * @brief Generate a .Metadata file from the provided metadata structure
     * @param[in] metadata Metadata structure to use for generating the file
     **************************************************************************/
    virtual void generateMetadataFile(const Metadata& metadata) = 0;
};

}  // namespace swc_data
}  // namespace smt_sdk

#endif  // LASX_CONVERTER_H

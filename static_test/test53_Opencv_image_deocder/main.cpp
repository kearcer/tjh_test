
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string>

struct CameraInfo {
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
public:
    CameraInfo();
};

CameraInfo::CameraInfo()
    : appVersion("1.2.0.643"),
      bitDepth(24),
      blueGain(2.49169921875),
      calibrationInfo("Pixel size = 9.60*9.60um^2"),
      calibrationName(""),
      camera("K3C"),
      cameraMode("BGR"),
      createdTime("2024-09-19 15:43:42.47"),
      device(""),
      deviceSerialNumber(""),
      digitalZoom("100%"),
      exposure(131753),
      filterTurret(""),
      format("PNG"),
      gain(0),
      gamma(1),
      grayscale(false),
      greenGain(1),
      hdr(false),
      height(1080),
      light(""),
      lightIntensity(""),
      magnification(""),
      modifiedTime("2024-09-19 16:10:36"),
      negative(false),
      noiseReduction(0),
      nosepiece(""),
      others("N/A"),
      pix2mic(9.60000041325887),
      redGain(1.39111328125),
      saturation(0),
      serialNumber("700005907250"),
      sharpness(2),
      version("1.0"),
      width(1920)
{}

void saveJsonToFile(const CameraInfo& info, const std::string& filePath) {
    std::ofstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error opening file for writing.\n";
        return;
    }

    file << "{\n"
         << "    \"appVersion\": \"" << info.appVersion << "\",\n"
         << "    \"bitDepth\": " << info.bitDepth << ",\n"
         << "    \"blueGain\": " << info.blueGain << ",\n"
         << "    \"calibrationInfo\": \"" << info.calibrationInfo << "\",\n"
         << "    \"calibrationName\": \"" << info.calibrationName << "\",\n"
         << "    \"camera\": \"" << info.camera << "\",\n"
         << "    \"cameraMode\": \"" << info.cameraMode << "\",\n"
         << "    \"createdTime\": \"" << info.createdTime << "\",\n"
         << "    \"device\": \"" << info.device << "\",\n"
         << "    \"deviceSerialNumber\": \"" << info.deviceSerialNumber << "\",\n"
         << "    \"digitalZoom\": \"" << info.digitalZoom << "\",\n"
         << "    \"exposure\": " << info.exposure << ",\n"
         << "    \"filterTurret\": \"" << info.filterTurret << "\",\n"
         << "    \"format\": \"" << info.format << "\",\n"
         << "    \"gain\": " << info.gain << ",\n"
         << "    \"gamma\": " << info.gamma << ",\n"
         << "    \"grayscale\": " << (info.grayscale ? "true" : "false") << ",\n"
         << "    \"greenGain\": " << info.greenGain << ",\n"
         << "    \"hdr\": " << (info.hdr ? "true" : "false") << ",\n"
         << "    \"height\": " << info.height << ",\n"
         << "    \"light\": \"" << info.light << "\",\n"
         << "    \"lightIntensity\": \"" << info.lightIntensity << "\",\n"
         << "    \"magnification\": \"" << info.magnification << "\",\n"
         << "    \"modifiedTime\": \"" << info.modifiedTime << "\",\n"
         << "    \"negative\": " << (info.negative ? "true" : "false") << ",\n"
         << "    \"noiseReduction\": " << info.noiseReduction << ",\n"
         << "    \"nosepiece\": \"" << info.nosepiece << "\",\n"
         << "    \"others\": \"" << info.others << "\",\n"
         << "    \"pix2mic\": " << info.pix2mic << ",\n"
         << "    \"redGain\": " << info.redGain << ",\n"
         << "    \"saturation\": " << info.saturation << ",\n"
         << "    \"serialNumber\": \"" << info.serialNumber << "\",\n"
         << "    \"sharpness\": " << info.sharpness << ",\n"
         << "    \"version\": \"" << info.version << "\",\n"
         << "    \"width\": " << info.width << "\n"
         << "}\n";
    file.close();
}

int main() {
    CameraInfo cameraInfo;
    saveJsonToFile(cameraInfo, "output.metadata");
    return 0;
}

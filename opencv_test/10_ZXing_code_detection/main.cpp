#include <iostream>
#include <chrono>
#include <opencv2/opencv.hpp>
#include "ReadBarcode.h"

using namespace cv;
using namespace std;
using namespace std::chrono;

inline ZXing::ImageView ImageViewFromMat(const cv::Mat& image) {
    using ZXing::ImageFormat;

    auto fmt = ImageFormat::None;
    switch (image.channels()) {
        case 1:
            fmt = ImageFormat::Lum;
            break;
        case 2:
            fmt = ImageFormat::LumA;
            break;
        case 3:
            fmt = ImageFormat::BGR;
            break;
        case 4:
            fmt = ImageFormat::BGRA;
            break;
    }

    if (image.depth() != CV_8U || fmt == ImageFormat::None) return {nullptr, 0, 0, ImageFormat::None};

    return {image.data, image.cols, image.rows, fmt};
}

inline ZXing::Barcodes ReadBarcodes(const cv::Mat& image, const ZXing::ReaderOptions& options = {}) {
    return ZXing::ReadBarcodes(ImageViewFromMat(image), options);
}

void DrawBarcode(cv::Mat& img, ZXing::Barcode barcode) {
    auto pos = barcode.position();
    auto zx2cv = [](ZXing::PointI p) { return cv::Point(p.x, p.y); };
    auto contour = std::vector<cv::Point>{zx2cv(pos[0]), zx2cv(pos[1]), zx2cv(pos[2]), zx2cv(pos[3])};
    const auto* pts = contour.data();
    int npts = contour.size();

    cv::polylines(img, &pts, &npts, 1, true, CV_RGB(0, 255, 0));
    cv::putText(img, barcode.text(), zx2cv(pos[3]) + cv::Point(0, 20), cv::FONT_HERSHEY_DUPLEX, 0.5, CV_RGB(0, 255, 0));
}

int main(int argc, char* argv[]) {
    string in_file_name;
    string out_file_name;

    // 解析命令行参数
    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "-i" && i + 1 < argc) {
            in_file_name = argv[i + 1]; // 设置输入文件名
        } else if (string(argv[i]) == "-o" && i + 1 < argc) {
            out_file_name = argv[i + 1]; // 设置输出文件目录
        }
    }

    if (in_file_name.empty()) {
        cout << "No input file specified." << endl;
        return -1;
    }

    if (out_file_name.empty()) {
        cout << "No output directory specified." << endl;
        return -1;
    }

    // 构造输出文件名
    size_t last_slash_idx = in_file_name.find_last_of("\\/");
    if (last_slash_idx == string::npos) last_slash_idx = -1; // Handle no path case
    string base_name = in_file_name.substr(last_slash_idx + 1);

    size_t last_dot_idx = base_name.rfind('.');
    if (last_dot_idx == string::npos) {
        cout << "Input file does not have an extension." << endl;
        return -1;
    }

    string name_only = base_name.substr(0, last_dot_idx);
    string extension = base_name.substr(last_dot_idx);

    out_file_name += name_only + "zxing_out" + extension; // Adding '_out' before the extension

    Mat color_src = imread(in_file_name, IMREAD_COLOR);
    if (color_src.empty()) {
        cout << "Cannot read image file: " << in_file_name << endl;
        return -1;
    }
    auto start = high_resolution_clock::now();
    auto barcodes = ReadBarcodes(color_src);
    auto end = high_resolution_clock::now();
    chrono::duration<double, milli> elapsed = end - start;
    printf("[tjhlog]zxing No.%s image in %.8f ms\n", name_only.c_str(), elapsed.count());

    if (barcodes.empty()) {
        printf("[tjhlog] No codes detected.\n");
    } else {
        for (auto& barcode : barcodes) {
            DrawBarcode(color_src, barcode);
            printf("[tjhlog] ZXing No.%s Detected %s: %s\n", name_only.c_str(), barcode.format() == ZXing::BarcodeFormat::QRCode ? "QRCode" : "Barcode", barcode.text().c_str());
        }
    }

    imwrite(out_file_name, color_src);
    waitKey(0);
}

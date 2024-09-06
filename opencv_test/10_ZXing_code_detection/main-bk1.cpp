
/*
 * Copyright 2020 Axel Waggershauser
 */
// SPDX-License-Identifier: Apache-2.0
#include <iostream>
#pragma once

#include <windows.h>

#include <chrono>
#include <iostream>
#include <opencv2/opencv.hpp>

#include "ReadBarcode.h"

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



using namespace cv;
using namespace std;
using namespace std::chrono;
void DrawBarcode(cv::Mat& img, ZXing::Barcode barcode) {
    auto pos = barcode.position();
    auto zx2cv = [](ZXing::PointI p) { return cv::Point(p.x, p.y); };
    auto contour = std::vector<cv::Point>{zx2cv(pos[0]), zx2cv(pos[1]), zx2cv(pos[2]), zx2cv(pos[3])};
    const auto* pts = contour.data();
    int npts = contour.size();

    cv::polylines(img, &pts, &npts, 1, true, CV_RGB(0, 255, 0));
    cv::putText(img, barcode.text(), zx2cv(pos[3]) + cv::Point(0, 20), cv::FONT_HERSHEY_DUPLEX, 0.5, CV_RGB(0, 255, 0));
}

string openFileDialog() {
    OPENFILENAME ofn;
    char szFile[260];
    HWND hwnd = NULL;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    if (GetOpenFileName(&ofn) == TRUE) {
        return string(ofn.lpstrFile);
    }
    return "";
}

int main() {
    string in_file_name = openFileDialog();
    if (in_file_name.empty()) {
        cout << "No file selected." << endl;
        return -1;
    }

    Mat color_src = imread(in_file_name, IMREAD_COLOR);
    if (color_src.empty()) {
        cout << "Cannot read image file: " << in_file_name << endl;
        return -1;
    }
    auto barcodes = ReadBarcodes(color_src);
    for (auto& barcode : barcodes) DrawBarcode(color_src, barcode);
    imshow("Display window", color_src);
    imwrite("C:\\WorkSpace\\mytest\\tjh_test\\opencv_test\\7_bar_code_detection\\Detected_Barcodes_out.png", color_src);
    waitKey(0);
}
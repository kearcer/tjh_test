#include <windows.h>  // 用于打开文件选择对话框

#include <iostream>
#include <string>

#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

static void drawQRCodeContour(Mat &color_image, vector<Point> transform, const string &decoded_info);
static void drawBarCodeContour(Mat &color_image, vector<Point> corners, const string &decoded_info);
string openFileDialog() {
    OPENFILENAME ofn;  // common dialog box structure
    char szFile[260];  // buffer for file name
    HWND hwnd = NULL;  // owner window

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

int main(int argc, char *argv[]) {
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

    Mat src;
    cvtColor(color_src, src, COLOR_BGR2GRAY);

    QRCodeDetector qrcode;
    Ptr<barcode::BarcodeDetector> bardet = makePtr<barcode::BarcodeDetector>();

    // QRCodeDetector qrcode;
    vector<Point> qr_transform;
    vector<string> qr_decoded_info;
    vector<Mat> qr_straight_code;
    auto start = std::chrono::high_resolution_clock::now();
    if (qrcode.detectAndDecodeMulti(src, qr_decoded_info, qr_transform, qr_straight_code)) {
        for (size_t i = 0; i < qr_decoded_info.size(); ++i) {
            cout << "Detected QR Code: " << qr_decoded_info[i] << endl;
            vector<Point> contour(qr_transform.begin() + i * 4, qr_transform.begin() + (i + 1) * 4);
            drawQRCodeContour(color_src, contour, qr_decoded_info[i]);
        }
    } else {
        cout << "No QR Codes detected." << endl;
    }

    vector<Point> bar_corners;
    vector<string> bar_decoded_info;
    vector<string> bar_decode_type;
    bardet->detectAndDecodeWithType(src, bar_decoded_info, bar_decode_type, bar_corners);

    if (!bar_decoded_info.empty()) {
        for (size_t i = 0; i < bar_decoded_info.size(); ++i) {
            cout << "Detected Barcode: " << bar_decoded_info[i] << " (Type: " << bar_decode_type[i] << ")" << endl;
            vector<Point> corners(bar_corners.begin() + i * 4, bar_corners.begin() + (i + 1) * 4);
            drawBarCodeContour(color_src, corners, bar_decoded_info[i]);
        }
    } else {
        cout << "No Barcodes detected." << endl;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    printf("size:%dx%d image, Zbar detection and decoding %.8fms\n", color_src.cols, color_src.rows, elapsed.count());

    imshow("Detected QR and Barcodes", color_src);
    imwrite("C:\\WorkSpace\\mytest\\tjh_test\\opencv_test\\7_bar_code_detection\\Detected_Barcodes_out.png",
            color_src);  // 保存图像到文件
    waitKey(0);
    return 0;
}

void drawQRCodeContour(Mat &color_image, vector<Point> transform, const string &decoded_info) {
    if (!transform.empty()) {
        vector<vector<Point>> contours{transform};
        drawContours(color_image, contours, 0, Scalar(211, 0, 148), 3);

        for (size_t i = 0; i < 4; i++) {
            circle(color_image, transform[i], 10, Scalar(0, 255, 0), -1);
        }
        if (!decoded_info.empty()) {
            putText(color_image, decoded_info, transform[0], FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 0, 0), 1);
        }
    }
}

void drawBarCodeContour(Mat &color_image, vector<Point> corners, const string &decoded_info) {
    if (corners.size() == 4) {
        vector<vector<Point>> contours{corners};
        drawContours(color_image, contours, 0, Scalar(0, 255, 255), 3);

        for (size_t i = 0; i < 4; i++) {
            circle(color_image, corners[i], 10, Scalar(255, 0, 0), -1);
        }

        if (!decoded_info.empty()) {
            putText(color_image, decoded_info, corners[0], FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 0, 0), 1);
        }
    }
}

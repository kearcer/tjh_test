#include <iostream>

struct ProgressSteps {
    double alignmentPos;
    double illuminationPos;
    double decomposePos;
    double depthPos;
    double composePos;
    double fullPos;

    // 动态调整累积进度百分比
    void adjustProgress(bool alignmentEnabled, bool illuminationEnabled) {
        // 初始化各阶段的进度
        alignmentPos = alignmentEnabled ? 40.0 : 0.0; 
        illuminationPos = illuminationEnabled ? 5.0 : 0.0;
        decomposePos = 10.0;
        depthPos = 43.0;
        composePos = 1.0;
        fullPos = 100.0;

        // 计算总的可用百分比
        double total = alignmentPos + illuminationPos + decomposePos + depthPos + composePos;

        // 累积计算每个阶段的进度
        double currentPos = 0.0;
        alignmentPos = alignmentEnabled ? currentPos += alignmentPos : 0.0;
        illuminationPos = illuminationEnabled ? currentPos += illuminationPos : currentPos;
        decomposePos = currentPos += decomposePos;
        depthPos = currentPos += depthPos;
        composePos = currentPos += composePos;
        fullPos = currentPos;
    }
};

class EDOF_IMPL {
public:
    bool mAlignmentMode;
    bool mIlluminationCorrectionMode;
    ProgressSteps progress;

    void updateProgress() {
        progress.adjustProgress(mAlignmentMode, mIlluminationCorrectionMode);
    }
};

int main() {
    EDOF_IMPL edof;
    edof.mAlignmentMode = false; // 假设对齐模式关闭
    edof.mIlluminationCorrectionMode = true; // 照明校正模式开启

    edof.updateProgress();
    
    // 输出调整后的累积进度百分比
    std::cout << "Alignment: " << edof.progress.alignmentPos << "%" << std::endl;
    std::cout << "Illumination: " << edof.progress.illuminationPos << "%" << std::endl;
    std::cout << "Decompose: " << edof.progress.decomposePos << "%" << std::endl;
    std::cout << "Depth: " << edof.progress.depthPos << "%" << std::endl;
    std::cout << "Compose: " << edof.progress.composePos << "%" << std::endl;
    std::cout << "Full: " << edof.progress.fullPos << "%" << std::endl;
}

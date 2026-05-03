#include <array>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

const int screenWidth = 1920;
const int screenHeight = 1080;

const int cropWidth = 350;
const int cropHeight = 160;

constexpr std::array<int, 12> cropPosX = {216, 590,  964, 1337, 216, 590,
                                          964, 1337, 216, 590,  964, 1337};
constexpr std::array<int, 12> cropPosY = {260, 260, 260, 260, 530, 530,
                                          530, 530, 799, 799, 799, 799};

std::vector<uint8_t> takeScreenshot() {
    HDC screenDC = GetDC(NULL);
    HDC memoryDC = CreateCompatibleDC(screenDC);
    HBITMAP targetBitmap = CreateCompatibleBitmap(screenDC, screenWidth, screenHeight);
    HGDIOBJ oldObj = SelectObject(memoryDC, targetBitmap);
    BitBlt(memoryDC, 0, 0, screenWidth, screenHeight, screenDC, 0, 0, SRCCOPY);

    BITMAPINFO bmi{};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = screenWidth;
    bmi.bmiHeader.biHeight = -screenHeight;

    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    std::vector<uint8_t> pixels(screenWidth * screenHeight * 4);
    GetDIBits(memoryDC, targetBitmap, 0, screenHeight, pixels.data(), &bmi, DIB_RGB_COLORS);

    // Copy screenshot to clipboard for debugging
    // size_t headerSize = sizeof(BITMAPINFOHEADER);
    // size_t pixelSize = pixels.size();
    // size_t totalSize = headerSize + pixelSize;
    //
    // HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, totalSize);
    //
    // void *dest = GlobalLock(hMem);
    //
    // memcpy(dest, &bmi.bmiHeader, headerSize);
    // memcpy(static_cast<uint8_t *>(dest) + headerSize, pixels.data(), pixelSize);
    //
    // GlobalUnlock(hMem);
    //
    // OpenClipboard(NULL);
    // EmptyClipboard();
    // SetClipboardData(CF_DIB, hMem);
    // CloseClipboard();

    SelectObject(memoryDC, oldObj);
    DeleteObject(targetBitmap);
    DeleteDC(memoryDC);
    ReleaseDC(NULL, screenDC);

    return pixels;
}

std::vector<uint8_t> crop(const std::vector<uint8_t> &src, int srcWidth, int srcHeight, int x,
                          int y, int cropWidth, int cropHeight) {
    std::vector<uint8_t> out(cropWidth * cropHeight * 4);
    for (int row = 0; row < cropHeight; ++row) {
        int srcIdx = ((y + row) * srcWidth + x) * 4;
        int destIdx = row * cropWidth * 4;

        memcpy(&out[destIdx], &src[srcIdx], cropWidth * 4);
    }

    // Copy to clipboard for debugging
    BITMAPINFO bmi{};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = cropWidth;
    bmi.bmiHeader.biHeight = -cropHeight;

    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    size_t headerSize = sizeof(BITMAPINFOHEADER);
    size_t pixelSize = out.size();
    size_t totalSize = headerSize + pixelSize;

    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, totalSize);

    void *dest = GlobalLock(hMem);

    memcpy(dest, &bmi.bmiHeader, headerSize);
    memcpy(static_cast<uint8_t *>(dest) + headerSize, out.data(), pixelSize);

    GlobalUnlock(hMem);

    OpenClipboard(NULL);
    EmptyClipboard();
    SetClipboardData(CF_DIB, hMem);
    CloseClipboard();

    return out;
}

std::vector<uint8_t> crop(const std::vector<uint8_t> &src, int tileNumber) {
    return crop(src, screenWidth, screenHeight, cropPosX.at(tileNumber), cropPosY.at(tileNumber),
                cropWidth, cropHeight);
}

int main() {
    std::cout << "Which tile do you want? ";

    std::string input;
    std::getline(std::cin, input);

    int tileNumber = std::stoi(input);

    std::vector<uint8_t> fullScreenshot = takeScreenshot();
    crop(fullScreenshot, tileNumber);

    std::cout << "Coppied\n";
    return 0;
}

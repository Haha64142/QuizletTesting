#include <iostream>
#include <windows.h>
#include <winuser.h>

int main() {
    // Virtual screen position (all monitors)
    // int topLeftX = GetSystemMetrics(SM_XVIRTUALSCREEN);
    // int topLeftY = GetSystemMetrics(SM_YVIRTUALSCREEN);
    // int width = GetSystemMetrics(SM_CXVIRTUALSCREEN);
    // int height = GetSystemMetrics(SM_CYVIRTUALSCREEN);

    // Primary screen position (single monitor)
    int topLeftX = 0;
    int topLeftY = 0;
    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);
    std::cout << "Top Left: " << topLeftX << ", " << topLeftY << '\n';
    std::cout << "Screen res: " << width << "x" << height << '\n';

    HDC screenDC = GetDC(NULL);
    HDC memoryDC = CreateCompatibleDC(screenDC);
    HBITMAP targetBitmap = CreateCompatibleBitmap(screenDC, width, height);
    HGDIOBJ oldObj = SelectObject(memoryDC, targetBitmap);
    BitBlt(memoryDC, 0, 0, width, height, screenDC, topLeftX, topLeftY, SRCCOPY);

    OpenClipboard(NULL);
    EmptyClipboard();
    SetClipboardData(CF_BITMAP, targetBitmap);
    CloseClipboard();

    SelectObject(memoryDC, oldObj);
    DeleteDC(memoryDC);
    ReleaseDC(NULL, screenDC);
    return 0;
}

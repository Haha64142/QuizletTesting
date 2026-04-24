#include <iostream>
#include <windows.h>

INPUT mouse[2] = {};

int main() {
    mouse[0].type = INPUT_MOUSE;
    mouse[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

    mouse[1].type = INPUT_MOUSE;
    mouse[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

    const UINT START_HOTKEY_ID = 1;
    if (!RegisterHotKey(NULL, START_HOTKEY_ID, MOD_CONTROL | MOD_ALT, 'K')) {
        std::cerr << "Failed to register hotkey: START_HOTKEY";
        return 1;
    }

    const UINT EXIT_HOTKEY_ID = 2;
    if (!RegisterHotKey(NULL, EXIT_HOTKEY_ID, MOD_CONTROL | MOD_ALT, 'C')) {
        std::cerr << "Failed to register hotkey: EXIT_HOTKEY";
        return 1;
    }

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        if (msg.message == WM_HOTKEY) {
            if (msg.wParam == START_HOTKEY_ID) {
                SendInput(2, mouse, sizeof(INPUT));
            } else if (msg.wParam == EXIT_HOTKEY_ID) {
                break;
            }
        }
    }

    UnregisterHotKey(NULL, START_HOTKEY_ID);
    UnregisterHotKey(NULL, EXIT_HOTKEY_ID);
    return 0;
}

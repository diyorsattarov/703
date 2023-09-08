#include <gtest/gtest.h>
#include <iostream>
#include <Windows.h>
#include <spdlog/spdlog.h>

HWND targetWindow = nullptr;
int keypressCount = 0;
DWORD startTime = 0;
HHOOK keyboardHook = NULL;

bool IsTargetWindow(HWND hwnd) {
    return (hwnd == targetWindow);
}

LRESULT CALLBACK KeyboardHook(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        if (wParam == WM_KEYDOWN) {
            HWND activeWindow = GetForegroundWindow();
            if (IsTargetWindow(activeWindow)) {
                keypressCount++;
                if (startTime == 0) {
                    startTime = GetTickCount();
                }
            }
        }
    }
    
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

void MessageLoop() {
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

TEST(MyTests, KeyboardHookTest) {
    spdlog::info("Welcome to spdlog!");
    while (true) {
        targetWindow = nullptr;
        const int windowOpenTimeoutInSeconds = 60;
        const int pollingIntervalMilliseconds = 5000;

        for (int i = 0; i < windowOpenTimeoutInSeconds * 1000 / pollingIntervalMilliseconds; i++) {
            spdlog::info("Waiting for League of Legends to open.");
            targetWindow = FindWindow(nullptr, "League of Legends (TM) Client");
            if (targetWindow != NULL) {
                spdlog::info("League of Legends window is open.");
                break;
            }
            Sleep(pollingIntervalMilliseconds);
        }

        if (targetWindow == NULL) {
            spdlog::error("Timed out waiting for League of Legends window to open");
            return;
        }

        keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHook, NULL, 0);

        if (keyboardHook == NULL) {
            spdlog::error("Failed to set up keyboard hook");
            return;
        }

        bool success = false;
        const int timeoutInSeconds = 20;
        const int expectedKeyPresses = 20;

        MSG msg;
        DWORD startTime = GetTickCount();
        while (true) {
            while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }

            if (GetTickCount() - startTime >= 1000) {
                double apm = static_cast<double>(keypressCount) / 60.0;
                spdlog::info("APM: {}", apm);
                startTime = GetTickCount();
            }

            Sleep(10);

            if (FindWindow(nullptr, "League of Legends (TM) Client") == NULL) {
                spdlog::info("League of Legends window is closed.");
                break;
            }
        }
        UnhookWindowsHookEx(keyboardHook);

        if (!success) {
            spdlog::info("Restarting the test...");
        } else {
            break;
        }
    }
}



int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

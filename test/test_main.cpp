#include <gtest/gtest.h>
#include <iostream>
#include <Windows.h>
#include <spdlog/spdlog.h>

HWND targetWindow = nullptr; // The handle of the target window
int keypressCount = 0;
DWORD startTime = 0;
HHOOK keyboardHook = NULL;

// Define a function to check if the window handle matches the target window
bool IsTargetWindow(HWND hwnd) {
    // You can implement your own logic here to determine if hwnd is the target window
    // For example, compare window title, class name, or process ID
    // Here, we assume you have a valid method to check if hwnd is the target window.
    return (hwnd == targetWindow);
}

LRESULT CALLBACK KeyboardHook(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        if (wParam == WM_KEYDOWN) {
            // Check if the keypress events are from the target window
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

    // Set the target window handle here. You should obtain this handle based on your criteria.
    // Example: targetWindow = FindWindow(nullptr, "Target Window Title");
    targetWindow = FindWindow(nullptr, "League of Legends (TM) Client");

    if (targetWindow == NULL) {
        spdlog::error("Failed to find the target window");
        return;
    }

    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHook, NULL, 0);

    if (keyboardHook == NULL) {
        spdlog::error("Failed to set up keyboard hook");
        return;
    }

    bool success = false;
    const int timeoutInSeconds = 20; // Adjust the timeout as needed
    const int expectedKeyPresses = 20; // Adjust the expected number of keypresses

    // Start the message loop in the main thread
    MSG msg;
    DWORD startTime = GetTickCount();
    while (!success) {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (GetTickCount() - startTime >= 1000) {
            double apm = static_cast<double>(keypressCount) / 60.0;
            spdlog::info("APM: {}", apm);

            if (keypressCount >= expectedKeyPresses) {
                success = true;
            }

            keypressCount = 0;
            startTime = GetTickCount();
        }

        Sleep(10);
    }

    // Cleanup
    UnhookWindowsHookEx(keyboardHook);

    EXPECT_TRUE(success);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

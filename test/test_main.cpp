#include <gtest/gtest.h>
#include <iostream>
#include <Windows.h>
#include <spdlog/spdlog.h>

int keypressCount = 0;
DWORD startTime = 0;
HHOOK keyboardHook = NULL;

LRESULT CALLBACK KeyboardHook(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode >= 0) {
		if (wParam == WM_KEYDOWN) {
			keypressCount++;
			if(startTime == 0) {
				startTime = GetTickCount();
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
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHook, NULL, 0);

    if (keyboardHook == NULL) {
        spdlog::error("Failed to set up keyboard hook");
    }

    bool success = false;
    const int timeoutInSeconds = 10; // Adjust the timeout as needed
    const int expectedKeyPresses = 5; // Adjust the expected number of keypresses

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

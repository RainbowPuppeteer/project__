#include <Windows.h>
#include <ItemGenerator.h>

LRESULT CALLBACK mainWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

#define createwindowbuttoninwindow1 101

bool mainOpened = false;
bool mainRegisteredBefore = false;

const int MAIN_WIDTH = 640;
const int MAIN_HEIGHT = 480;

enum WindowToOpenEnum { none, itemGenerator };

WindowToOpenEnum windowtoopen = none;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShowCmd)
{
    bool endprogram = false;

    MSG msg;
    WNDCLASSEX mainWindow;
    ZeroMemory(&mainWindow, sizeof(WNDCLASSEX));
    mainWindow.cbClsExtra = NULL;
    mainWindow.cbSize = sizeof(WNDCLASSEX);
    mainWindow.cbWndExtra = NULL;
    mainWindow.hbrBackground = (HBRUSH)COLOR_WINDOW;
    mainWindow.hCursor = LoadCursor(NULL, IDC_ARROW);
    mainWindow.hIcon = NULL;
    mainWindow.hIconSm = NULL;
    mainWindow.hInstance = hInst;
    mainWindow.lpfnWndProc = (WNDPROC)mainWindowProc;
    mainWindow.lpszClassName = L"window class 1";
    mainWindow.lpszMenuName = NULL;
    mainWindow.style = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClassEx(&mainWindow))
    {
        int nResult = GetLastError();
        MessageBox(NULL,
            L"Window class creation failed",
            L"Window Class Failed",
            MB_ICONERROR);
    }

    HWND handleformain = CreateWindowEx(NULL,
        mainWindow.lpszClassName,
        L"Window 1",
        WS_OVERLAPPEDWINDOW,
        200,
        150,
        MAIN_WIDTH,
        MAIN_HEIGHT,
        NULL,
        NULL,
        hInst,
        NULL                /* No Window Creation data */
    );

    if (!handleformain)
    {
        int nResult = GetLastError();

        MessageBox(NULL,
            L"Window creation failed",
            L"Window Creation Failed",
            MB_ICONERROR);
    }

    ShowWindow(handleformain, nShowCmd);
    bool endloop = false;
    while (endloop == false) {
        if (GetMessage(&msg, NULL, 0, 0));
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (windowtoopen != none) {
            switch (windowtoopen) {
            case itemGenerator:
                WNDCLASSEX win;
                HWND han;
                createItemGeneratorWindow(win, han, hInst, nShowCmd, NULL);
                break;
            }
            windowtoopen= none;
        }
        if (mainOpened == false)
            endloop = true;

    }
    //MessageBox(NULL,
      //  L"All Windows are closed.  Program will now close.",
      //  L"Message",
      //  MB_ICONINFORMATION);

}


// windows process functions

LRESULT CALLBACK mainWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_CREATE:
        mainOpened = true;
        CreateWindowEx(NULL,
            L"BUTTON",
            L"Open Window 2",
            WS_TABSTOP | WS_VISIBLE |
            WS_CHILD | BS_DEFPUSHBUTTON,
            50,
            220,
            150,
            24,
            hwnd,
            (HMENU)createwindowbuttoninwindow1,
            GetModuleHandle(NULL),
            NULL);
        break;
    case WM_DESTROY:
        mainOpened = false;
        break;
    case WM_COMMAND:
        switch LOWORD(wParam) {
        case createwindowbuttoninwindow1:
            windowtoopen= itemGenerator;
            break;
        }
    }
    return DefWindowProc(hwnd, message, wParam, lParam);

}
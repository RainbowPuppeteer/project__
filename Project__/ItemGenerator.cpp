#include "ItemGenerator.h"

bool itemGeneratorCreatedBefore = false;

void createItemGeneratorWindow(WNDCLASSEX& wc, HWND& hwnd, HINSTANCE& hInst, int nShowCmd, int (*p_func)(char*, int)) {

    ItemGenerator* ig = new ItemGenerator();
    ig->callback = p_func;

    if (itemGeneratorCreatedBefore == false) {
        ZeroMemory(&wc, sizeof(WNDCLASSEX));
        wc.cbClsExtra = NULL;
        wc.cbSize = sizeof(WNDCLASSEX);
        wc.cbWndExtra = NULL;
        wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hIcon = NULL;
        wc.hIconSm = NULL;
        wc.hInstance = hInst;
        wc.lpfnWndProc = (WNDPROC)ItemGeneratorWindowProc;
        wc.lpszClassName = ITEM_GENERATOR_CLASSNAME;
        wc.lpszMenuName = NULL;
        wc.style = CS_HREDRAW | CS_VREDRAW;

        if (!RegisterClassEx(&wc))
        {
            int nResult = GetLastError();
            MessageBox(NULL,
                L"Window class creation failed",
                L"Window Class Failed",
                MB_ICONERROR);
        }
        else
            itemGeneratorCreatedBefore = true;
    }

    hwnd = CreateWindowEx(NULL,
        wc.lpszClassName,
        ITEM_GENERATOR_NAME,
        WS_OVERLAPPEDWINDOW,
        200,
        170,
        IG_WIDTH,
        IG_HEIGHT,
        NULL,
        NULL,
        hInst,
        ig
    );

    if (!hwnd)
    {
        int nResult = GetLastError();

        MessageBox(NULL,
            L"Window creation failed",
            L"Window Creation Failed",
            MB_ICONERROR);

        delete ig;
    } 

    ShowWindow(hwnd, nShowCmd);
}

LRESULT CALLBACK ItemGeneratorWindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    ItemGenerator* ig;

    if (msg == WM_CREATE) {
        CREATESTRUCT* cs = (CREATESTRUCT*)lp;
        ig = (ItemGenerator*)cs->lpCreateParams;
        SetLastError(0);
        if (SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)ig) == 0) {
            if (GetLastError() != 0)
                return FALSE;
        }
    }
    else {
        ig = (ItemGenerator*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    }

    if (ig) {
        switch (msg)
        {
        case WM_COMMAND:
            switch (wp) {
            case IG_GEN:
                wchar_t txt[100];
                GetWindowTextA(ig->hOut, (LPSTR)txt, 100);
                SetWindowTextA(hwnd, (LPSTR)txt);
                break;
            }
            break;
        case WM_CREATE:
            addItemGeneratorControls(hwnd, ig);
            break;
        case WM_DESTROY:
            delete ig;
            break;
        }
    }

    return DefWindowProc(hwnd, msg, wp, lp);
}


void addItemGeneratorControls(HWND hwnd, ItemGenerator* igClass) {

    igClass->hIdEdit = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 370, 40, 100, 20, hwnd, NULL, NULL, NULL);
    igClass->hCountEdit = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 525, 40, 100, 20, hwnd, NULL, NULL, NULL);


    igClass->hGen = CreateWindowW(L"button", L"Generate", WS_VISIBLE | WS_CHILD, 200, 700, 100, 30, hwnd, (HMENU)IG_GEN, NULL, NULL);
    igClass->hOk = CreateWindowW(L"button", L"Ok", WS_VISIBLE | WS_CHILD, 525, 700, 100, 30, hwnd, (HMENU)IG_OK, NULL, NULL);
    if (igClass->callback == NULL) EnableWindow(igClass->hOk, false);
    igClass->hOut = CreateWindowW(L"edit",L"",WS_VISIBLE | WS_CHILD | WS_VSCROLL | ES_AUTOVSCROLL | ES_MULTILINE, 10, 40,300, 650, hwnd, NULL, NULL, NULL);

    CreateWindowW(L"static", L"Commands:", WS_CHILD | WS_VISIBLE, 10, 15, 300, 25, hwnd, NULL, NULL, NULL);
    CreateWindowW(L"static", L"Id:", WS_CHILD | WS_VISIBLE, 320, 40, 50, 20, hwnd, NULL, NULL, NULL);
    CreateWindowW(L"static", L"Count:", WS_CHILD | WS_VISIBLE, 475, 40, 50, 20, hwnd, NULL, NULL, NULL);





}
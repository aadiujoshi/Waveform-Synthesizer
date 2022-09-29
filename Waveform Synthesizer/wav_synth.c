#include <windows.h>
#include <stdlib.h>

LRESULT CALLBACK window_procedure(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hprev, LPSTR args, int ncmdshow){

    WNDCLASSW frame = {0};

    frame.hbrBackground = (HBRUSH)COLOR_WINDOW;
    frame.hCursor = LoadCursor(NULL, IDC_ARROW);
    frame.hInstance = hInst;
    frame.lpszClassName = L"winclass";
    frame.lpfnWndProc = window_procedure;

    if(!RegisterClassW(&frame)){
        //register unsuccessful
        return -1;
    }
    
    CreateWindowW(L"winclass", L"test window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500, NULL, NULL, NULL, NULL);

    MSG msg = {};

    while(GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK window_procedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){

    switch (msg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        
        default:
            DefWindowProcW(hwnd, msg, wp, lp);
            break;
    }

}
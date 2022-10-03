#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define BT_PLAY_SOUND 0xBEEF

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void InitComponents(HWND);
void ImposeWindowLayout(LPARAM);
wchar_t DigitToChar(byte);
wchar_t* UIntToStr(int);

HINSTANCE hInst;

WNDCLASSW WNDC;

HWND root;
HWND lbl_prompt;
HWND bt_playsound;

int WINAPI WinMain(HINSTANCE _hInst, HINSTANCE hprev, LPSTR args, int ncmdshow){

    hInst = _hInst;

    WNDCLASSW WNDC = {0};

    WNDC.lpszClassName = L"wndclass";
    WNDC.hInstance     = _hInst;
    WNDC.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    WNDC.lpfnWndProc   = WndProc;
    WNDC.hCursor       = LoadCursor(0, IDC_ARROW);


    if(!RegisterClassW(&WNDC)){
        //register unsuccessful
        return -1;
    }
    
    root = CreateWindowW(WNDC.lpszClassName, L"Wave Synthesizer", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500, 0, 0, _hInst, 0);

    MSG msg = {};

    while(GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){

    switch (msg) {
        case WM_SIZE:
            ImposeWindowLayout(lp);
            break;

        case WM_CREATE:
            InitComponents(hwnd);
            ImposeWindowLayout(lp);
            break;

        case WM_COMMAND:
            if(LOWORD(wp) == BT_PLAY_SOUND){
                MessageBeep(MB_YESNO);
                printf("playsound\n");
            }

            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;
    }

    return DefWindowProcW(hwnd, msg, wp, lp);
}

void ImposeWindowLayout(LPARAM lp){

    int width = LOWORD(lp);
    int height = HIWORD(lp);

    int r = (rand())%100;

    wchar_t pc = DigitToChar(r);

    LPCWSTR wpc = (LPCWSTR)&pc;

    SetWindowTextW(lbl_prompt, wpc);

    SetWindowPos(lbl_prompt, NULL, (int)(width*0.5), (int)(height*0.5), 50, 20, SWP_SHOWWINDOW);
}

void InitComponents(HWND hwnd){
    lbl_prompt = CreateWindowW(L"static", L"ok", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER , 0, 0, 0, 0, hwnd, NULL, NULL, NULL);
    bt_playsound = CreateWindowW(L"Button", L"playsound", WS_CHILD | WS_VISIBLE, 10, 10, 100, 20, hwnd, (HMENU)BT_PLAY_SOUND, NULL, NULL);
} 

wchar_t* UIntToStr(int x){
    wchar_t* str = (wchar_t*)malloc(sizeof(wchar_t)*11);
    // wchar_t* str[11];

    //start from the end (11-1-i)

    int i = 0;

    return str;

    // while(x){
        
    // }
}

wchar_t DigitToChar(byte x){
    return (wchar_t)(x+48);
}
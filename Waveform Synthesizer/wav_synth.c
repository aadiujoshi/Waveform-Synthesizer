#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void InitLabels();
void ImposeWindowLayout(LPARAM);

HINSTANCE hInst;

HWND root;
HWND label;

int WINAPI WinMain(HINSTANCE _hInst, HINSTANCE hprev, LPSTR args, int ncmdshow){

    hInst = _hInst;

    WNDCLASSW frame = {0};

    frame.hbrBackground = (HBRUSH)COLOR_WINDOW;
    frame.hCursor = LoadCursor(NULL, IDC_ARROW);
    frame.hInstance = _hInst;
    frame.lpszClassName = L"winclass";
    frame.lpfnWndProc = WindowProcedure;

    if(!RegisterClassW(&frame)){
        //register unsuccessful
        return -1;
    }
    
    root = CreateWindowW(L"winclass", L"test window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, 500, 500, NULL, NULL, NULL, NULL);

    MSG msg = {};

    while(GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){

    switch (msg) {
        case WM_SIZE:
            ImposeWindowLayout(lp);
            MessageBeep(MB_ICONERROR);
            break;

        case WM_CREATE:
            InitLabels();
            ImposeWindowLayout(lp);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        
        default:
            DefWindowProcW(hwnd, msg, wp, lp);
            break;
    }

}

void ImposeWindowLayout(LPARAM lp){

    int width = LOWORD(lp);
    int height = HIWORD(lp);
    printf("width: %d, ", width);
    printf("height: %d\n", height);
    
    // printf();

    LPRECT dim;

    GetWindowRect(label, &dim);

    //print lprect values 

    // printf("\twidth: %d, ", (int)(width*0.5));   
    // printf("\theight: %d\n", (int)(height*0.5));

    SetWindowPos(label, NULL, (int)(width*0.5), (int)(height*0.5), 70, 20, SWP_SHOWWINDOW);
}

void InitLabels(){
    printf("initializing labels :)");
    label = CreateWindowW(L"Static", L"test labelfadsfdsafdsafdsafdsa", WS_VISIBLE | WS_CHILD | SS_CENTER, 100, 100, 100, 100, root, NULL, NULL, NULL);
}

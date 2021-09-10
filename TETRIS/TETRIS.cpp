// TETRIS.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "TETRIS.h"

#define MAX_LOADSTRING 100

// Global Variables:
HWND      hWnd;                                 
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
    Global::SetWIDTH(400);
    Global::SetHEIGHT(800);

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TETRIS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    MSG msg = { 0, };

    //START_DEBUG_CONSOLE();                 
    initGraphic(hWnd, 0, 0, Global::GetWIDTH(), Global::GetHEIGHT());  
    Global::SetHWND(hWnd);

    Random::Init(); 
    Time::init();     
    
    //Init Objects Here
    ObjectManager::instantiate(new BackGround(0, 0), 0);
    ObjectManager::instantiate(new CheckCompleteBlocksCollider(0, 0), 3);
    TetrisBlockController::SpawnBlocks(Random::Range(0, 6), Global::GetWIDTH() / 2 - 80, -120);
    


    while (msg.message != WM_QUIT)
    {

        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) == TRUE)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }


        clear(0, 0, 0);

        Time::update(); 
        Input::update();

        ObjectManager::checkCollision();
        TetrisBlockController::BlockControlUpdate();

        ObjectManager::update();
        ObjectManager::clearDead();

        ObjectManager::draw();
        render();

        ObjectManager::checkBlocksComplete();
    }

    //Exit Program
    //STOP_DEBUG_CONSOLE();
    exitGraphic();

    return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TETRIS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TETRIS);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    //윈도우 크기 조정하기
    RECT rt = { 0,0,Global::GetWIDTH(), Global::GetHEIGHT() };

    AdjustWindowRect(&rt, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, FALSE);

    int width = rt.right - rt.left;
    int height = rt.bottom - rt.top;

    hWnd = CreateWindowW(szWindowClass,
        szTitle,
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
        CW_USEDEFAULT,
        0,
        width,   //윈도우 가로크기
        height,  //윈도우 세로크기
        nullptr,
        nullptr,
        hInstance,
        nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        render();

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
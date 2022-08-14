#include <Windows.h>
#include <iostream>
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console") 

// WIN API
// Windows : OS (Operating System)
// Application : 응용 프로그램
// Programming 
// Interface : 함수의 집합체

// #define MAX_LOADSTRING 100

// WCHAR : wchar_t 형태의 typedef 에 대한 별칭입니다.
// 문자열을 표기할 때 L"" 로 표기합니다.
// 보통 2 ~ 4 byte 까지 저장할 수 있습니다.
// WCHAR szTitle[MAX_LOADSTRING]       = L"게임";

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

#define WINSIZEX 1280
#define WINSIZEY 720



/*
HINSTANCE (Instance handle) ★
프로세서에 대한 주소값을 나타냅니다.
*/

int APIENTRY wWinMain(_In_    HINSTANCE hInstance,      // 현재 인스턴스 핸들 
                     _In_opt_ HINSTANCE hPrevInstance,  // 이전 인스턴스 핸들
                     _In_     LPWSTR    lpCmdLine,
                     _In_     int       nCmdShow)
{
    // ★
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    { return FALSE; }

    MSG msg;

    // GetMessage
    // 메시지가 존재한다면 메세지를 가져와 true 를 반환하고
    // 존재하지 않는다면 대기 상태 (while 문을 잠재움)를 가집니다.
    // WM_QUIT 메세지가 들어오게 된다면 false 를 반환합니다.
    while (GetMessage(&msg, nullptr, NULL, NULL))
    {
        // DispatchMessage : 메세지를 WndProc 로 보내주는 역할입니다.
           DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}



ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;
    // 윈도우 클래스를 등록하기 위한 요청서

    
    wcex.cbSize = sizeof(WNDCLASSEX);                         // 윈도우의 크기
    wcex.style          = CS_HREDRAW | CS_VREDRAW;            // 윈도우 스타일
    // 수평 수직으로 창 크기가 변화할 때 윈도우를 다시 그립니다.
    wcex.lpfnWndProc    = WndProc;                            // 메세지 처리함수 설정
    wcex.cbClsExtra     = 0;                                  // 클래스 여분의 메모리
    wcex.cbWndExtra     = 0;                                  // 윈도우 여분의 메모리
    wcex.hInstance      = hInstance;                          // 인스턴스 핸들 설정
    wcex.hIcon          = LoadIcon(nullptr, IDI_APPLICATION); // 큰 아이콘
    wcex.hIconSm        = LoadIcon(nullptr, IDI_ERROR);       // 작은 아이콘
    wcex.hCursor        = LoadCursor(nullptr, IDC_WAIT);      // 마우스 커서 설정ㄴ
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);           // 배경색상
    wcex.lpszMenuName   = nullptr;                            // 메뉴 사용 여부
    wcex.lpszClassName  = L"Window";                          // 등록할 클래스 이름

    return RegisterClassExW(&wcex); // 클래스를 등록합니다.
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   RECT rt = { 0 , 0, WINSIZEX, WINSIZEY };

   // AdjustWindowRect(RECT, WindowStyle, bMenu);
   AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);

   int width = rt.right - rt.left;
   int height = rt.bottom - rt.top;

   HWND hWnd = 
       CreateWindowW(
           L"Window",           // 만들 윈도우 클래스 ★
           L"Game",             // 타이틀 설정 ★
           WS_OVERLAPPEDWINDOW, // 윈도우 스타일
           0,                   // 생성 X 좌표 ★ 
           0,                   // 생성 Y 좌표 ★
           width,               // X 크기  ★
           height,              // Y 크기  ★
           nullptr,             // 부모윈도우
           nullptr,             // 메뉴
           hInstance,           // 인스턴스 핸들
           nullptr);

   if (!hWnd)
   { return FALSE; }
   
   // 윈도우를 보여줍니다. ★
   ShowWindow(hWnd, nCmdShow);


   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // POINT : x , y 를 저장할 수 있는 구조체
    static POINT PlayerPt = { 0 , 0 };
    static POINT MousePt  = { 0 , 0 };
    static bool  bPicked  = false;
    switch (message)
    {
    case WM_MOUSEMOVE :
    {
        // LOWORD(lParam) : 마우스 커서의 작업영역에 x 좌표를 반환합니다. 
        MousePt.x = LOWORD(lParam);
        // HIWORD(lParam) : 마우스 커서의 작업영역에 y 좌표를 반환합니다. 
        MousePt.y = HIWORD(lParam);

        if (bPicked)
        { 
            PlayerPt = MousePt;
            InvalidateRect(hWnd, NULL, true);
        }
        break;
    }
    case WM_LBUTTONDOWN :
    {
        printf("a");
        if (MousePt.x >= PlayerPt.x && MousePt.x <= PlayerPt.x + 80 &&
            MousePt.y >= PlayerPt.y && MousePt.y <= PlayerPt.y + 80)
        { bPicked = true; }
        break;
    }
    case WM_LBUTTONUP :
    {
        if (bPicked) bPicked = false;
        break;
    }
    case WM_KEYDOWN:
    {
        // 맵밖으로 나가는 현상을 막아주세요.
        // 타일을 한칸씩 이동하도록 만들어주세요.
        switch(wParam)
        {
            case 'A' : if(PlayerPt.x > 0)     PlayerPt.x -= 80; break;
            case 'D' : if(PlayerPt.x < 1200)  PlayerPt.x += 80; break;
            case 'W' : if(PlayerPt.y > 0)     PlayerPt.y -= 80; break;
            case 'S' : if(PlayerPt.y < 640)   PlayerPt.y += 80; break;
            case VK_SPACE : break;// 스페이스바 
        }

        // InvalidateRect : 화면을 갱신시킵니다.
        InvalidateRect(hWnd,  // HWND
                       NULL,  // 갱신시킬 좌표를 결정합니다. (전체부분 갱신)
                       true); // 지우고 다시 그릴지 여부

        break;
    }
    case WM_PAINT :
    {
        PAINTSTRUCT ps; // 그리기 도구

        HDC hdc = BeginPaint(hWnd, &ps);

        unsigned tileSize = 80;

        for (int i = 0; i < 9; ++i)
        {
            MoveToEx(hdc, 0,        i * tileSize, NULL);
            LineTo  (hdc, WINSIZEX, i * tileSize      );
        }
        for (int i = 0; i < 16; ++i)
        {
            MoveToEx(hdc, i * tileSize, 0,  NULL);
            LineTo  (hdc, i * tileSize, WINSIZEY);
        }
        
        Rectangle(hdc, PlayerPt.x + 10, PlayerPt.y + 10, PlayerPt.x + 70, PlayerPt.y + 70);

        EndPaint(hWnd, &ps);

        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0); // Quit 메세지를 내보냅니다.
        break;
    default:
        // DefWindowProc : 케이스로 지정하지 않은 메세지 형태를 기본적으로 처리해주는 함수
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

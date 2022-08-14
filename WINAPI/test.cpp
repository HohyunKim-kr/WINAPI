#include <Windows.h>
#include <iostream>
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console") 

// WIN API
// Windows : OS (Operating System)
// Application : ���� ���α׷�
// Programming 
// Interface : �Լ��� ����ü

// #define MAX_LOADSTRING 100

// WCHAR : wchar_t ������ typedef �� ���� ��Ī�Դϴ�.
// ���ڿ��� ǥ���� �� L"" �� ǥ���մϴ�.
// ���� 2 ~ 4 byte ���� ������ �� �ֽ��ϴ�.
// WCHAR szTitle[MAX_LOADSTRING]       = L"����";

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

#define WINSIZEX 1280
#define WINSIZEY 720



/*
HINSTANCE (Instance handle) ��
���μ����� ���� �ּҰ��� ��Ÿ���ϴ�.
*/

int APIENTRY wWinMain(_In_    HINSTANCE hInstance,      // ���� �ν��Ͻ� �ڵ� 
    _In_opt_ HINSTANCE hPrevInstance,  // ���� �ν��Ͻ� �ڵ�
    _In_     LPWSTR    lpCmdLine,
    _In_     int       nCmdShow)
{
    // ��
    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    MSG msg;

    // GetMessage
    // �޽����� �����Ѵٸ� �޼����� ������ true �� ��ȯ�ϰ�
    // �������� �ʴ´ٸ� ��� ���� (while ���� �����)�� �����ϴ�.
    // WM_QUIT �޼����� ������ �ȴٸ� false �� ��ȯ�մϴ�.
    while (GetMessage(&msg, nullptr, NULL, NULL))
    {
        // DispatchMessage : �޼����� WndProc �� �����ִ� �����Դϴ�.
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}



ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;
    // ������ Ŭ������ ����ϱ� ���� ��û��


    wcex.cbSize = sizeof(WNDCLASSEX);                         // �������� ũ��
    wcex.style = CS_HREDRAW | CS_VREDRAW;            // ������ ��Ÿ��
    // ���� �������� â ũ�Ⱑ ��ȭ�� �� �����츦 �ٽ� �׸��ϴ�.
    wcex.lpfnWndProc = WndProc;                            // �޼��� ó���Լ� ����
    wcex.cbClsExtra = 0;                                  // Ŭ���� ������ �޸�
    wcex.cbWndExtra = 0;                                  // ������ ������ �޸�
    wcex.hInstance = hInstance;                          // �ν��Ͻ� �ڵ� ����
    wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION); // ū ������
    wcex.hIconSm = LoadIcon(nullptr, IDI_ERROR);       // ���� ������
    wcex.hCursor = LoadCursor(nullptr, IDC_WAIT);      // ���콺 Ŀ�� ������
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);           // ������
    wcex.lpszMenuName = nullptr;                            // �޴� ��� ����
    wcex.lpszClassName = L"Window";                          // ����� Ŭ���� �̸�

    return RegisterClassExW(&wcex); // Ŭ������ ����մϴ�.
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
            L"Window",           // ���� ������ Ŭ���� ��
            L"Game",             // Ÿ��Ʋ ���� ��
            WS_OVERLAPPEDWINDOW, // ������ ��Ÿ��
            0,                   // ���� X ��ǥ �� 
            0,                   // ���� Y ��ǥ ��
            width,               // X ũ��  ��
            height,              // Y ũ��  ��
            nullptr,             // �θ�������
            nullptr,             // �޴�
            hInstance,           // �ν��Ͻ� �ڵ�
            nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    // �����츦 �����ݴϴ�. ��
    ShowWindow(hWnd, nCmdShow);


    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // POINT : x , y �� ������ �� �ִ� ����ü
    static POINT PlayerPt = { 0 , 0 };
    static POINT PrevPt = { 0, 0 };
    static POINT MousePt = { 0, 0 };
    static bool bPicked = false;

    switch (message)
    {
    case WM_MOUSEMOVE:
    {
        PrevPt = MousePt;

        MousePt.x = LOWORD(lParam); // 0
        MousePt.y = HIWORD(lParam); // 100

        if (bPicked)
        {      
            PlayerPt = MousePt;
            InvalidateRect(hWnd, NULL, false);
        }
        break;
    }
  
    case WM_PAINT:
    {
        PAINTSTRUCT ps; // �׸��� ����

        HDC hdc = BeginPaint(hWnd, &ps);

        // if (bPicked)
        // {
        //     MoveToEx(hdc,MousePt.x,)
        //     LineTo(hdc, MousePt.x, MousePt.y);
        // }
        MoveToEx(hdc, PrevPt.x, PrevPt.y, NULL);
        LineTo(hdc, MousePt.x, MousePt.y);
  
        // if (bPicked)
        // {
        //     LineTo(hdc, MousePt.x, MousePt.y);
        //     InvalidateRect(hWnd, NULL, false);
        // }


  

        
        //for (int i = 0; i < 25; ++i)
        //{
        //    int left = 100 + i % 5 * 70;
        //    int top  = 100 + i / 5 * 70;

        //    if (i / 5 % 2) Ellipse  (hdc, left, top, left + 50, top + 50);
        //    else           Rectangle(hdc, left, top, left + 50, top + 50);
        //}

       
        EndPaint(hWnd, &ps);

        break;
    }
    case WM_LBUTTONDOWN:
    {
            bPicked = true;
        break;
    }
    case WM_LBUTTONUP:
    {
        if (bPicked) bPicked = false;
        break;
    }
    case WM_KEYDOWN:
    {
        // �ʹ����� ������ ������ �����ּ���.
        // Ÿ���� ��ĭ�� �̵��ϵ��� ������ּ���.
        switch (wParam)
        {
        case 'A': if (PlayerPt.x > 0) PlayerPt.x -= 80; break;
        case 'D': if (PlayerPt.x < 1200)PlayerPt.x += 80; break;
        case 'W': if (PlayerPt.y > 0)PlayerPt.y -= 80; break;
        case 'S': if (PlayerPt.y < 640)PlayerPt.y += 80; break;
        case VK_SPACE: InvalidateRect(hWnd, NULL, true); break;
        }

        // InvalidateRect : ȭ���� ���Ž�ŵ�ϴ�.
        InvalidateRect(hWnd,  // HWND
            NULL,  // ���Ž�ų ��ǥ�� �����մϴ�. (��ü�κ� ����)
            true); // ����� �ٽ� �׸��� ����

        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0); // Quit �޼����� �������ϴ�.
        break;
    default:
        // DefWindowProc : ���̽��� �������� ���� �޼��� ���¸� �⺻������ ó�����ִ� �Լ�
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

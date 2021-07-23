// FlappyBird.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "FlappyBird.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
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

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_FLAPPYBIRD, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FLAPPYBIRD));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FLAPPYBIRD));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_FLAPPYBIRD);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_TIMER:
	{
		switch (wParam)
		{
		case Bird_Move_Timer:
		{
			Bird_Time++;
			Move_Bird();

			if (Bird_Wall_Crack()) {
				/*KillTimer(hWnd, Wall_Move_Timer);
				KillTimer(hWnd, Bird_Move_Timer);
				MessageBox(hWnd, _T("GAME OVER"), _T("GAME OVER"), NULL);*/

				Bird.current_Bird.bottom = (Screen_Height + 5 * 2) / 2;
				Bird.current_Bird.top = (Screen_Height - 5 * 2) / 2;
				Bird.current_Bird.left = (Screen_Weight - 5 * 2) / 2;
				Bird.current_Bird.right = (Screen_Weight + 5 * 2) / 2;

				Bird_Time = 0;
				Bird_Velocity = 0;
			}

			PostMessage(hWnd, WM_PAINT, NULL, NULL);
		}
		break;
		case Wall_Move_Timer:
		{
			if (Wall_Length % Length_Node == 0)
				Wall_Move_Velocity += 5;

			Move_Wall();
			PostMessage(hWnd, WM_PAINT, NULL, NULL);
		}
		break;
		}
	}
	break;
	case WM_KEYDOWN:
	{
		//空格键
		if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
			Bird_Velocity = -Gravity * 4 / 6;
			Bird_Time = 0;
		}
		//W向上键
		else if (GetAsyncKeyState(0x57) & 0x8000) {
			Bird_Velocity = -Gravity * 4 / 6;
			Bird_Time = 0;
		}
	}
	break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case ID_32771:
			{
				//设定随机种子
				srand(0);
				//获取设备

				//初始化鸟的位置
				Bird.old_Bird.bottom = (Screen_Height + 5 * 2) / 2;
				Bird.old_Bird.top = (Screen_Height - 5 * 2) / 2;
				Bird.old_Bird.left = (Screen_Weight - 5 * 2) / 2;
				Bird.old_Bird.right = (Screen_Weight + 5 * 2) / 2;

				Bird.current_Bird.bottom = (Screen_Height + 5 * 2) / 2;
				Bird.current_Bird.top = (Screen_Height - 5 * 2) / 2;
				Bird.current_Bird.left = (Screen_Weight - 5 * 2) / 2;
				Bird.current_Bird.right = (Screen_Weight + 5 * 2) / 2;

				Creat_Wall();

				SetTimer(hWnd, Bird_Move_Timer, Bird_Move_Timer_Gap, NULL);
				SetTimer(hWnd, Wall_Move_Timer, Wall_Move_Timer_Gap, NULL);
			}
			break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...

			hdc = GetDC(hWnd);

			Bird_Print(hdc);
			Wall_Print(hdc);

			ReleaseDC(hWnd, hdc);

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

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

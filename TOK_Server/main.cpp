#include <string>
#include <tchar.h>
#ifndef _WINSOCK2API_
#include "Server.h"
#include <Windows.h>
#endif

bool GenerateWindow(LPCWSTR className, LPCWSTR windowTitle, int width, int height, HWND& hWnd);
bool GenerateWindow(LPCWSTR className, LPCWSTR windowTitle, int x, int y, int width, int height, HWND& hWnd);
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
WNDCLASSEX wcex;
enum {INITIAL, WAIT_CONNETION, DATA_SEND, DATA_RECIVE};
Server* server;
LPWSTR state = _T("34324234234");

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd;
	server = new Server;
	//Server s;

	if(GenerateWindow(_T("The Server"), _T("The Server of TOK"), 600, 500, hWnd))
	{
		MSG msg;
		//s.Initialize();

		while(true)
		{
			while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			if(msg.message == WM_QUIT) break;
			else
			{
				//s.Listen();
				//s.Accept();
				//s.Send();
			}
		}
		return msg.wParam;
	}
	UnregisterClass(_T("The Server"), wcex.hInstance);
	delete server;
	return 0;
}

bool GenerateWindow(LPCWSTR className, LPCWSTR windowTitle, int width, int height, HWND& hWnd)
{
	return GenerateWindow(className, windowTitle, (GetSystemMetrics(SM_CXSCREEN)-width)/2,
		(GetSystemMetrics(SM_CYSCREEN)-height)/2, width, height, hWnd);
}

bool GenerateWindow(LPCWSTR className, LPCWSTR windowTitle, int x, int y, int width, int height, HWND& hWnd)
{
	ZeroMemory(&wcex, sizeof(WNDCLASSEX));
	wcex.cbSize = sizeof(wcex);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WindowProc;
	wcex.hInstance = GetModuleHandle(NULL);
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wcex.lpszClassName = className;
	wcex.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

	if(!RegisterClassEx(&wcex))
	{
		return false;
	}

	hWnd = CreateWindow(className, windowTitle, WS_OVERLAPPEDWINDOW, x, y, width, height,
		NULL, NULL, wcex.hInstance, NULL );

	ShowWindow(hWnd, SW_SHOWDEFAULT);
	return true;
	
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rt;
	rt.left = 200;
	rt.right = 400;
	rt.top = 300;
	rt.bottom = 500;
	switch(message)
	{
		case WM_CREATE:
			CreateWindow(_T("button"), _T("서버초기화"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				20,20,100,50,hWnd, (HMENU)INITIAL, NULL,NULL);
			CreateWindow(_T("button"), _T("연결대기"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				20,90,100,50,hWnd, (HMENU)WAIT_CONNETION, NULL,NULL);
			CreateWindow(_T("button"), _T("데이터전송"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				20,160,100,50,hWnd, (HMENU)DATA_SEND, NULL,NULL);
			CreateWindow(_T("button"), _T("데이터수신"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				20,230,100,50,hWnd, (HMENU)DATA_RECIVE, NULL,NULL);
			return 0;
		case WM_DESTROY : 
			PostQuitMessage(0);
			return 0;
		case WM_PAINT :
			hdc = BeginPaint(hWnd, &ps);
			//TextOut(hdc,100,400, _T("Korea"),5);
			DrawText(hdc,state,-1,&rt,DT_CENTER | DT_WORDBREAK);
			EndPaint(hWnd, &ps);
			return 0;
		case WM_LBUTTONDOWN : 
			return 0;
		case WM_COMMAND : 
			switch(LOWORD(wParam))
			{
			case INITIAL :
				if(server->Initialize())
					state = _T("초기화 성공");
				else
					state = _T("초기화 실패");
				InvalidateRect(hWnd, &rt, true);
				break;
			case WAIT_CONNETION : 
				//server->Listen();
				server->Accept();
				state = _T("연결대기 상태");
				InvalidateRect(hWnd, &rt, true);
				break;
			case DATA_SEND : 
				server->Send();
				state = _T("데이터 전송상태");
				InvalidateRect(hWnd, &rt, true);
				break;
			case DATA_RECIVE : 
				break;
			}
			return 0;
		case WM_INPUT : 
			break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}
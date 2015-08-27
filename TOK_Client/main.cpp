#include "Client.h"
#include <Windows.h>
#include <tchar.h>

bool GenerateWindow(LPCWSTR className, LPCWSTR windowTitle, int width, int height, HWND& hWnd);
bool GenerateWindow(LPCWSTR className, LPCWSTR windowTitle, int x, int y, int width, int height, HWND& hWnd);
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
enum {INITIAL, WAIT_CONNETION, DATA_SEND, DATA_RECIVE};
WNDCLASSEX wcex;
Client* client;
LPWSTR state = _T("34324234234");

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd;
	client = new Client;
	if(GenerateWindow(_T("The Client"), _T("The Client of TOK"), 600, 500, hWnd))
	{
		MSG msg;

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
			}
		}
		return msg.wParam;
	}
	UnregisterClass(_T("The Client"), wcex.hInstance);
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
			break;
		case WM_DESTROY : 
			PostQuitMessage(0);
			return 0;
			break;
		case WM_PAINT :
			hdc = BeginPaint(hWnd, &ps);
			DrawText(hdc,state,-1,&rt,DT_CENTER | DT_WORDBREAK);
			EndPaint(hWnd, &ps);
			return 0;
			break;
		case WM_LBUTTONDOWN : 
			return 0;
			break;
		case WM_COMMAND : 
			switch(LOWORD(wParam))
			{
			case INITIAL :
				if(client->Initialize())
					state = _T("초기화 성공");
				else
					state = _T("초기화 실패");
				InvalidateRect(hWnd, &rt, true);
				break;
			case WAIT_CONNETION : 
				//server->Listen();
				client->Connet();
				state = _T("연결대기 상태");
				InvalidateRect(hWnd, &rt, true);
				break;
			case DATA_SEND : 
				//state = _T("데이터 전송상태");
				//InvalidateRect(hWnd, &rt, true);
				break;
			case DATA_RECIVE :
				client->Recive();
				state = _T("데이터수신상태");
				InvalidateRect(hWnd, &rt, true);
				break;
			}
			break;
		case WM_INPUT : 
			break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}
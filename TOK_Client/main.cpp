#undef UNICODE
#undef _UNICODE
#include "Client.h"
#include <Windows.h>
#include "Main_Scene.h"


bool GenerateWindow(const char* className, const char* windowTitle, int width, int height, HWND& hWnd);
bool GenerateWindow(const char* className, const char* windowTitle, int x, int y, int width, int height, HWND& hWnd);
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
enum {INITIAL, WAIT_CONNETION, DATA_SEND, DATA_RECIVE};
WNDCLASSEX wcex;
Client* client;
Manage_Scene* sceneManager;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	AllocConsole(); 
	HWND hWnd;
	sceneManager = new Main_Scene();
	client = new Client();
	
	if(GenerateWindow("The Client", "The Client of TOK", 600, 500, hWnd))
	{
		MSG msg;
		sceneManager->Initialize(hWnd);
		sceneManager->Draw(0.0f);
		if(client->Initialize())
			client->Connet();
		client->SendGameStage(sceneManager->GetSceneNumber());
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
				//std::cout<<userTest.userInfo.allClientReady<<std::endl;
				/*
				if(client->GetReciveMsgState())
				{
					sceneManager->GetUser().SetUserInformation(client->GetUser().GetUserInfomation());
					std::cout<<sceneManager->GetUser().GetAllClientReadyState()<<std::endl;
					client->SetReciveMsgState(false);
				}
				*/
			}
		}
		return msg.wParam;
	}
	UnregisterClass(_T("The Client"), wcex.hInstance);
	delete client;
	delete sceneManager;
	return 0;
}

bool GenerateWindow(const char* className, const char* windowTitle, int width, int height, HWND& hWnd)
{
	return GenerateWindow(className, windowTitle, (GetSystemMetrics(SM_CXSCREEN)-width)/2,
		(GetSystemMetrics(SM_CYSCREEN)-height)/2, width, height, hWnd);
}

bool GenerateWindow(const char* className, const char* windowTitle, int x, int y, int width, int height, HWND& hWnd)
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
			return 0;
			break;
		case WM_DESTROY : 
			PostQuitMessage(0);
			return 0;
			break;
		case WM_PAINT :
			hdc = BeginPaint(hWnd, &ps);
			sceneManager->Draw(0.0f);
			EndPaint(hWnd, &ps);
			return 0;
			break;
		case WM_LBUTTONDOWN : 
			return 0;
			break;
		case WM_COMMAND : 
			switch(LOWORD(wParam))
			{
			case sceneManager->NAME_SEND_BTN:
				//에디터 박스가 글자가 입력되어있는지 확인후 전송
				client->Send(sceneManager->GetEditWindowText().c_str());
				/*
				if(!_tcscmp(sceneManager->GetEditWindowText(),_T("")))
					MessageBox(hWnd, _T("닉네임을 입력해주세요"), _T("Button"), MB_OK);
				else
				{
					/*
					user = new User(obj->GetEditWindowText());
					delete obj;
					obj = new GameExplainScene();
					obj->Initialize(hWnd);
					obj->Draw(0.0f);
					*/
				//*/
				break;
			}
			break;
		case WM_INPUT : 
			break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}
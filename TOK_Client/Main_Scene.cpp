#include "Main_Scene.h"

Main_Scene::Main_Scene() : spriter(NULL), texture(NULL), pFont(NULL), pServerMsgFont(NULL)
{ 
	position.x=0;
	position.y=0;
	position.z=0;

	color = D3DCOLOR_ARGB(255,255,255,255);
	background = "..\\Resource\\main_screen_background.jpg";
	serverMsg="";
	SetSceneNumber(MAIN_SCENE);
}

Main_Scene::Main_Scene(const int width, const int height)
{

}

Main_Scene::~Main_Scene()
{
	if(spriter != NULL)
	{
		spriter->Release();
		spriter=0;
	}
	if(texture != NULL)
	{
		texture->Release();
		texture = 0;
	}
	if(pFont != NULL)
	{
		pFont->Release();
		pFont = 0;
	}
	if(pServerMsgFont != NULL)
	{
		pServerMsgFont->Release();
		pServerMsgFont = 0;
	}
	DestroyWindow(btnWnd);
	DestroyWindow(hEditWnd);
	DestroyWindow(permissionWnd);
}

void Main_Scene::Initialize(const HWND& hWnd)
{
	if(!Manage_Scene::Initialized())
	{
		Manage_Scene::Initialize(hWnd);
	}
	
	if (!SUCCEEDED(D3DXCreateTextureFromFileEx(gDevice->g_pd3dDevice, background.c_str(), GetWindowWidth(), GetWindowHeight(), 1, NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, NULL, NULL, &texture)))
	{
		MessageBox(NULL,_T("Image Load error"),NULL,NULL);
	}
	
	if (!SUCCEEDED(D3DXCreateSprite(gDevice->g_pd3dDevice, &spriter)))
	{
		MessageBox(NULL,_T("Error on generating spriter"),NULL,NULL);
	}

	if (!SUCCEEDED(D3DXCreateFont(gDevice->g_pd3dDevice, 30,15, 255, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("¸¼Àº °íµñ"), &pFont)))
	{
		MessageBox(NULL, _T("Load Error of Font from the System"), NULL, NULL);
	}

	if (!SUCCEEDED(D3DXCreateFont(gDevice->g_pd3dDevice, 30,15, 255, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("¸¼Àº °íµñ"), &pServerMsgFont)))
	{
		MessageBox(NULL, _T("Load Error of Font from the System"), NULL, NULL);
	}

	if (!SUCCEEDED(hEditWnd = CreateWindow(_T("edit"), _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 200, 350, 225, 25, hWnd, (HMENU) EDITBTN_ID, NULL, NULL)))
	{
		MessageBox(NULL, _T("Generation error of Edit Box"), NULL, NULL);
	}

	
	if (!SUCCEEDED(btnWnd = CreateWindow(_T("button"),_T("È®ÀÎ"),WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 450,350,100,25,hWnd,(HMENU)NAME_SEND_BTN,NULL,NULL)))
	{
		MessageBox(NULL, _T("Generation error of Button"), NULL, NULL);
	}

	if (!SUCCEEDED(permissionWnd = CreateWindow(_T("button"),_T("°ÔÀÓ½ÃÀÛ"),WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 250,400,100,25,hWnd,(HMENU)ACCESS_PERMISSION_BTN,NULL,NULL)))
	{
		MessageBox(NULL, _T("Generation error of Button"), NULL, NULL);
	}
	ShowWindow(permissionWnd, SW_HIDE);
}

void Main_Scene::Draw(const float gameTime)
{
	gDevice->Clear(D3DCOLOR_XRGB(0,0,255));
	gDevice->Begin();

	RECT rcSrcRect;
	rcSrcRect.left = 0;
	rcSrcRect.right = GetWindowWidth();
	rcSrcRect.bottom = GetWindowHeight();
	rcSrcRect.top = 0;
	

	RECT textRect = {100,343,-1,-1};
	RECT serverTextRect = {200,450,-1,-1};
    if(spriter && texture)
	{
		spriter->Begin(D3DXSPRITE_ALPHABLEND);
		spriter->Draw(texture,&rcSrcRect,NULL, &position, color);
		//spriter->Draw(NULL, &button, NULL, NULL, D3DCOLOR_ARGB(255,0,255,0));
		if(pFont)
			pFont->DrawText(spriter, _T("´Ð³×ÀÓ"), -1, &textRect, DT_NOCLIP, D3DXCOLOR(1,1,1,1));

		if(pServerMsgFont)
			pServerMsgFont->DrawText(spriter, serverMsg.c_str(), -1, &serverTextRect, DT_NOCLIP, D3DXCOLOR(1,1,1,1));
		spriter->End();
	}

	gDevice->End();
	gDevice->Present();
	
}

std::string Main_Scene::GetEditWindowText()
{
	char str[128];
	GetWindowText(hEditWnd, str, 128);
	return std::string(str);
}

void Main_Scene::SetWindowVisible()
{
	ShowWindow(permissionWnd, SW_SHOW);
}

void Main_Scene::SetServerMessage(const std::string msg)
{
	serverMsg = msg;
}
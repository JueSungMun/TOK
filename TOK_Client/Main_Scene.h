/*
	사용자가 본 게임전에 보는 첫화면.

*/
#undef UNICODE
#undef _UNICODE
#include "Manage_Scene.h"

class Main_Scene : public Manage_Scene
{
private:
	HWND btnWnd;
	HWND permissionWnd;
	HWND hEditWnd;
	D3DXVECTOR3 position;
	D3DCOLOR color;
	LPD3DXSPRITE spriter;
	LPD3DXFONT pFont;
	LPD3DXFONT pServerMsgFont;
	LPDIRECT3DTEXTURE9 texture;
	std::string background;
	std::string serverMsg;
public:
	Main_Scene();
	Main_Scene(const int windth, const int height);
	virtual ~Main_Scene();
	virtual void Initialize(const HWND& hWnd);
	virtual void Draw(const float gameTime);
	virtual std::string GetEditWindowText();
	virtual void SetServerMessage(const std::string msg);
	void SetWindowVisible();
};
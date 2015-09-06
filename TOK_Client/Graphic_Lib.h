/*
	�׷��� ��ġ ���� �� ������ �ڵ��� �̿��� �ʱ�ȭ

	1. �׸��� �׸��� �������̽� ����
*/
#undef UNICODE
#undef _UNICODE
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

class Graphic_Lib
{
private:
	LPDIRECT3D9             g_pD3D;					 // Used to create the D3DDevice
	HRESULT InitD3D( HWND hWnd );
public:
	Graphic_Lib();
	~Graphic_Lib();
	LPDIRECT3DDEVICE9       g_pd3dDevice;			 // rendering device
	bool Initilize(HWND hWnd);
	void Clear (D3DCOLOR color);
	void Begin();
	void End();
	void Present();
};
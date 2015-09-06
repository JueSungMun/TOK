#include "HeaderFiles.h"

LPDIRECT3D9             g_pD3D       = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9       renderDevice = NULL; // Our rendering device
LPD3DXSPRITE sprite;
WNDCLASSEX createWin;
HWND hwnd;
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
HRESULT InitD3D( HWND hWnd );

LPDIRECT3DTEXTURE9 bgTexture = NULL;
Objects *bg;

void LoadData(void)
{
	RECT bgrect = { 0,0,700,700 };
	D3DXVECTOR3 pos,cent;
	pos.x=0;
	pos.y=0;
	cent.x= .0f;
	cent.y= .0f;
	cent.z= .0f;

	bg = new Objects;
	bg->setCenter(cent);
	bg->setPosition(pos);
	bg->setSource(bgrect);
	bg->setTexture(renderDevice, IMG_BG);
	bg->setVisible(TRUE);
}

void Initilize(void)
{	
	// Register the window class
	WNDCLASSEX createWin = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		_T("The Throne of The Kingdom"), NULL };
	RegisterClassEx( &createWin );

	// Create the application's window
	hwnd = CreateWindow( _T("The Throne of The Kingdom"), _T("TOK"),
		WS_OVERLAPPEDWINDOW, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
		NULL, NULL, createWin.hInstance, NULL );
	
	InitD3D(hwnd);
	if(!SUCCEEDED(D3DXCreateSprite(renderDevice, &sprite)))
	{
		MessageBox(NULL, _T("Error of create sprite"), NULL, NULL);
	}
	//ZeroMemory(&bg, sizeof(Objects));
	//ZeroMemory(&om, sizeof(ObjectManager));

	LoadData();

	// Show the window
	ShowWindow( hwnd, SW_SHOWDEFAULT );
	UpdateWindow( hwnd );
}

//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
HRESULT InitD3D( HWND hWnd )
{
	g_pD3D = Direct3DCreate9( D3D_SDK_VERSION );
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof(d3dpp) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.hDeviceWindow = hWnd;

	g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,	D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &renderDevice );

    return S_OK;
}

//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Cleanup()
{
	if (sprite != NULL)
		sprite->Release();
	if( renderDevice != NULL ) 
		renderDevice->Release();
	if( g_pD3D != NULL )       
		g_pD3D->Release();
	if( bg != NULL)
		delete bg;
}

//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID Render()
{
	renderDevice->Clear(0,NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0);
	renderDevice->BeginScene();
	if(bg->getTexture())
	{
		sprite->Begin(D3DXSPRITE_ALPHABLEND);
		sprite->Draw(bg->getTexture(), bg->getSource(), bg->getCenter(), bg->getPosition(), 0xFFFFFFFF);
		sprite->End();
		// End the scene
	}
	renderDevice->EndScene();
	renderDevice->Present( NULL, NULL, NULL, NULL );
}

//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
    case WM_DESTROY:
        Cleanup();
        PostQuitMessage( 0 );
        return 0;
    }

    return DefWindowProc( hwnd, msg, wParam, lParam );
}

//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
	Initilize();
	//AllocConsole(); //콘솔창 소환
	MSG msg;
	ZeroMemory( &msg, sizeof(msg) );
	while( msg.message!=WM_QUIT )
	{
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			Render();	
		}
	}

    UnregisterClass( _T("T_O_K"), createWin.hInstance );
    return 0;
}
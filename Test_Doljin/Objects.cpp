#include "HeaderFiles.h"

Objects::Objects(void) : Texture(NULL)
{
}

Objects::~Objects(void)
{
}
void Objects::initObjects(RECT &inputX)
{
	Source.top= inputX.top;
	Source.bottom = inputX.bottom;
	Source.left = inputX.left;
	Source.right = inputX.right;
	Visible = TRUE;
	direction = TRUE;
	Position.x = 1;
	Position.y = 0;
	Position.z = 0;
	Center.x = 0;
	Center.y = 0;
	Center.z = 0;
	test_value =0;

	//Position.z = 1;
	ani_inverval =0;
}

int Objects::getID()
{
	return id;
}

LPDIRECT3DTEXTURE9& Objects::getTexture()
{
	return Texture;
}

BOOL Objects::getVisible() const
{
	return Visible;
}

RECT* Objects::getSource()
{
	return &Source;
}

D3DXVECTOR3* Objects::getPosition() 
{
	return &Position;
}

const D3DXVECTOR3* Objects::getCenter()
{
	return &Center;
}

void Objects::setSource(RECT rct)
{
	Source.bottom = rct.bottom;
	Source.top = rct.top;
	Source.left = rct.left;
	Source.right = rct.right;
}

void Objects::setPosition(D3DXVECTOR3 pos)
{
	Position.x = pos.x;
	Position.y = pos.y;
	Position.z = 0;
}

void Objects::setCenter(D3DXVECTOR3 cent)
{
	Center.x = cent.x;
	Center.y = cent.y;
	Center.z = cent.z;
}

void Objects::setVisible(BOOL isVisible)
{
	Visible = isVisible;
}
void Objects::setTexture(LPDIRECT3DDEVICE9 device, LPCWSTR img)
{
	if(!SUCCEEDED(D3DXCreateTextureFromFileEx( device, img, 
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, NULL, NULL, &Texture)))
	{
		MessageBox(NULL, _T("Image Load Error"), NULL, NULL);
	}
}
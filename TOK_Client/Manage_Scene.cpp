#include "Manage_Scene.h"

Manage_Scene::Manage_Scene() : sceneNumber(0) , isInitialed(false), windowWidth(600), windowHeight(700), isGameOver (false)
{
}

Manage_Scene::Manage_Scene(const Manage_Scene& _ms) : sceneNumber(_ms.sceneNumber), windowHeight(_ms.windowHeight)
	, windowWidth(_ms.windowWidth), isGameOver(_ms.isGameOver), isInitialed(_ms.isInitialed), gDevice(_ms.gDevice)//, client(_ms.client)
{
	/*
	this->sceneNumber = _ms.sceneNumber;
	this->windowWidth = _ms.windowWidth;
	this->windowHeight = _ms.windowHeight;
	this->isGameOver = _ms.isGameOver;
	this->isInitialed = _ms.isInitialed;
	this->gDevice = _ms.gDevice;
	*/
}

Manage_Scene::~Manage_Scene()
{
	if(gDevice)
	{
		delete gDevice;
		isInitialed = false;
		gDevice = NULL;
	}

	/*
	if(client)
	{
		delete client;
		isInitialed=false;
		client = NULL;
	}
	*/
}
int Manage_Scene::GetSceneNumber()
{
	return sceneNumber;
}

void Manage_Scene::SetSceneNumber(const int num)
{
	sceneNumber = num;
}

void Manage_Scene::Initialize(const HWND& hWnd)
{
	gDevice = new Graphic_Lib();
	
	if(!gDevice->Initilize(hWnd))
	{
		isInitialed = false;
	}
	else
	{
		//isInitialed = client->Initialize();
		isInitialed = true;
	}
	
}

void Manage_Scene::Draw(const float gameTime)
{
	gDevice->Clear(D3DCOLOR_XRGB(0,0,255));
	gDevice->Begin();


	gDevice->End();
	gDevice->Present();
}

void Manage_Scene::Draw(const float gameTime, const User& user)
{
	gDevice->Clear(D3DCOLOR_XRGB(0,0,255));
	gDevice->Begin();


	gDevice->End();
	gDevice->Present();
}

bool Manage_Scene::Initialized()
{
	return isInitialed;
}

std::string Manage_Scene::GetEditWindowText()
{
	return std::string();
}

void Manage_Scene::SetServerMessage(const std::string msg)
{

}

int Manage_Scene::GetWindowWidth()
{
	return windowWidth;
}

int Manage_Scene::GetWindowHeight()
{
	return windowHeight;
}

void Manage_Scene::SetGameOver(const bool state)
{
	isGameOver = state;
}

bool Manage_Scene::GetGameState()
{
	return isGameOver;
}

User& Manage_Scene::GetUser()
{
	return user;
}

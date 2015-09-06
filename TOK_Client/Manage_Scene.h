/*
	Scene�� �����ϱ� ���� �������.
	
	1. Scene���� �̵��� Scene��ȣ�� �̿��Ͽ� ����
	2. �׷��� ��ġ�� �ʱ�ȭ
	3. Draw�� �����ϵ��� �������̽� ����

	4. ���� �������̽� �����ؾ���.
*/
#undef UNICODE
#undef _UNICODE
#ifndef MANAGE_SCENE_H
#define MANAGE_SCENE_H
#pragma once
//#include "Client.h"
#include "Graphic_Lib.h"
#include "User.h"
#include <tchar.h>
//#define BUTTON_ID 0
//#define EDITBTN_ID 100

class Manage_Scene
{
private:
	int windowWidth;
	int windowHeight;
	int sceneNumber;
	bool isGameOver;
	bool isInitialed;
	User user;
public:
	//Client* client;	
	Graphic_Lib *gDevice;
	enum {NAME_SEND_BTN=10, ACCESS_PERMISSION_BTN, EDITBTN_ID=100};								//������ �а��� ���(enum hack)
	enum {MAIN_SCENE=1, GAME_SCENE, GAME_RESULT_SCENE};
	Manage_Scene();
	Manage_Scene(const Manage_Scene&);
	virtual ~Manage_Scene();
	int GetSceneNumber();
	void SetSceneNumber(const int num);
	int GetWindowWidth();
	int GetWindowHeight();
	bool Initialized();
	void SetGameOver(const bool state);
	bool GetGameState();
	User& GetUser();
	virtual void Initialize(const HWND& hWnd);
	virtual void Draw(const float gameTime);
	virtual void Draw(const float gameTime, const User& user);
	virtual std::string GetEditWindowText();							//Main_Scene���� EditBox�� ���ڿ��� �ޱ����� �Լ�
	virtual	void SetServerMessage(const std::string msg);
};

#endif
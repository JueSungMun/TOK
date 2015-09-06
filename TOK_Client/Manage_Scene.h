/*
	Scene을 관리하기 위한 헤더파일.
	
	1. Scene간의 이동을 Scene번호를 이용하여 제어
	2. 그래픽 장치를 초기화
	3. Draw를 구현하도록 인터페이스 제공

	4. 음악 인터페이스 구현해야함.
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
	enum {NAME_SEND_BTN=10, ACCESS_PERMISSION_BTN, EDITBTN_ID=100};								//나열자 둔갑술 기법(enum hack)
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
	virtual std::string GetEditWindowText();							//Main_Scene에서 EditBox의 문자열을 받기위한 함수
	virtual	void SetServerMessage(const std::string msg);
};

#endif
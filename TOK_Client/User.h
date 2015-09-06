#undef UNICODE
#undef _UNICODE
#include <iostream>
#pragma once

class User
{
private:
	typedef struct USER_INFORMATION
	{
		std::string userName;
		bool allClientReady;
	};


public:
	USER_INFORMATION userInfo;

	enum {GAME_CLEAR=10, USER_DIE, PLAYING_GAME};
	User();
	~User();
	const USER_INFORMATION GetUserInfomation();
	void SetUserInformation(const USER_INFORMATION& user);
	void SetAllClientReadyState(const bool state);
	const bool GetAllClientReadyState();
};

static User userTest;
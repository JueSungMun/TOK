#include "User.h"

User::User()
{
	memset(&userInfo, 0, sizeof(userInfo));
}

User::~User()
{
}

const User::USER_INFORMATION User::GetUserInfomation()
{
	return userInfo;
};

void User::SetUserInformation(const USER_INFORMATION& user)
{
	userInfo.userName = user.userName;
	userInfo.allClientReady = user.allClientReady;
}

void User::SetAllClientReadyState(const bool state)
{
	userInfo.allClientReady = state;
}

const bool User::GetAllClientReadyState()
{
	return userInfo.allClientReady;
}
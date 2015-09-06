#pragma once
#undef UNICODE
#undef _UNICODE
#include <WinSock2.h>
#include <process.h>
#include "Protocol.h"
#include "User.h"
#pragma comment(lib,"ws2_32.lib")

//char message[30];

class Client : private Protocol
{
private:
	WSADATA wsaData;
	SOCKET hSocket;
	SOCKADDR_IN servAddr;
	int strLen;
	bool reciveMsged;
	HANDLE recThread;
public:
	Client();
	~Client();
	bool Initialize();
	void Connet();
	void Recive(SOCKET* arg);
	void Send(const char* nickName);
	void SendGameStage(const int state);
	void SetReciveMsgState(const bool state);
	const bool GetReciveMsgState();
	static unsigned WINAPI ReciveMessageThread(void* arg);
};

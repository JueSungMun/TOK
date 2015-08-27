#include <WinSock2.h>
#include <tchar.h>
#pragma comment(lib,"ws2_32.lib")

//char message[30];

class Client
{
private:
	WSADATA wsaData;
	SOCKET hSocket;
	SOCKADDR_IN servAddr;
	int strLen;

public:
	Client();
	~Client();
	bool Initialize();
	void Connet();
	void Recive();
};
#include <WinSock2.h>
#include <tchar.h>
#pragma comment(lib, "ws2_32.lib")

class Server
{
private:
	WSADATA wsaData;		//윈도우 소켓버전에 따른 라이브러리 정보를 담고있는 구조체
	SOCKET servSock;
	SOCKET clntSock;
	SOCKADDR_IN servAddr;
	SOCKADDR_IN clntAddr;
	int szClntAddr;
	int port;
	//const char* message1 = "Hello World!";
	//bool GenerateSocket(int af, int type, int protocol);
	//bool Bind(SOCKET s, const struct sockaddr* name, int namelen);

public:
	Server();
	~Server();
	bool Initialize();
	void Listen();
	void Accept();
	void Send();//(const char* message);
};
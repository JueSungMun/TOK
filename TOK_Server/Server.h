#undef UNICODE
#undef _UNICODE
#include <WinSock2.h>
#include <process.h>
#include "Protocol.h"
#include <vector>
#include <string>
#include <mutex>
#pragma comment(lib, "ws2_32.lib")

class Server : private Protocol
{
private:
	typedef struct GameState
	{
		bool EVERY_CLIENT_READYED;
		int MAX_USER_NUMBER;
		int ACCESSED_USER_NUMBER;
		int CURRENT_GAME_SCENE;
	};
	typedef struct UserState
	{
		SOCKET socket;
		std::string nickname;
	};
	enum {MAX_CLNT = 10, PORT = 9190};
	enum {MAIN_SCENE=1, GAME_SCENE, GAME_RESULT_SCENE};
	WSADATA wsaData;		//윈도우 소켓버전에 따른 라이브러리 정보를 담고있는 구조체
	SOCKET servSock;
	SOCKET clntSock;
	//SOCKET* clntSockList;
	SOCKADDR_IN servAddr;
	SOCKADDR_IN clntAddr;
	int szClntAddr;
	int clntCount;
	HANDLE recThread;
	HANDLE sendThread;
	HANDLE hMutex;
	Message packet;
	GameState* gameState;
	std::vector<UserState>* clntSockList;
//	mutex 
public:
	Server();
	~Server();
	const bool Initialize();
	const void InitializeGameState(int maxUserNum);
	void Accept();
	static unsigned WINAPI ReciveMessageThread(void* arg);
	static unsigned WINAPI SendMessageThread(void* arg);
	void ReciveMessage(SOCKET* socket);
	void SendMessageToClient(SOCKET* msg);
};
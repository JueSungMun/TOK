#include "Server.h"

Server::Server() : servSock(0), clntSock(0),szClntAddr(0), recThread(NULL), sendThread(NULL),clntCount(0), hMutex(NULL)
{
	//clntSockList = new SOCKET[MAX_CLNT];
	memset(&packet, 0,sizeof(packet));
	clntSockList = new std::vector<UserState>;
	gameState = new GameState;
}

Server::~Server()
{
	closesocket(clntSock);
	closesocket(servSock);
	WaitForSingleObject(recThread, INFINITE);
	WaitForSingleObject(sendThread,INFINITE);
	CloseHandle(recThread);
	CloseHandle(sendThread);
	CloseHandle(hMutex);
	delete clntSockList;
	delete gameState;
	WSACleanup();
}

const bool Server::Initialize()
{
	if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0) //네트워크 라이브러리 초기화
		return false;

	servSock = socket(PF_INET, SOCK_STREAM, 0);	//TCP 서버 소켓 생성
	if(servSock == INVALID_SOCKET)
		return false;

	hMutex = CreateMutex(NULL, FALSE, NULL);
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(PORT);			

	InitializeGameState(2);
	if(bind(servSock, reinterpret_cast<SOCKADDR*>(&servAddr), sizeof(servAddr))==SOCKET_ERROR)
		return false;

	if(listen(servSock, 5) == SOCKET_ERROR)
		return false;	
	return true;
}
	
const void Server::InitializeGameState(int maxUserNum)
{
	memset(gameState, 0, sizeof(*gameState));
	gameState->MAX_USER_NUMBER = maxUserNum;
}

void Server::Accept()
{
	szClntAddr = sizeof(clntAddr);
	clntSock = accept(servSock, reinterpret_cast<SOCKADDR*>(&clntAddr), &szClntAddr);
	if(clntSock == INVALID_SOCKET)
		MessageBox(NULL, "accept() error", NULL, NULL);
	//clntSockList[clntCount++] = clntSock;
	UserState user;
	user.socket = clntSock;
	user.nickname = "";
	clntSockList->push_back(user);
	gameState->ACCESSED_USER_NUMBER++;
	recThread = (HANDLE) _beginthreadex(NULL, 0, ReciveMessageThread, this, 0, NULL);
	//sendThread = (HANDLE) _beginthreadex(NULL, 0, SendMessageThread, (void*)&clntSock, 0, NULL);
	
}

unsigned WINAPI Server::ReciveMessageThread(void* arg)
{
	
	Server* server = (Server*)arg;
	//server->ReciveMessage((SOCKET*)arg);
	server->ReciveMessage(0);
	/*
	SOCKET hClntSock = *(SOCKET*)arg;
	char recvMsg[150]={};
	int strLen;
	while(1)
	{
		Message packet;
		strLen = recv(hClntSock, recvMsg, sizeof(recvMsg),0);
		if(strLen == -1)
			break;
		std::string msgStr(recvMsg);
		server->TranslateProtocol(msgStr, packet);
		if(packet.type == BROADCAST)
		{
			//다른 클라이언트에게 데이터 정보 전달
		}
		else if(packet.type == NOTIFICATION)
		{
			if(packet.protocol == SEND_GAMESTAGE)
			{
				gameState->CURRENT_GAME_SCENE = atoi(packet.message);
				MessageBox(NULL, packet.message, NULL, NULL);
			}

			if(packet.protocol == SEND_NICKNAME)
			{
				for(int i=0; i<clntSockList->size(); i++)
				{
					if(clntSockList->at(i).socket == hClntSock)
					{
						clntSockList->at(i).nickname = packet.message;
					}
				}
			}
		}
	}
	*/
	//ReciveMessage((SOCKET*)arg);
	return 0;
}

void Server::ReciveMessage(SOCKET* socket)
{
	//SOCKET hClntSock = *socket;
	char recvMsg[150]={};
	int strLen;
	while(1)
	{
		strLen = recv(clntSock, recvMsg, sizeof(recvMsg),0);
		if(strLen == -1)
			break;
		std::string msgStr(recvMsg);
		TranslateProtocol(msgStr, packet);
		if(packet.type == BROADCAST)
		{
			//다른 클라이언트에게 데이터 정보 전달
		}
		else if(packet.type == NOTIFICATION)
		{
			if(packet.protocol == SEND_GAMESTAGE)
			{
				gameState->CURRENT_GAME_SCENE = atoi(packet.message);
				MessageBox(NULL, packet.message, NULL, NULL);
			}

			if(packet.protocol == SEND_NICKNAME)
			{
				for(int i=0; i<clntSockList->size(); i++)
				{
					if(clntSockList->at(i).socket == clntSock)
					{
						clntSockList->at(i).nickname = packet.message;
					}
				}
			}
		}
	}
}

unsigned WINAPI Server::SendMessageThread(void* arg)
{
	Server* server = (Server*)arg;
	server->SendMessageToClient((SOCKET*)arg);
	return 0;
}

void Server::SendMessageToClient(SOCKET* msg)
{
	SOCKET hClntSock = *msg;
	std::string temp;
	char sendBuf[150]={};
	int strLen;
	temp = MakeTheProtocol(BROADCAST, SEND_MAXIMUM_USERNUM, std::to_string(gameState->MAX_USER_NUMBER).c_str());
	strcpy_s(sendBuf, temp.c_str());
	send(hClntSock, sendBuf, sizeof(sendBuf),0);
	while(gameState->CURRENT_GAME_SCENE == MAIN_SCENE)
	{
		if(!gameState->EVERY_CLIENT_READYED)
		{
			temp = MakeTheProtocol(BROADCAST, SEND_ACCESS_USER_NUM, std::to_string(gameState->ACCESSED_USER_NUMBER).c_str());
			strcpy_s(sendBuf, temp.c_str());
			send(hClntSock, sendBuf, sizeof(sendBuf),0);
		}
		else
		{
			temp = MakeTheProtocol(BROADCAST, SEND_READYSTATE, std::to_string(gameState->EVERY_CLIENT_READYED).c_str());
			strcpy_s(sendBuf, temp.c_str());
			send(hClntSock, sendBuf, sizeof(sendBuf),0);
		}
	}
}

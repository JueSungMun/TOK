#include "Client.h"

Client::Client() : recThread(NULL) , reciveMsged(false), strLen(0), hSocket(0)
{
	//memset(&clientInf,0,sizeof(clientInf));
	//userTest = new User;
}

Client::~Client()
{
	closesocket(hSocket);
	WaitForSingleObject(recThread,INFINITE);
	CloseHandle(recThread);
	WSACleanup();
}

bool Client::Initialize()
{
	if(WSAStartup(MAKEWORD(2,2), &wsaData) !=0)
		return false;
	
	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	if(hSocket == INVALID_SOCKET)
		return false;

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servAddr.sin_port = htons(9190);
	return true;
}

void Client::Connet()
{
	if(connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		MessageBox(NULL, "Connet() error", NULL, NULL);

	//sendThread = (HANDLE) _beginthreadex(NULL, 0, SendMessageThread, (void*)&hSocket, 0, NULL);
	recThread = (HANDLE) _beginthreadex(NULL, 0, ReciveMessageThread, (void*)&hSocket, 0, NULL);
}

void Client::Recive(SOCKET* arg)
{
	SOCKET hConnectedSock = *arg;
	Message msg;
	char buf[150]={};
	strLen = recv(hConnectedSock, buf, sizeof(buf), 0);
	if(strLen == -1)
	{
		//break;
	}
	else
	{
		memset(&msg, 0, sizeof(msg));
		TranslateProtocol(std::string(buf),msg); 
		if (msg.protocol == SEND_READYSTATE)
		{
			//clientInf.allClientReady = atoi(buf);
			int temp = atoi(msg.message);
			if(temp == 1)
				userTest.SetAllClientReadyState(true);
				//user->userInfo.allClientReady = true;
			else 
				//user->userInfo.allClientReady = false;
				userTest.SetAllClientReadyState(false);
			MessageBox(NULL, msg.message, NULL, NULL);
		}
	}
	reciveMsged = true;
}

void Client::Send(const char* nickName)
{
	char buf[150];
	std::string str = MakeTheProtocol(NOTIFICATION, SEND_NICKNAME, nickName);
	strcpy_s(buf, str.c_str());
	send(hSocket, buf, sizeof(buf)-1,0);
}

void Client::SendGameStage(const int state)
{
	char buf[150];
	std::string str = MakeTheProtocol(NOTIFICATION, SEND_GAMESTAGE, std::to_string(state).c_str());
	strcpy_s(buf, str.c_str());
	send(hSocket, buf, sizeof(buf)-1,0);
}

unsigned WINAPI Client::ReciveMessageThread(void* arg)
{
	Client* client = (Client*)arg;
	client->Recive((SOCKET*)arg);
	return 0;
	//BroadCastMessage("");
}

void Client::SetReciveMsgState(const bool state)
{
	reciveMsged = state;
}

const bool Client::GetReciveMsgState()
{
	return reciveMsged;
}

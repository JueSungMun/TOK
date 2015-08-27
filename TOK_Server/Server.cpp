#include "Server.h"

Server::Server() : servSock(0), clntSock(0), port(9190), szClntAddr(0)
{

}

Server::~Server()
{
	closesocket(clntSock);
	closesocket(servSock);
	WSACleanup();
}

bool Server::Initialize()
{
	if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
		return false;
	servSock = socket(PF_INET, SOCK_STREAM, 0);
	if(servSock == INVALID_SOCKET)
		return false;
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(port);				//port번호 입력받거나 초기화하는 부분 고치기

	if(bind(servSock, (SOCKADDR*)&servAddr, sizeof(servAddr))==SOCKET_ERROR)
		return false;
	Listen();
	return true;
}

void Server::Listen()
{
	if(listen(servSock, 5) == SOCKET_ERROR)
		MessageBox(NULL, _T("listen() error"), NULL, NULL);
}


void Server::Accept()
{
	szClntAddr = sizeof(clntAddr);
	clntSock = accept(servSock, reinterpret_cast<SOCKADDR*>(&clntAddr), &szClntAddr);
	if(clntSock == INVALID_SOCKET)
		MessageBox(NULL, _T("accept() error"), NULL, NULL);
}

void Server::Send()//(const char* message)
{
	char message[] = "HelloWorld!";
	send(clntSock, message, sizeof(message), 0);
}
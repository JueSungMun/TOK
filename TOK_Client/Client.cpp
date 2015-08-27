#include "Client.h"

Client::Client()
{
}

Client::~Client()
{
	closesocket(hSocket);
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
		MessageBox(NULL, _T("Connet() error"), NULL, NULL);
}

void Client::Recive()
{
	char message[30];
	strLen = recv(hSocket, message, sizeof(message)-1, 0);
	if(strLen == -1)
		MessageBox(NULL, _T("Read Error!"), NULL, NULL);
	else
	MessageBox(NULL, _T("Message From Server"), NULL, NULL);
}
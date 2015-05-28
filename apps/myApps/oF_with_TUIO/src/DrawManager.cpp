#include "DrawManager.h"

static DrawManager* pDrawManager = nullptr;

DrawManager::DrawManager()
{
}

DrawManager::~DrawManager()
{
}

DrawManager* DrawManager::GetInstance()
{
	if(pDrawManager == nullptr)
		pDrawManager = new DrawManager();

	return pDrawManager;
}

void DrawManager::Init()
{
	if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!\n");

	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	if(hSocket == INVALID_SOCKET)
		ErrorHandling("socket() error!\n");
	else
		printf("socket() succeed\n");

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(SERVER_PORT);
	servAddr.sin_addr.s_addr = inet_addr(SERVER_ADDR);

	if(connect(hSocket, ( SOCKADDR* )&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		ErrorHandling("connect() error!\n");
	else
		printf("connect() succeed\n");
}

void DrawManager::Close()
{
	closesocket(hSocket);
	WSACleanup();
}

void DrawManager::SendData()
{
	char* send_buf = "1234"; // test data	
	if(send(hSocket, send_buf, sizeof(send_buf), 0) == SOCKET_ERROR)
		ErrorHandling("send() error!\n");
	else
		printf("sending : %s\n", send_buf);
}

void DrawManager::ErrorHandling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
#ifndef _DRAW_MANAGER_
#define _DRAW_MANAGER_

#include <winsock2.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#include "Define.h"

#define SERVER_PORT 8001
#define SERVER_ADDR "192.168.0.4"

class DrawManager
{
private:
	DrawManager();
	~DrawManager();

public:
	static DrawManager* GetInstance();

	void Init();
	void Close();

	void SendData();

private:
	void ErrorHandling(char* message);

	WSADATA	wsaData;
	SOCKET hSocket;
	SOCKADDR_IN servAddr;
};

#endif
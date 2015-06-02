#ifndef _DRAW_MANAGER_
#define _DRAW_MANAGER_

#include <windows.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#include "Define.h"

#define PORT "\\\\.\\COM12"
#define ARDUINO_WAIT_TIME 2000

class DrawManager
{
private:
	DrawManager();
	~DrawManager();

public:
	static DrawManager* GetInstance();

	void Connect();
	void Close();

	// Writes data from a buffer through the Serial connection
	// return true on success.
	bool WriteData(char* buffer, unsigned int nbChar);

	// Check if we are actually connected
	bool IsConnected();

private:
	//Serial comm handler
	HANDLE hSerial;

	//Connection status
	bool connected;

	//Get various information about the connection
	COMSTAT status;

	//Keep track of last error
	DWORD errors;
};

#endif
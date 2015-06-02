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

void DrawManager::Connect()
{
	// We're not yet connected
	connected = false;

	// Try to connect to the given port through CreateFile
	hSerial = CreateFile(PORT,
						 GENERIC_READ | GENERIC_WRITE,
						 0,
						 NULL,
						 OPEN_EXISTING,
						 FILE_ATTRIBUTE_NORMAL,
						 NULL);

	// Check if the connection was successful
	if(hSerial == INVALID_HANDLE_VALUE)
	{
		// If not successful display an Error
		if(GetLastError() == ERROR_FILE_NOT_FOUND)
		{
			fputs("ERROR: Handle was not attached. Reason: COM12 not available.", stderr);
			fputc('\n', stderr);
		}
		else
		{
			fputs("ERROR: CreateFile error.", stderr);
			fputc('\n', stderr);
		}
	}
	else
	{
		// If connected we try to set the comm parameters
		DCB dcbSerialParams = {0};

		// Try to get the current
		if(!GetCommState(hSerial, &dcbSerialParams))
		{
			// If impossible, show an error
			fputs("ERROR: Failed to get current serial parameters.", stderr);
			fputc('\n', stderr);
		}
		else
		{
			// Define serial connection parameters for the arduino board
			dcbSerialParams.BaudRate = CBR_56000;
			dcbSerialParams.ByteSize = 8;
			dcbSerialParams.StopBits = ONESTOPBIT;
			dcbSerialParams.Parity = NOPARITY;

			// Setting the DTR to Control_Enable ensures that the arduino is properly
			// reset upon establishing a connection
			dcbSerialParams.fDtrControl = DTR_CONTROL_ENABLE;

			// Set the parameters and check for their proper application
			if(!SetCommState(hSerial, &dcbSerialParams))
			{
				fputs("ALERT: Could not set Serial Port parameters.", stderr);
				fputc('\n', stderr);
			}
			else
			{
				// If everything went fine we're connected
				connected = true;

				// Flush any remaining characters in the buffers 
				PurgeComm(hSerial, PURGE_RXCLEAR | PURGE_TXCLEAR);

				// We wait 2s till the arduino board will be reseting
				Sleep(ARDUINO_WAIT_TIME);
			}
		}
	}
}

void DrawManager::Close()
{
	// Check if we are connected before trying to disconnect
	if(connected)
	{
		// We're no longer connected
		connected = false;

		// Close the serial handler
		CloseHandle(hSerial);
	}
}

bool DrawManager::WriteData(char* buffer, unsigned int nbChar)
{
	DWORD bytesSend;

	// Try to write the buffer on the Serial port
	if(!WriteFile(hSerial, (void*)buffer, nbChar, &bytesSend, 0))
	{
		// In case it don't work get comm error and return false
		ClearCommError(hSerial, &errors, &status);
		std::cout << "send fail" << std::endl;
		return false;
	}
	else
	{
		std::cout << "send success" << std::endl;
		return true;
	}
}

bool DrawManager::IsConnected()
{
	// Return the connection status
	return connected;
}

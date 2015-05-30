// colorwheel demo for Adafruit RGBmatrixPanel library.
// Renders a nice circle of hues on our 32x32 RGB LED matrix:
// http://www.adafruit.com/products/607

// Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon
// for Adafruit Industries.
// BSD license, all text above must be included in any redistribution.


#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library
#include <SPI.h>
#include <Ethernet.h>

#define CLK 8
#define OE  9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

EthernetServer server(8001);	// Server port number that you set

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

uint16_t color[13][9] = {0, };

void initColor();

void setup()
{
	byte mac[] = {0x90, 0xA2, 0xDA, 0x0E, 0xAE, 0xDD};	// Mac address of ethernet shield
	IPAddress ip(192, 168, 0, 4);						// DHCP IP address

	Ethernet.begin(mac, ip);	// Initialize the ethernet device
	server.begin();				// Start listening for client

	Serial.begin(9600);		// Open serial communications

	matrix.begin();	// Initialize the LED

	initColor();	// Initialize the color chip
}

void loop()
{
	EthernetClient client = server.available();	// Wait for a new client

	if(client)
	{
		while(client.available() > 0)
		{
			char thisChar = client.read();
			Serial.print(thisChar);
		}
		Serial.println();
	}
}

void initColor()
{
	color[0][0] = matrix.Color888(51, 0, 0);
	color[0][1] = matrix.Color888(102, 0, 0);
	color[0][2] = matrix.Color888(153, 0, 0);
	color[0][3] = matrix.Color888(204, 0, 0);
	color[0][4] = matrix.Color888(255, 0, 0);
	color[0][5] = matrix.Color888(255, 51, 51);
	color[0][6] = matrix.Color888(255, 102, 102);
	color[0][7] = matrix.Color888(255, 153, 153);
	color[0][8] = matrix.Color888(255, 204, 204);

	color[1][0] = matrix.Color888(51, 25, 0);
	color[1][1] = matrix.Color888(102, 51, 0);
	color[1][2] = matrix.Color888(153, 76, 0);
	color[1][3] = matrix.Color888(204, 102, 0);
	color[1][4] = matrix.Color888(255, 128, 0);
	color[1][5] = matrix.Color888(255, 153, 51);
	color[1][6] = matrix.Color888(255, 178, 102);
	color[1][7] = matrix.Color888(255, 204, 153);
	color[1][8] = matrix.Color888(255, 229, 204);
	
	color[2][0] = matrix.Color888(51, 51, 0);
	color[2][1] = matrix.Color888(102, 102, 0);
	color[2][2] = matrix.Color888(153, 153, 0);
	color[2][3] = matrix.Color888(204, 204, 0);
	color[2][4] = matrix.Color888(255, 255, 0);
	color[2][5] = matrix.Color888(255, 255, 51);
	color[2][6] = matrix.Color888(255, 255, 102);
	color[2][7] = matrix.Color888(255, 255, 153);
	color[2][8] = matrix.Color888(255, 255, 204);
	
	color[3][0] = matrix.Color888(25, 51, 0);
	color[3][1] = matrix.Color888(51, 102, 0);
	color[3][2] = matrix.Color888(76, 153, 0);
	color[3][3] = matrix.Color888(102, 204, 0);
	color[3][4] = matrix.Color888(128, 255, 0);
	color[3][5] = matrix.Color888(153, 255, 51);
	color[3][6] = matrix.Color888(178, 255, 102);
	color[3][7] = matrix.Color888(204, 255, 153);
	color[3][8] = matrix.Color888(229, 255, 204);
	
	color[4][0] = matrix.Color888(0, 51, 0);
	color[4][1] = matrix.Color888(0, 102, 0);
	color[4][2] = matrix.Color888(0, 153, 0);
	color[4][3] = matrix.Color888(0, 204, 0);
	color[4][4] = matrix.Color888(0, 255, 0);
	color[4][5] = matrix.Color888(51, 255, 51);
	color[4][6] = matrix.Color888(102, 255, 102);
	color[4][7] = matrix.Color888(153, 255, 153);
	color[4][8] = matrix.Color888(204, 255, 204);
	
	color[5][0] = matrix.Color888(0, 51, 25);
	color[5][1] = matrix.Color888(0, 102, 51);
	color[5][2] = matrix.Color888(0, 153, 76);
	color[5][3] = matrix.Color888(0, 204, 102);
	color[5][4] = matrix.Color888(0, 255, 128);
	color[5][5] = matrix.Color888(51, 255, 153);
	color[5][6] = matrix.Color888(102, 255, 178);
	color[5][7] = matrix.Color888(153, 255, 204);
	color[5][8] = matrix.Color888(204, 255, 209);
	
	color[6][0] = matrix.Color888(0, 51, 51);
	color[6][1] = matrix.Color888(0, 102, 102);
	color[6][2] = matrix.Color888(0, 153, 153);
	color[6][3] = matrix.Color888(0, 204, 204);
	color[6][4] = matrix.Color888(0, 255, 255);
	color[6][5] = matrix.Color888(51, 255, 255);
	color[6][6] = matrix.Color888(102, 255, 255);
	color[6][7] = matrix.Color888(153, 255, 255);
	color[6][8] = matrix.Color888(204, 255, 255);
	
	color[7][0] = matrix.Color888(0, 25, 51);
	color[7][1] = matrix.Color888(0, 51, 102);
	color[7][2] = matrix.Color888(0, 76, 153);
	color[7][3] = matrix.Color888(0, 102, 204);
	color[7][4] = matrix.Color888(0, 128, 255);
	color[7][5] = matrix.Color888(51, 153, 255);
	color[7][6] = matrix.Color888(102, 178, 255);
	color[7][7] = matrix.Color888(153, 204, 255);
	color[7][8] = matrix.Color888(204, 229, 255);
	
	color[8][0] = matrix.Color888(0, 0, 51);
	color[8][1] = matrix.Color888(0, 0, 102);
	color[8][2] = matrix.Color888(0, 0, 153);
	color[8][3] = matrix.Color888(0, 0, 204);
	color[8][4] = matrix.Color888(0, 0, 255);
	color[8][5] = matrix.Color888(51, 51, 255);
	color[8][6] = matrix.Color888(102, 102, 255);
	color[8][7] = matrix.Color888(153, 153, 255);
	color[8][8] = matrix.Color888(204, 204, 255);

	color[9][0] = matrix.Color888(25, 0, 51);
	color[9][1] = matrix.Color888(51, 0, 102);
	color[9][2] = matrix.Color888(76, 0, 153);
	color[9][3] = matrix.Color888(102, 0, 204);
	color[9][4] = matrix.Color888(127, 0, 255);
	color[9][5] = matrix.Color888(153, 51, 255);
	color[9][6] = matrix.Color888(178, 102, 255);
	color[9][7] = matrix.Color888(204, 153, 255);
	color[9][8] = matrix.Color888(229, 204, 255);

	color[10][0] = matrix.Color888(51, 0, 51);
	color[10][1] = matrix.Color888(102, 0, 102);
	color[10][2] = matrix.Color888(153, 0, 153);
	color[10][3] = matrix.Color888(204, 0, 204);
	color[10][4] = matrix.Color888(255, 0, 255);
	color[10][5] = matrix.Color888(255, 51, 255);
	color[10][6] = matrix.Color888(255, 102, 255);
	color[10][7] = matrix.Color888(255, 153, 255);
	color[10][8] = matrix.Color888(255, 204, 255);

	color[11][0] = matrix.Color888(51, 0, 25);
	color[11][1] = matrix.Color888(102, 0, 51);
	color[11][2] = matrix.Color888(153, 0, 76);
	color[11][3] = matrix.Color888(204, 0, 102);
	color[11][4] = matrix.Color888(255, 0, 127);
	color[11][5] = matrix.Color888(255, 51, 153);
	color[11][6] = matrix.Color888(255, 102, 178);
	color[11][7] = matrix.Color888(255, 153, 204);
	color[11][8] = matrix.Color888(255, 204, 229);

	color[12][0] = matrix.Color888(0, 0, 0);
	color[12][1] = matrix.Color888(32, 32, 32);
	color[12][2] = matrix.Color888(64, 64, 64);
	color[12][3] = matrix.Color888(96, 96, 96);
	color[12][4] = matrix.Color888(128, 128, 128);
	color[12][5] = matrix.Color888(160, 160, 160);
	color[12][6] = matrix.Color888(192, 192, 192);
	color[12][7] = matrix.Color888(224, 224, 224);
	color[12][8] = matrix.Color888(255, 255, 255);
}
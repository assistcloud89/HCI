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

void setup()
{
	byte mac[] = {0x90, 0xA2, 0xDA, 0x0E, 0xAE, 0xDD};	// Mac address of ethernet shield
	IPAddress ip(192, 168, 0, 4);						// DHCP IP address

	Ethernet.begin(mac, ip);	// Initialize the ethernet device
	server.begin();				// Start listening for client

	Serial.begin(9600);		// Open serial communications

	matrix.begin();	// Initialize the LED
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

// WebApp.h

#ifndef _WEBAPP_h
#define _WEBAPP_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <WiFi.h>


#define ssid "TGR Studios"
#define password "uzumymw1leS"


inline WiFiServer server(80);

class WebUtilll
{ 
public:

	static WebUtilll* Instance;
	String header;


	void WebUtilSetup();
	void WebUtilUpdate();


	void CreateClient(WiFiClient* client);
#pragma region Header
	void CreateHeader(WiFiClient* client);
	static void CreateCSS(WiFiClient* client);
	static void CreateMainScript(WiFiClient* client);
#pragma endregion Header
#pragma region Body
	void CreateBody(WiFiClient* client);
#pragma endregion Body
	std::tuple<int, int> GetSpeed();
	WebUtilll()
	{
		Instance = this;
	}
private:
	String valueString = String(5);
	int pos1 = 0;
	int pos2 = 0;
	unsigned long currentTime = millis();
	unsigned long previousTime = 0;
	const long timeoutTime = 200000;
};
#endif


// WebApp.h

#ifndef _WEBAPP_h
#define _WEBAPP_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
#include <WiFi.h>
#pragma once

#define ssid "kamen ia ne dam"
#define password "lizochek"

#define dataInPackage 2




struct WebUtil {
public:
  String header;


  static WebUtil& GetInstance();

  WebUtil(const WebUtil& arg) = delete;              // Copy constructor
  WebUtil(const WebUtil&& arg) = delete;             // Move constructor
  WebUtil& operator=(const WebUtil& arg) = delete;   // Assignment operator
  WebUtil& operator=(const WebUtil&& arg) = delete;  // Move operator


  WebUtil() {
    currentTime = millis();
  }
  ~WebUtil() {
    delete[] & header;
    delete[] & valueString;
  }




  void WebUtilSetup(WiFiServer* server);
  void WebUtilUpdate(WiFiServer* server);


  void CreateClient(WiFiClient* client);
  void GetPackageIndex(String* value);

#pragma region Header
  void CreateHeader(WiFiClient* client);
  static void CreateCSS(WiFiClient* client);
  static void CreateMainScript(WiFiClient* client);
#pragma endregion Header
#pragma region Body
  void CreateBody(WiFiClient* client);
  void CreateJoystick(WiFiClient* client);
  void CreateSideScript(WiFiClient* client);
#pragma endregion Body

  String* GetData();
  void SplitData(String* value);
  std::tuple<int, int> GetSpeed();

  //static int joystickPos[2];





private:
  String valueString = String(5);
  int pos1 = 0;
  int pos2 = 0;
  unsigned long currentTime;
  unsigned long previousTime = 0;
  const long timeoutTime = 200000;
  char dataIndexBuf[2];
  int joystickPos[2];
};
#endif
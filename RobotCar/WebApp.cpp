//
//
//

#include "WebApp.h"


WebUtil& WebUtil::GetInstance() {

  static WebUtil singleInstance;
  return singleInstance;
}

void WebUtil::WebUtilSetup(WiFiServer* server) {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Pico W is connected!");
  Serial.print("Assigned IP address: ");
  Serial.println(WiFi.localIP());
  server->begin();
}

void WebUtil::WebUtilUpdate(WiFiServer* server) {

  WiFiClient client = server->available();
  Serial.println("shfd");
  if (client) {
    Serial.println("TryToConnect");
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");
    String currentLine = "";
    while (client.connected() && currentTime - previousTime <= timeoutTime) {
      currentTime = millis();
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        header += c;
        if (c == '\n') {
          if (currentLine.length() == 0) {
            CreateClient(&client);
            client.println();
            break;
          } else {
            // New lline is received, clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}

void WebUtil::CreateClient(WiFiClient* client) {
  client->println("HTTP/1.1 200 OK");
  client->println("Content-type:text/html");
  client->println("Connection: close");
  client->println();
  CreateHeader(client);
  CreateBody(client);
  client->println("</body></html>");
}
#pragma region Header
void WebUtil::CreateHeader(WiFiClient* client) {
  client->println("<!DOCTYPE html><html>");
  client->println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  client->println("<link rel=\"icon\" href=\"data:,\">");
  CreateCSS(client);
  CreateMainScript(client);
  client->println("</head>");
}

void WebUtil::CreateCSS(WiFiClient* client) {
  client->println("<style>body { text-align: center; font-family: \"Trebuchet MS\", Arial; margin-left:auto; margin-right:auto; }");
  client->println(".row{display: inline-flex;clear: both;}");
  client->println(".columnLateral{float: left;width: 15%;min-width: 300px;}");
  client->println(".columnCetral{float: left;width: 70%;min-width: 300px;}");
  client->println("#joy2Div{width:200px;height:200px;margin:50px}");
  client->println("#joystick{border: 1px solid #FF0000;}");
  client->println("#joystick2{border: 1px solid #0000FF;}</style>");
}

void WebUtil::CreateMainScript(WiFiClient* client) {
  client->println("<script >let StickStatus={xPosition:0,yPosition:0,x:0,y:0,cardinalDirection:\"C\"};var JoyStick=function(t,e,i){var o=void 0===(e=e||{}).title?\"joystick\":e.title,n=void 0===e.width?0:e.width,a=void 0===e.height?0:e.height,r=void 0===e.internalFillColor?\"#00AA00\":e.internalFillColor,c=void 0===e.internalLineWidth?2:e.internalLineWidth,s=void 0===e.internalStrokeColor?\"#003300\":e.internalStrokeColor,d=void 0===e.externalLineWidth?2:e.externalLineWidth,u=void 0===e.externalStrokeColor?\"#008000\":e.externalStrokeColor,h=void 0===e.autoReturnToCenter||e.autoReturnToCenter;i=i||function(t){};var S=document.getElementById(t);S.style.touchAction=\"none\";var f=document.createElement(\"canvas\");f.id=o,0===n&&(n=S.clientWidth),0===a&&(a=S.clientHeight),f.width=n,f.height=a,S.appendChild(f);var l=f.getContext(\"2d\"),k=0,g=2*Math.PI,x=(f.width-(f.width/2+10))/2,v=x+5,P=x+30,m=f.width/2,C=f.height/2,p=f.width/10,y=-1*p,w=f.height/10,L=-1*w,F=m,E=C;function W(){l.beginPath(),l.arc(m,C,P,0,g,!1),l.lineWidth=d,l.strokeStyle=u,l.stroke()}function T(){l.beginPath(),F<x&&(F=v),F+x>f.width&&(F=f.width-v),E<x&&(E=v),E+x>f.height&&(E=f.height-v),l.arc(F,E,x,0,g,!1);var t=l.createRadialGradient(m,C,5,m,C,200);t.addColorStop(0,r),t.addColorStop(1,s),l.fillStyle=t,l.fill(),l.lineWidth=c,l.strokeStyle=s,l.stroke()}function D(){let t=\"\",e=F-m,i=E-C;return i>=L&&i<=w&&(t=\"C\"),i<L&&(t=\"N\"),i>w&&(t=\"S\"),e<y&&(\"C\"===t?t=\"W\":t+=\"W\"),e>p&&(\"C\"===t?t=\"E\":t+=\"E\"),t}\"ontouchstart\"in document.documentElement?(f.addEventListener(\"touchstart\",function(t){k=1},!1),document.addEventListener(\"touchmove\",function(t){1===k&&t.targetTouches[0].target===f&&(F=t.targetTouches[0].pageX,E=t.targetTouches[0].pageY,\"BODY\"===f.offsetParent.tagName.toUpperCase()?(F-=f.offsetLeft,E-=f.offsetTop):(F-=f.offsetParent.offsetLeft,E-=f.offsetParent.offsetTop),l.clearRect(0,0,f.width,f.height),W(),T(),StickStatus.xPosition=F,StickStatus.yPosition=E,StickStatus.x=((F-m)/v*100).toFixed(),StickStatus.y=((E-C)/v*100*-1).toFixed(),StickStatus.cardinalDirection=D(),i(StickStatus))},!1),document.addEventListener(\"touchend\",function(t){k=0,h&&(F=m,E=C);l.clearRect(0,0,f.width,f.height),W(),T(),StickStatus.xPosition=F,StickStatus.yPosition=E,StickStatus.x=((F-m)/v*100).toFixed(),StickStatus.y=((E-C)/v*100*-1).toFixed(),StickStatus.cardinalDirection=D(),pos = \"\",pos = StickStatus.x +\".\"+ StickStatus.y,console.log(\"kurwa\"),$.get(\"/?value=\" + pos + \"&\"),console.log(pos),{Connection: close},i(StickStatus)},!1)):(f.addEventListener(\"mousedown\",function(t){k=1},!1),document.addEventListener(\"mousemove\",function(t){1===k&&(F=t.pageX,E=t.pageY,\"BODY\"===f.offsetParent.tagName.toUpperCase()?(F-=f.offsetLeft,E-=f.offsetTop):(F-=f.offsetParent.offsetLeft,E-=f.offsetParent.offsetTop),l.clearRect(0,0,f.width,f.height),W(),T(),StickStatus.xPosition=F,StickStatus.yPosition=E,StickStatus.x=((F-m)/v*100).toFixed(),StickStatus.y=((E-C)/v*100*-1).toFixed(),StickStatus.cardinalDirection=D(),i(StickStatus))},!1),document.addEventListener(\"mouseup\",function(t){k=0,h&&(F=m,E=C);l.clearRect(0,0,f.width,f.height),W(),T(),StickStatus.xPosition=F,StickStatus.yPosition=E,StickStatus.x=((F-m)/v*100).toFixed(),StickStatus.y=((E-C)/v*100*-1).toFixed(),StickStatus.cardinalDirection=D(),pos = \"\",pos = StickStatus.x +\".\"+ StickStatus.y,console.log(\"kurwa\"),$.get(\"/?value=\" + pos + \"&\"),console.log(pos),{Connection: close},i(StickStatus)},!1)),W(),T(),this.GetWidth=function(){return f.width},this.GetHeight=function(){return f.height},this.GetPosX=function(){return F},this.GetPosY=function(){return E},this.GetX=function(){return((F-m)/v*100).toFixed()},this.GetY=function(){return((E-C)/v*100*-1).toFixed()},this.GetDir=function(){return D()}};</script>");
  client->println("<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script>");
}
#pragma endregion Header
#pragma region Body
void WebUtil::CreateBody(WiFiClient* client) {
  client->println("<body style=\"background-color:#1B1F3B;\">");
  CreateJoystick(client);
  CreateSideScript(client);
}

void WebUtil::CreateJoystick(WiFiClient* client) {
  client->println("<div class=\"columnLateral\"><div id=\"joy2Div\"></div>Posizione X:<input id=\"joy2PosizioneX\" type=\"text\" /></br>Posizione Y:<input id=\"joy2PosizioneY\" type=\"text\" /></br>Direzione:<input id=\"joy2Direzione\" type=\"text\" /></br>X :<input id=\"joy2X\" type=\"text\" onchange=\"joyVal(this.value)\" /></br>Y :<input id=\"joy2Y\" type=\"text\" /></div></div>");
}

void WebUtil::CreateSideScript(WiFiClient* client) {
  client->println("<script type=\"text/javascript\">var joy2Param = { \"title\": \"joystick2\", \"autoReturnToCenter\": false };  var Joy2 = new JoyStick('joy2Div', joy2Param);    var joy2IinputPosX = document.getElementById(\"joy2PosizioneX\");  var joy2InputPosY = document.getElementById(\"joy2PosizioneY\");  var joy2Direzione = document.getElementById(\"joy2Direzione\");  var joy2X = document.getElementById(\"joy2X\");  var joy2Y = document.getElementById(\"joy2Y\");    setInterval(function(){ joy2IinputPosX.value=Joy2.GetPosX(); }, 50);  setInterval(function(){ joy2InputPosY.value=Joy2.GetPosY(); }, 50);  setInterval(function(){ joy2Direzione.value=Joy2.GetDir(); }, 50);  setInterval(function(){ joy2X.value=Joy2.GetX(); }, 50);  setInterval(function(){ joy2Y.value=Joy2.GetY(); }, 50);");
  client->println("$.ajaxSetup({timeout:1000}); ");
  client->println("function joyVal() { var pos = Joy2.GetX() +\".\"+ Joy2.GetY(); ");
  client->println("$.get(\"/?value=\" + pos + \"&\");");
  client->println("console.log(\"asdf\");}");
  client->println("</script>");
}
#pragma endregion Body

String* WebUtil::GetData() {
  if (header.indexOf("GET /?value=") >= 0) {
    pos1 = header.indexOf('=');
    pos2 = header.indexOf('&');
    valueString = header.substring(pos1 + 1, pos2);
    Serial.print("Val =");
    Serial.println(valueString);
  }
  return &valueString;
}

void WebUtil::GetPackageIndex(String* value) {
  value->substring(value->operator[](0), value->operator[](2)).toCharArray(dataIndexBuf, 2);
  Serial.print("Index =");
  Serial.println(dataIndexBuf);
  *value = value->substring(3);
}

void WebUtil::SplitData(String* value) {
  GetPackageIndex(value);
  switch (static_cast<int>(strtol(dataIndexBuf, nullptr, 16))) {
    case 0:
      break;
    case 1:
      break;
    case 2:
      joystickPos[0] = value->substring(0, value->indexOf(".")).toInt();
      *value = value->substring(value->indexOf("."));
      joystickPos[1] = value->toInt();
    case 3:
      break;
    case 4:
      break;
    default:
      break;
  }
}

/*
char CharToHex(char cIn)
{
	static_assert('1' == '0' + 1 && '2' == '1' + 1 && '3' == '2' + 1 && '4' == '3' + 1 && '5' == '4' + 1 && '6' == '5' + 1 && '7' == '6' + 1 && '8' == '7' + 1 && '9' == '8' + 1, "code expects");
	static_assert('B' == 'A' + 1 && 'C' == 'B' + 1 && 'D' == 'C' + 1 && 'E' == 'D' + 1 && 'F' == 'E' + 1, "code expects");
	static_assert('b' == 'a' + 1 && 'c' == 'b' + 1 && 'd' == 'c' + 1 && 'e' == 'd' + 1 && 'f' == 'e' + 1, "code expects");
	static_assert('9' < 'A' && 'F' < 'a', "code expects");

	char cRet = 0x10; // > 0xF means unrecognized input

	if (cIn <= '9')
	{
		if (cIn >= '0')
			cRet = cIn - '0';
	}
	else if (cIn <= 'F')
	{
		if (cIn >= 'A')
			cRet = cIn - 'A' + 10;
	}
	else if (cIn <= 'f')
	{
		if (cIn >= 'a')
			cRet = cIn - 'a' + 10;
	}

	return cRet;
}

//---------------------------------------------------------------------------

void StrToCommands(const char* pszIn)
{
	for (int iPair = 0; ; ++iPair)
	{
		// note: terminating zero is also detected by CharToHex's error-ret

		char cVal1;
		char cVal2;
		char cDigit;

		cDigit = CharToHex(*pszIn++); if (cDigit > 0xF) break;
		cVal1 = cDigit << 4;

		cDigit = CharToHex(*pszIn++); if (cDigit > 0xF) break;
		cVal1 |= cDigit;

		if (*pszIn++ != '-') // this check includes term-zero
			break;

		cDigit = CharToHex(*pszIn++); if (cDigit > 0xF) break;
		cVal2 = cDigit << 4;

		cDigit = CharToHex(*pszIn++); if (cDigit > 0xF) break;
		cVal2 |= cDigit;

		// %%% here is a place to execute command using cVal1, cVal2 and iPair values ...

		if (*pszIn++ != '.') // this check includes term-zero
			break;
	}
}
*/
std::tuple<int, int> WebUtil::GetSpeed() {

  return std::tuple<int, int>(joystickPos[1] - joystickPos[0], joystickPos[1] + joystickPos[0]);
}
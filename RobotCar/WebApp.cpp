// 
// 
// 

#include "WebApp.h"


void WebUtil::WebUtilSetup()
{
		WiFi.begin(ssid, password);
		while (WiFi.status() != WL_CONNECTED) {
			delay(500);
			Serial.print(".");
		}

		Serial.println("");
		Serial.println("Pico W is connected!");
		Serial.print("Assigned IP address: ");
		Serial.println(WiFi.localIP());
		server.begin();
}

void WebUtil::WebUtilUpdate()
{
	WiFiClient client = server.available();

	if (client) {
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
					}
				}
			}
		}
	}
}

void WebUtil::CreateClient(WiFiClient* client)
{
	client->println("HTTP/1.1 200 OK");
	client->println("Content-type:text/html");
	client->println("Connection: close");
	client->println();
	CreateHeader(client);
	CreateBody(client);
}
#pragma region Header
void WebUtil::CreateHeader(WiFiClient* client)
{
	client->println("<!DOCTYPE html><html>");
	client->println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
	client->println("<link rel=\"icon\" href=\"data:,\">");
	CreateCSS(client);
	CreateMainScript(client);
	client->println("</head>");
}

void WebUtil::CreateCSS(WiFiClient* client)
{
	client->println("<style>body { text-align: center; font-family: \"Trebuchet MS\", Arial; margin-left:auto; margin-right:auto; }");
	client->println(".row{display: inline-flex;clear: both;}");
	client->println(".columnLateral{float: left;width: 15%;min-width: 300px;}");
	client->println(".columnCetral{float: left;width: 70%;min-width: 300px;}");
	client->println("#joy2Div{width:200px;height:200px;margin:50px}");
	client->println("#joystick{border: 1px solid #FF0000;}");
	client->println("#joystick2{border: 1px solid #0000FF;}</style>");
}

void WebUtil::CreateMainScript(WiFiClient* client)
{
	client->println("<script >let StickStatus={xPosition:0,yPosition:0,x:0,y:0,cardinalDirection:\"C\"};var JoyStick=function(t,e,i){var o=void 0===(e=e||{}).title?\"joystick\":e.title,n=void 0===e.width?0:e.width,a=void 0===e.height?0:e.height,r=void 0===e.internalFillColor?\"#00AA00\":e.internalFillColor,c=void 0===e.internalLineWidth?2:e.internalLineWidth,s=void 0===e.internalStrokeColor?\"#003300\":e.internalStrokeColor,d=void 0===e.externalLineWidth?2:e.externalLineWidth,u=void 0===e.externalStrokeColor?\"#008000\":e.externalStrokeColor,h=void 0===e.autoReturnToCenter||e.autoReturnToCenter;i=i||function(t){};var S=document.getElementById(t);S.style.touchAction=\"none\";var f=document.createElement(\"canvas\");f.id=o,0===n&&(n=S.clientWidth),0===a&&(a=S.clientHeight),f.width=n,f.height=a,S.appendChild(f);var l=f.getContext(\"2d\"),k=0,g=2*Math.PI,x=(f.width-(f.width/2+10))/2,v=x+5,P=x+30,m=f.width/2,C=f.height/2,p=f.width/10,y=-1*p,w=f.height/10,L=-1*w,F=m,E=C;function W(){l.beginPath(),l.arc(m,C,P,0,g,!1),l.lineWidth=d,l.strokeStyle=u,l.stroke()}function T(){l.beginPath(),F<x&&(F=v),F+x>f.width&&(F=f.width-v),E<x&&(E=v),E+x>f.height&&(E=f.height-v),l.arc(F,E,x,0,g,!1);var t=l.createRadialGradient(m,C,5,m,C,200);t.addColorStop(0,r),t.addColorStop(1,s),l.fillStyle=t,l.fill(),l.lineWidth=c,l.strokeStyle=s,l.stroke()}function D(){let t=\"\",e=F-m,i=E-C;return i>=L&&i<=w&&(t=\"C\"),i<L&&(t=\"N\"),i>w&&(t=\"S\"),e<y&&(\"C\"===t?t=\"W\":t+=\"W\"),e>p&&(\"C\"===t?t=\"E\":t+=\"E\"),t}\"ontouchstart\"in document.documentElement?(f.addEventListener(\"touchstart\",function(t){k=1},!1),document.addEventListener(\"touchmove\",function(t){1===k&&t.targetTouches[0].target===f&&(F=t.targetTouches[0].pageX,E=t.targetTouches[0].pageY,\"BODY\"===f.offsetParent.tagName.toUpperCase()?(F-=f.offsetLeft,E-=f.offsetTop):(F-=f.offsetParent.offsetLeft,E-=f.offsetParent.offsetTop),l.clearRect(0,0,f.width,f.height),W(),T(),StickStatus.xPosition=F,StickStatus.yPosition=E,StickStatus.x=((F-m)/v*100).toFixed(),StickStatus.y=((E-C)/v*100*-1).toFixed(),StickStatus.cardinalDirection=D(),i(StickStatus))},!1),document.addEventListener(\"touchend\",function(t){k=0,h&&(F=m,E=C);l.clearRect(0,0,f.width,f.height),W(),T(),StickStatus.xPosition=F,StickStatus.yPosition=E,StickStatus.x=((F-m)/v*100).toFixed(),StickStatus.y=((E-C)/v*100*-1).toFixed(),StickStatus.cardinalDirection=D(),pos = \"\",pos = StickStatus.x +\".\"+ StickStatus.y,console.log(\"kurwa\"),$.get(\"/?value=\" + pos + \"&\"),console.log(pos),{Connection: close},i(StickStatus)},!1)):(f.addEventListener(\"mousedown\",function(t){k=1},!1),document.addEventListener(\"mousemove\",function(t){1===k&&(F=t.pageX,E=t.pageY,\"BODY\"===f.offsetParent.tagName.toUpperCase()?(F-=f.offsetLeft,E-=f.offsetTop):(F-=f.offsetParent.offsetLeft,E-=f.offsetParent.offsetTop),l.clearRect(0,0,f.width,f.height),W(),T(),StickStatus.xPosition=F,StickStatus.yPosition=E,StickStatus.x=((F-m)/v*100).toFixed(),StickStatus.y=((E-C)/v*100*-1).toFixed(),StickStatus.cardinalDirection=D(),i(StickStatus))},!1),document.addEventListener(\"mouseup\",function(t){k=0,h&&(F=m,E=C);l.clearRect(0,0,f.width,f.height),W(),T(),StickStatus.xPosition=F,StickStatus.yPosition=E,StickStatus.x=((F-m)/v*100).toFixed(),StickStatus.y=((E-C)/v*100*-1).toFixed(),StickStatus.cardinalDirection=D(),pos = \"\",pos = StickStatus.x +\".\"+ StickStatus.y,console.log(\"kurwa\"),$.get(\"/?value=\" + pos + \"&\"),console.log(pos),{Connection: close},i(StickStatus)},!1)),W(),T(),this.GetWidth=function(){return f.width},this.GetHeight=function(){return f.height},this.GetPosX=function(){return F},this.GetPosY=function(){return E},this.GetX=function(){return((F-m)/v*100).toFixed()},this.GetY=function(){return((E-C)/v*100*-1).toFixed()},this.GetDir=function(){return D()}};</script>");
	client->println("<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script>");
}
#pragma endregion Header
#pragma region Body
void WebUtil::CreateBody(WiFiClient* client)
{
	client->println("<body style=\"background-color:#1B1F3B;\">");
}
#pragma endregion Body
std::tuple<int, int> WebUtil::GetSpeed()
{
	return std::tuple<int, int>(0, 0);
}

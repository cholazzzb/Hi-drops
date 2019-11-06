#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <AutoConnect.h>

ESP8266WebServer Server;
AutoConnect Portal(Server);

void rootPage(){
  char content[] = "Hello, world";
  Server.send(200, "text/plain", content);
}

void setup() {
  Serial.begin(115200);
  Serial.println();

  Server.on("/", rootPage);
  Portal.begin();
  Serial.println("Web server started:" + WiFi.localIP().toString());
}

void loop() {
  Portal.handleClient();
}

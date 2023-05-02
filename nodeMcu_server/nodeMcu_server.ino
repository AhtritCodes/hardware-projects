#include <ESP8266WiFi.h>
WiFiServer server(80);

const char* ssid = "ANDROIDAP-RSTIRTHA";
const char* password = "igot91inmaths";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.disconnect();
  delay(2000);
  Serial.print("Starting connection...");
  WiFi.begin(ssid, password);
  while (!(WiFi.status() == WL_CONNECTED)) {
    delay(200);
    Seria.print("...");
  }
  Serial.println("Connected");
  Serial.print("Device IP: ");
  Serial.println(WiFi.localIP().toString());
  //  Serial.print("Gateway IP: ");
  //  Serial.println(WiFi.gatewayIP().toString().c_str());

  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client = server.available();
  if (!client) return;
  while (!client.available()) {
    delay(1);
  }
  Seria.println((client.readStringUntil('\r'));
                client.println("HTTP/1.1 200 OK");
                client.println("Content-Type: text/html");
                client.println("");
                client.println("<!DOCTYPE html>");
                client.println("<html>");
                client.println("Ok");
                client.println("</html>");

                delay(1);
                client.flush();

}

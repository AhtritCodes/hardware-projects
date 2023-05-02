#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

SoftwareSerial espSerial(D9, D10);

// SSID and password for WiFi connection
//const char* ssid = "";
//const char* password = "";

//unsigned long prevMillis = 0;
//unsigned long interval = 30000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(100);
  init_espSerial();
}

void loop() {
  // put your main code here, to run repeatedly:
  //  check_espSerial();
  if (espSerial.available() > 0) {
    //    byte data[20];
    //    int bytesReceived = Serial.readBytesUntil('\n', data, 10);
    //    data[bytesReceived] = '\0';
    String data = espSerial.readStringUntil('\r');
    Serial.print("Received Data: ");
    //    Serial.println((char*)data);
    Serial.println(data);
  }
}

/*
  void init_wifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.print('\n');
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  }

  void check_wifi() {
  unsigned long currMillis = millis();
  // if WiFi is not connected, try reconnecting every interval seconds
  if (WiFi.status() != WL_CONNECTED && currMillis - prevMillis >= interval) {
    Serial.print(millis());
    Serial.println("Reconnecting .. ");
    WiFi.disconnect();
    WiFi.begin(ssid, password);
    Serial.println(WiFi.localIP());
    Serial.println(WiFi.RSSI());
    prevMillis = currMillis;
  }
  }

*/


void init_espSerial() {
  espSerial.begin(9600);
  //  pinMode(D9, INPUT);
  //  pinMode(D10, OUTPUT);
}

/*
  void check_espSerial() {
  if (espSerial.available() > 0) {
    //    byte data[20];
    //    int bytesReceived = Serial.readBytesUntil('\n', data, 10);
    //    data[bytesReceived] = '\0';
    String data = espSerial.readStringUntil('\r');
    Serial.print("Received Data: ");
    //    Serial.println((char*)data);
    Serial.println(data);
  }
  }
*/

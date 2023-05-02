#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

// network credentials
const char* ssid = "ahtritCodes";
const char* password = "rdxqc5k2jbdmaei";

// Server address and port for POST request
const String serverAddress = "http://192.168.0.143:1337/sendData";
//const int serverPort = 3000;


// Received data from Serial communication
String jsonString;

/*
    Serial communication software serial object
*/
SoftwareSerial ESP_Serial(D5, D6);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  init_ESP_Serial();
  delay(100);

  initWiFi();

  delay(2000);
  //  Set server address and port
  //  client.connect(serverAddress, serverPort);
}

void loop() {
  // put your main code here, to run repeatedly:

  POSTusingHTTPClient();
}

//======================================================================

void initWiFi() {

  // connect to WiFi network
  Serial.println();
  Serial.print("Connecting ..");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.print("IP address: ");
  Serial.print(WiFi.localIP());
}


void POSTusingHTTPClient() {

  if (WiFi.status() == WL_CONNECTED) {
    // http client object
    HTTPClient http;

    // WiFiClient object
    WiFiClient client;

    // set target url with query parameters
    //        String url = String(serverAddress) + "/api/data";

    // set request body data
    //    StaticJsonDocument<200> doc;
    //    doc["sensor"] = "NodeMCU";
    //    doc["value"] = random(50);

    // Serialize JSON data to a string
    //    String jsonString;
    //    serializeJson(doc, jsonString);

    read_serial_communication_data();

    // send POST request
    http.begin(client, serverAddress);
    http.addHeader("Content-Type", "application/json");

    //    String data = "param1=" + String(random(50));
    //    String data = "data=30";

    Serial.println(jsonString);

    int httpCode = http.POST(jsonString);
    
    //    String payload = http.getString();

    //    Serial.println("HTTP Code: " + String(httpCode));
    //    Serial.println("payload: " + String(payload));

    // handle server response
    if (httpCode > 0) {
      String response = http.getString();
      Serial.println("Response Code: " + String(httpCode));
      Serial.println("Server response: " + String(response));
    }
    else {
      Serial.println("Error sending POST request: " + httpCode);
    }

    // Close HTTPClient object
    http.end();
  }

  delay(10000);
}


void init_ESP_Serial() {
  ESP_Serial.begin(9600);
  //  pinMode(D9, INPUT);
  //  pinMode(D10, OUTPUT);
}


void read_serial_communication_data() {

  //  if (ESP_Serial.available() > 0) {
  //    //    byte data[20];
  //    //    int bytesReceived = Serial.readBytesUntil('\n', data, 10);
  //    //    data[bytesReceived] = '\0';
  //    received_data = ESP_Serial.readStringUntil('\r');
  //    Serial.print("Received Data: ");
  //    //    Serial.println((char*)data);
  //    Serial.println(data);
  //  }
  if (Serial.available() > 0) {
    jsonString = Serial.readStringUntil('\n');

    Serial.print("Received JSON data: ");
    Serial.println(jsonString);
  }
}


/*
  void POSTusingWiFiClient() {

  if (WiFi.status() == WL_CONNECTED) {

    StaticJsonDocument<200> doc;
    doc["sensor"] = "NodeMCU";
    doc["value"] = random(100);

    // Serialize JSON data to a string
    String jsonString;
    serializeJson(doc, jsonString);

    // Send data to server
    Serial.print("Sending data: ");
    Serial.println(jsonString);
    client.println("POST /api/data HTTP/1.1");
    client.println("Host: " + String(serverAddress) + ":" + String(serverPort));
    client.println("Content-Type: application/json");
    client.print("Content-Length: ");
    client.println(jsonString.length());
    client.println();
    client.println(jsonString);

    // Wait for response
    while (client.connected() && !client.available()) {
      delay(10);
    }
    if (client.available()) {
      String response = client.readStringUntil('\n');
      Serial.println(response);
    }

    // Wait for 5ms before sending the next data
    delay(5000);
  }
  }
*/

/*
  void GETusingHTTPClient() {

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    WiFiClient client;

    // define dynamic parameters from serial port
    //    String tdsVal = mySerial.read();

    //  build query string
    //    String url = baseUrl + "/1";

    //    send HTTP GET request to API endpoint with dynamic parameters
    http.begin(client, "http://localhost:3000/api/data");
    int httpCode = http.GET();
    if (httpCode > 0) {
      // HTTP request successful
      String payload = http.getString();
      Serial.println(httpCode);
      Serial.println(payload);
      // Do something with data
    } else {
      Serial.println("HTTP request failed");
    }
    http.end();
  }
  // wait 1 minute before sending the next request
  delay(60000);
  }
*/

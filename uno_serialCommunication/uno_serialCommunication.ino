#include <ArduinoJson.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  StaticJsonDocument<200> doc;
  doc["sensor"] = "Arduino";
  doc["value"] = random(50);

  // Serialize JSON data to a string
  String jsonString;
  serializeJson(doc, jsonString);

  Serial.println(jsonString);
  delay(1000);
}

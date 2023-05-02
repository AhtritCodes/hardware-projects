#include <SoftwareSerial.h>

SoftwareSerial mySerial(D5, D6);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {

  if (mySerial.available() > 0) {
    byte data[20];
    int bytes = mySerial.readBytesUntil('\n', data, 20);
    data[bytes] = '\0';
    Serial.print("Data: ");
    Serial.println((char*)data);
  }
}

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ArduinoJson.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to I2C address for a 16 x 2 display

#define inputPin A2             // input (voltage) pin as A1
#define L 0.11                 // length of the beaker (in m)
#define r 0.042                 // radius of the beaker (in m) --> to calculate area of cross-section
#define R1 991                  // known resistance of the voltage divider circuit (1K used)
#define Vin 4.5                // supply voltage from Arduino in V (ideally 5V)
#define ONE_WIRE_BUS 8          // temperature value reading digital pin

/* declare variables */
/* readVol holds the voltage read from the analog input pin*/
int readVol;
/* actualVol <--- read voltage mapped to 0-5V level
    A <--- area of cross-section
    R2 <--- resistance within the solution considered after ionic dissociation
    EC <--- calculated Electrical Conductivity of the solution
    TDS <-- calculated Total Dissolved Solids from EC
    tempC <--- temperature of the solution in ºC
    tempF <--- temperature of the solution in ºF
*/
float actualVol, A, R2, EC, TDS, tempC, tempF;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

byte Degree[] = {
  B00000,
  B01110,
  B01010,
  B01110,
  B00000,
  B00000,
  B00000,
  B00000
};

void setup() {
  // put your setup code here, to run once:
  pinMode(inputPin, INPUT);
  sensors.begin();
  Serial.begin(9600);
  //  Serial.println("V2(V)\tEC(dS/m)\tTDS(g/L)\tTempC\tTempF");
  //  Serial.println("=====\t========\t========\t=====\t=====");

  startLCD();
}

void loop() {
  // put your main code here, to run repeatedly:

  // measure voltage and calculate TDS value of water
  calculateTDS();
  getTemperature();

  //  printValues();
  printValuesLCD();

  sendJsonData();

  delay(10000);
}

void sendJsonData() {

  StaticJsonDocument<200> doc;
  doc["temp"] = tempC;
  doc["tds"] = TDS;

  // Serialize JSON data to a string
  String jsonString;
  serializeJson(doc, jsonString);

  Serial.println(jsonString);
}


void calculateTDS() {
  readVol = analogRead(inputPin);
  //  actualVol = (5.0 / 1023) * readVol;
  actualVol = map(readVol, 0, 1023, 0, 5.0);
  R2 = (R1 * actualVol) / (Vin - actualVol);  // ohm
  A = (3.14 * (r * r));                       // m^2
  EC = (1.0 / ((R2 * A) / L));                // ohm/m = mho/m = S/m

  if (EC >= 0.5 && EC <= 5)
    TDS = 640 * EC * 10.0;                    // mg/L = 640 * dS/m
  else
    TDS = 800 * EC * 10.0;
}

void getTemperature() {
  // issue a global temperature request to all devices on the bus
  sensors.requestTemperatures();

  tempC = sensors.getTempCByIndex(0);
  tempF = ((tempC * 9.0) / 5.0) + 32.0;
}

//void printValues() {
//  //  Serial.print(R2); Serial.print("\t");
//  Serial.print(actualVol); Serial.print(" V"); Serial.print("\t");
//  Serial.print(EC); Serial.print(" dS/m"); Serial.print("\t");
//  Serial.print(TDS); Serial.print(" g/L"); Serial.print("\t");
//  Serial.print(tempC); Serial.write(0xC2); Serial.write(0xB0); Serial.print("\t");
//  Serial.print(tempF); Serial.write(0xC2); Serial.write(0xB0); Serial.println("\t");
//}

void startLCD() {
  lcd.init();
  lcd.clear();
  lcd.backlight();

  // custom character creation
  lcd.createChar(0, Degree);
}

void printValuesLCD() {
  lcd.setCursor(1, 0);
  lcd.print("TDS= " + String(TDS));
  lcd.setCursor(1, 1);
  lcd.print("Temp=" + String(tempC));
  lcd.setCursor(12, 1);
  lcd.write(byte(0));
  lcd.setCursor(13, 1);
  lcd.print(char(67));
}

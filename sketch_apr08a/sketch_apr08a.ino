//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

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


byte Degree2[] = {
  B00000,
  B11111,
  B11011,
  B11011,
  B11111,
  B00000,
  B00000,
  B00000
};

float value = 23.2;

void setup()
{
  lcd.init();                      // initialize the lcd
  lcd.clear();
  // Print a message to the LCD.
  lcd.backlight();

  //  lcd.createChar(0, Degree);
  //  lcd.createChar(1, Degree2);

  //  lcd.clear();
  //  lcd.setCursor(0, 0);
  //  lcd.print("Hello, world!");
  //  lcd.setCursor(0, 1);
  //  lcd.print("Ywrobot Arduino!");
  //  delay(1000);
  //  lcd.clear();
  //  lcd.print("Heart");
  //  lcd.setCursor(0, 2);
  //  lcd.print("Arduino LCM IIC 2004");
  //  lcd.setCursor(2, 3);
  //  lcd.print("Power By Ec-yuan!");
}


void loop()
{
  //  lcd.setCursor(0, 1);
  //  lcd.print(millis() / 1000);
  //  for (int i = 0; i < 15; i++) {
  //    lcd.setCursor(i, 1);
  //    lcd.write(byte(0));
  //    delay(1000);
  //    lcd.clear();
  //  }
  //  lcd.setCursor(0, 1);
  //  lcd.write(byte(0));
  //
  //  lcd.setCursor(2, 1);
  //  lcd.write(byte(1));
  //
  //  lcd.setCursor(3, 1);
  //  lcd.print(char(76));

  lcd.setCursor(1, 0);
  //  lcd.print(String(value));
  lcd.print("Value=" + String(value));

  lcd.setCursor(2,1);
  lcd.write("hi");
}

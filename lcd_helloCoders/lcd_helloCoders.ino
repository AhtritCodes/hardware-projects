#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to I2C addres for a 16x2 display

void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.clear();
  lcd.backlight();    // make sure backlight is on

  // Print a message on both lines of the LCD
  //  lcd.setCursor(2, 0);  // set cursor to character 2 on line 0
  //  lcd.print("Hello Papri!");
  //
  //  lcd.setCursor(2,1);   // set cursor to character 2 on line 1
  //  lcd.print("Roy");
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(2, 0);
  lcd.print("Roy");
  lcd.setCursor(4, 1);
  lcd.print("     ");

  delay(2000);

  lcd.setCursor(2, 0);
  lcd.print("      ");
  lcd.setCursor(4, 1);
  lcd.print("Papri");

  delay(2000);

}

// -----------------------------------------------
// LCD 16x2 HD44780-40
// -----------------------------------------------

#include <LiquidCrystal.h>

int D7_pin = 4;
int D6_pin = 5;
int D5_pin = 6;
int D4_pin =  7;
int EN_pin = 11;
int RS_pin = 12;

LiquidCrystal lcd(RS_pin, EN_pin, D4_pin, D5_pin, D6_pin, D7_pin);

void setup()
{
  lcd.begin(16, 2);  
}

void loop()
{
  lcd.clear();
  lcd.print("Hello Coders!!");
  lcd.setCursor(0, 1);
  lcd.print("Great Success!");

  delay(3000); 
  
  lcd.clear();
  lcd.print("Yeah...");
  lcd.setCursor(0, 1);
  lcd.print("Swagatam Roy");

  delay(3000); 
}
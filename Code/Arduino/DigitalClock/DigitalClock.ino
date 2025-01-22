#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows
String str = "Nick Snyder";
int hour = 12;
int minute;
int second;
bool half = false;

void setup()
{
  lcd.init(); // initialize the lcd
  lcd.backlight();
  lcd.clear();

  lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print(str);              // print message at (0, 0)
}

void loop()
{
  lcd.setCursor(0, 1);         // move cursor to   (0, 1)
  lcd.print("Time: ");
  if (hour < 10) {
    lcd.print(0);
  }
  lcd.print(hour);
  lcd.print(":");
  if (minute < 10) {
    lcd.print(0);
  }
  lcd.print(minute);
  lcd.print(":");
  if (second < 10) {
    lcd.print(0);
  }
  lcd.print(second);
  lcd.print("AM");

  //second = millis() / 1000;
  delay(1000);
  second = second + 1;

  if(second >= 60){
    second = 0;
    minute = minute + 1;
  }
  if(minute >= 60)
  {
    minute = 0;
    hour = hour + 1;
  }
  if(hour == 13)
  {
    hour = 1;
    if (half == false) {
      lcd.print("AM");
      half = true;
    }
    else
    {
      lcd.print("PM");
      half = false;
    }
  } 
}

#include <LiquidCrystal_74HC595.h>

#define DS 11
#define SHCP 13
#define STCP 12
#define RS 1
#define E 2
#define D4 3
#define D5 4
#define D6 5
#define D7 6

LiquidCrystal_74HC595 lcd(DS, SHCP, STCP, RS, E, D4, D5, D6, D7);

void setup() {
  lcd.begin(20, 4);
  lcd.print("Hello, World!");
}

void loop() {
  lcd.setCursor(0, 1);
  lcd.print(millis() / 1000);
  delay(1000);
}

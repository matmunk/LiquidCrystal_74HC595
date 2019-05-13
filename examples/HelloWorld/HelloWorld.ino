/*
The MIT License (MIT)

Copyright (c) 2019 Mathias Munk Hansen

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <LiquidCrystal_74HC595.h>

#define LATCH 9
#define RS 1
#define EN 2
#define D4 3
#define D5 4
#define D6 5
#define D7 6

LiquidCrystal_74HC595 lcd(LATCH, RS, EN, D4, D5, D6, D7);

void setup() {
    lcd.begin(20, 4);
    lcd.print("Hello, World!");
}

void loop() {
    lcd.setCursor(0, 1);
    lcd.print(millis() / 1000);
    delay(1000);
}

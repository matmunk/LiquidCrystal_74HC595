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

#ifndef LIQUID_CRYSTAL_74HC595_H
#define LIQUID_CRYSTAL_74HC595_H

#include <inttypes.h>
#include <Arduino.h>
#include <Print.h>
#include <SPI.h>

#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

class LiquidCrystal_74HC595 : public Print {
    public:
        LiquidCrystal_74HC595(uint8_t latch, uint8_t rs, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3);

        void begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS);
        void clear();
        void home();
        void noDisplay();
        void display();
        void noBlink();
        void blink();
        void noCursor();
        void cursor();
        void scrollDisplayLeft();
        void scrollDisplayRight();
        void leftToRight();
        void rightToLeft();
        void autoscroll();
        void noAutoscroll();
        void createChar(uint8_t, uint8_t[]);
        void setCursor(uint8_t, uint8_t); 
        void command(uint8_t);
        virtual size_t write(uint8_t);

        using Print::write;
    private:
        void send(uint8_t, uint8_t);
        void write4bits(uint8_t);
        void pulseEnable();
        void spiTransfer();

        uint8_t _latch;
        uint8_t _rs;
        uint8_t _enable;
        uint8_t _d0;
        uint8_t _d1;
        uint8_t _d2;
        uint8_t _d3;
        uint8_t _cols;
        uint8_t _rows;
        uint8_t _displayFunction;
        uint8_t _displayControl;
        uint8_t _displayMode;
        uint8_t _bitString;
};

#endif

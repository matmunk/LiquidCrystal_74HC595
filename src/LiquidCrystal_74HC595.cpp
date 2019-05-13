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

LiquidCrystal_74HC595::LiquidCrystal_74HC595(uint8_t latch, uint8_t rs, uint8_t e, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3) {
    _latch = latch;
    _rs = rs;
    _e = e;
    _d0 = d0;
    _d1 = d1;
    _d2 = d2;
    _d3 = d3;

    pinMode(_latch, OUTPUT);

    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV2);
    SPI.setDataMode(SPI_MODE0);
    SPI.setBitOrder(MSBFIRST);
}

void LiquidCrystal_74HC595::begin(uint8_t cols, uint8_t rows, uint8_t charsize) {
    _cols = cols;
    _rows = rows;

    _displayFunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
    if (_rows > 1) {
        _displayFunction |= LCD_2LINE;
    }
    if ((charsize != 0) && (_rows == 1)) {
        _displayFunction |= LCD_5x10DOTS;
    }

    delayMicroseconds(50000);

    write4bits(0x03);
    delayMicroseconds(4500);
    write4bits(0x03);
    delayMicroseconds(4500);
    write4bits(0x03);
    delayMicroseconds(150);
    write4bits(0x02);

    command(LCD_FUNCTIONSET | _displayFunction);

    _displayControl = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
    display();

    clear();

    _displayMode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
    command(LCD_ENTRYMODESET | _displayMode);
}

void LiquidCrystal_74HC595::clear() {
    command(LCD_CLEARDISPLAY);
    delayMicroseconds(2000);
}

void LiquidCrystal_74HC595::home() {
    command(LCD_RETURNHOME);
    delayMicroseconds(2000);
}

void LiquidCrystal_74HC595::setCursor(uint8_t col, uint8_t row) {
    uint8_t row_offsets[] = {0x00, 0x40, uint8_t(0x00 + _cols), uint8_t(0x40 + _cols)};
    if (row > _rows) {
        row = _rows - 1;
    }
    command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

void LiquidCrystal_74HC595::noDisplay() {
    _displayControl &= ~LCD_DISPLAYON;
    command(LCD_DISPLAYCONTROL | _displayControl);
}

void LiquidCrystal_74HC595::display() {
    _displayControl |= LCD_DISPLAYON;
    command(LCD_DISPLAYCONTROL | _displayControl);
}

void LiquidCrystal_74HC595::noCursor() {
    _displayControl &= ~LCD_CURSORON;
    command(LCD_DISPLAYCONTROL | _displayControl);
}

void LiquidCrystal_74HC595::cursor() {
    _displayControl |= LCD_CURSORON;
    command(LCD_DISPLAYCONTROL | _displayControl);
}

void LiquidCrystal_74HC595::noBlink() {
    _displayControl &= ~LCD_BLINKON;
    command(LCD_DISPLAYCONTROL | _displayControl);
}

void LiquidCrystal_74HC595::blink() {
    _displayControl |= LCD_BLINKON;
    command(LCD_DISPLAYCONTROL | _displayControl);
}

void LiquidCrystal_74HC595::scrollDisplayLeft() {
    command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

void LiquidCrystal_74HC595::scrollDisplayRight() {
    command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

void LiquidCrystal_74HC595::leftToRight() {
    _displayMode |= LCD_ENTRYLEFT;
    command(LCD_ENTRYMODESET | _displayMode);
}

void LiquidCrystal_74HC595::rightToLeft() {
    _displayMode &= ~LCD_ENTRYLEFT;
    command(LCD_ENTRYMODESET | _displayMode);
}

void LiquidCrystal_74HC595::autoscroll() {
    _displayMode |= LCD_ENTRYSHIFTINCREMENT;
    command(LCD_ENTRYMODESET | _displayMode);
}

void LiquidCrystal_74HC595::noAutoscroll() {
    _displayMode &= ~LCD_ENTRYSHIFTINCREMENT;
    command(LCD_ENTRYMODESET | _displayMode);
}

void LiquidCrystal_74HC595::createChar(uint8_t location, uint8_t charmap[]) {
    location &= 0x7;
    command(LCD_SETCGRAMADDR | (location << 3));
    for (int i = 0; i < 8; i++) {
        write(charmap[i]);
    }
}

inline void LiquidCrystal_74HC595::command(uint8_t value) {
    send(value, 0);
}

inline size_t LiquidCrystal_74HC595::write(uint8_t value) {
    send(value, 1);
    return 1;
}

void LiquidCrystal_74HC595::send(uint8_t value, uint8_t mode) {
    bitWrite(_bitString, _rs, mode);
    spiTransfer();
    write4bits(value >> 4);
    write4bits(value);
}

void LiquidCrystal_74HC595::pulseEnable() {
    bitWrite(_bitString, _e, 0);
    spiTransfer();
    delayMicroseconds(1);
    bitWrite(_bitString, _e, 1);
    spiTransfer();
    delayMicroseconds(1);
    bitWrite(_bitString, _e, 0);
    spiTransfer();
    delayMicroseconds(50);
}

void LiquidCrystal_74HC595::write4bits(uint8_t value) {
    bitWrite(_bitString, _d0, (value >> 0) & 0x01);
    bitWrite(_bitString, _d1, (value >> 1) & 0x01);
    bitWrite(_bitString, _d2, (value >> 2) & 0x01);
    bitWrite(_bitString, _d3, (value >> 3) & 0x01);
    spiTransfer();
    pulseEnable();
}

void LiquidCrystal_74HC595::spiTransfer() {
    SPI.setClockDivider(SPI_CLOCK_DIV2);
    SPI.setDataMode(SPI_MODE0);
    SPI.setBitOrder(MSBFIRST);
    digitalWrite(_latch, LOW);
    SPI.transfer(_bitString);
    digitalWrite(_latch, HIGH);
}

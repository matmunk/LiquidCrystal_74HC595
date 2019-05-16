#ifndef LIQUID_CRYSTAL_74HC595_H
#define LIQUID_CRYSTAL_74HC595_H

#include <Arduino.h>

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
        LiquidCrystal_74HC595(uint8_t ds, uint8_t shcp, uint8_t stcp,
                uint8_t rs, uint8_t e, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3);
        void begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS);
        void clear();
        void home();
        void noDisplay();
        void display();
        void noCursor();
        void cursor();
        void noBlink();
        void blink();
        void scrollDisplayLeft();
        void scrollDisplayRight();
        void leftToRight();
        void rightToLeft();
        void autoscroll();
        void noAutoscroll();
        void createChar(uint8_t location, uint8_t charmap[]);
        void setCursor(uint8_t col, uint8_t row);
        void command(uint8_t value);
        virtual size_t write(uint8_t value);
        using Print::write;
    private:
        void send(uint8_t value, uint8_t mode);
        void pulseEnable();
        void write4bits(uint8_t value);
        void transfer();
        uint8_t _ds;
        uint8_t _shcp;
        uint8_t _stcp;
        uint8_t _rs;
        uint8_t _e;
        uint8_t _d0;
        uint8_t _d1;
        uint8_t _d2;
        uint8_t _d3;
        uint8_t _cols;
        uint8_t _rows;
        uint8_t _displayControl;
        uint8_t _displayMode;
        uint8_t _register;
};

#endif

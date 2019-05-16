#include <LiquidCrystal_74HC595.h>

LiquidCrystal_74HC595::LiquidCrystal_74HC595(uint8_t ds, uint8_t shcp, uint8_t stcp,
        uint8_t rs, uint8_t e, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3) {
    _ds = ds;
    _shcp = shcp;
    _stcp = stcp;
    _rs = rs;
    _e = e;
    _d0 = d0;
    _d1 = d1;
    _d2 = d2;
    _d3 = d3;

    pinMode(_ds, OUTPUT);
    pinMode(_shcp, OUTPUT);
    pinMode(_stcp, OUTPUT);
}

void LiquidCrystal_74HC595::begin(uint8_t cols, uint8_t rows, uint8_t charsize) {
    _cols = cols;
    _rows = rows;
    _displayControl = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
    _displayMode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;

    delayMicroseconds(50000);
    write4bits(0x03);
    delayMicroseconds(4500);
    write4bits(0x03);
    delayMicroseconds(4500);
    write4bits(0x03);
    delayMicroseconds(150);
    write4bits(0x02);

    if (_rows > 1) {
        command(LCD_FUNCTIONSET | LCD_4BITMODE | LCD_2LINE | LCD_5x8DOTS);
    } else if (_rows == 1 && charsize != 0) {
        command(LCD_FUNCTIONSET | LCD_4BITMODE | LCD_1LINE | LCD_5x10DOTS);
    } else {
        command(LCD_FUNCTIONSET | LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS);
    }

    command(LCD_DISPLAYCONTROL | _displayControl);
    clear();
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
    for (uint8_t i = 0; i < 8; i++) {
        write(charmap[i]);
    }
}

void LiquidCrystal_74HC595::setCursor(uint8_t col, uint8_t row) {
    uint8_t row_offsets[] = {0x00, 0x40, uint8_t(0x00 + _cols), uint8_t(0x40 + _cols)};
    if (row > _rows) {
        row = _rows - 1;
    }
    command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

inline void LiquidCrystal_74HC595::command(uint8_t value) {
    send(value, 0);
}

inline size_t LiquidCrystal_74HC595::write(uint8_t value) {
    send(value, 1);
    return 1;
}

void LiquidCrystal_74HC595::send(uint8_t value, uint8_t mode) {
    bitWrite(_register, _rs, mode);
    transfer();
    write4bits(value >> 4);
    write4bits(value);
}

void LiquidCrystal_74HC595::pulseEnable() {
    bitWrite(_register, _e, 0);
    transfer();
    delayMicroseconds(1);
    bitWrite(_register, _e, 1);
    transfer();
    delayMicroseconds(1);
    bitWrite(_register, _e, 0);
    transfer();
    delayMicroseconds(50);
}

void LiquidCrystal_74HC595::write4bits(uint8_t value) {
    bitWrite(_register, _d0, (value >> 0) & 1);
    bitWrite(_register, _d1, (value >> 1) & 1);
    bitWrite(_register, _d2, (value >> 2) & 1);
    bitWrite(_register, _d3, (value >> 3) & 1);
    transfer();
    pulseEnable();
}

void LiquidCrystal_74HC595::transfer() {
    digitalWrite(_stcp, LOW);
    shiftOut(_ds, _shcp, MSBFIRST, _register);
    digitalWrite(_stcp, HIGH);
}

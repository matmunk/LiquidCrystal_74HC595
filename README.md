# LiquidCrystal_74HC595 #

Communicate with HD44780 (or compatible) LCDs through a 74HC595 shift register over SPI. This reduces the number of pins needed to control the LCD from 6 to 3 pins (in 4 bit mode). The mapping from pins on the LCD to pins on the shift register is configurable, so this library should also work with other shift registers. Mostly compatible with the default LiquidCrystal library.

## Usage ##

Connect the LCD to your Arduino as shown below. The connections from pins RS, E, D4, D5, D6, and D7 on the LCD to the shift register must be explicitly defined. In this example they are as follows:

```
RS -> 1
EN -> 2
D4 -> 3
D5 -> 4
D6 -> 5
D7 -> 6
```

Additionally, the pin on the Arduino connected to the latch pin (aka ST_CP) on the shift register is also required (pin 9 in this example).

![LCD connected to Arduino via 74HC595 shift register](/extras/example.png)

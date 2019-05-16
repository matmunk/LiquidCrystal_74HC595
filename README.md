# LiquidCrystal_74HC595 #

This library allows an Arduino board to control most LCDs (Hitachi HD44780 based or compatible) through a 74HC595 shift register. This provides a very cost effective way of reducing the number of pins needed to control an LCD (from 6 to 3 pins in 4 bit mode).

It is based on the default `LiquidCrystal` library, and is almost a drop-in replacement with the only differences being three additional parameters required in the constructor and no support for 8 bit mode.

The motivation behind creating this library is that all existing libraries assume a static mapping between the pins on the LCD and the shift register. This can be impractical depending on the physical layout of the components, and also limits the number of other shift registers which can be used.

## Basic example ##

Connect an LCD to your Arduino as shown below. The connections from pins RS, E, D4, D5, D6, and D7 on the LCD to the shift register must be explicitly defined. In this example they are as follows:

```
RS -> 1
E  -> 3
D4 -> 4
D5 -> 5
D6 -> 6
D7 -> 7
```

where the right-hand side denotes the pin on the shift register. Additionally, the pins on the Arduino connected to the data pin (DS), clock pin (SH_CP), and latch pin (ST_CP) on the shift register are also required. In this example these are pins 11, 13, and 12, respectively.

Using the library is straightforward:

```
#include <LiquidCrystal_74HC595.h>

LiquidCrystal_74HC595 lcd(11, 13, 12, 1, 3, 4, 5, 6, 7);

void setup() {
  lcd.begin(20, 4);
  lcd.print("Hello, World!");
}

void loop() {}
```

Everything else is identical to the official library. Please refer to the [documentation](https://www.arduino.cc/en/Reference/LiquidCrystal) for more information.

![LCD connected to Arduino via 74HC595 shift register](/extras/example.png)

## LCD backpack ##

The following example shows how to build a poor man's version of the I²C/SPI LCD backpacks [commonly available](https://www.adafruit.com/product/292) on the internet.

![LCD backpack](/extras/backpack.png)

The backpack plugs directly into the back of the LCD using the 16 pin female header. It is built using a small piece of veroboard containing a circuit similar to the one shown in the first example. Note that the copper tracks must be cut above the negative lead of the potentiometer, along the entire length of the 74HC595, and under the four unconnected female headers in the center.

In this example, being able to reorder the pins is necessary. We have the following connections:

```
RS -> 7
E  -> 6
D4 -> 4
D5 -> 3
D6 -> 2
D7 -> 1
```

#### Parts list ####

* Veroboard
* 74HC595 shift register
* 16 pin female socket
* 5 pin screw terminal
* 10k potentiometer
* 0.1 μF ceramic capacitor
* 220 Ω resistor
* Jumper wires

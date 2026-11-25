# Sim-Racing-Peripherals
This is an Arduino-based project that combines Logitech G29 pedals, shifter, and an analog handbrake into a single USB output. 

There is also a switch that changes the handbrake output to a button, for games that don't support analog handbrakes.

All of these functions existed as separate projects, I just combined them into one thing to minimize the amount of USB plugs needed.

This project assumes you already have working Logitech peripherals, and a handbrake that produces an analog output signal.


PARTS:

-Arduino Pro Micro or Leonardo (or other ATMega 32U4 based processor) *DOESN'T WORK WITH ARDUINO UNO, NANO, OR OTHER ATMega 328P BOARDS*

-Male DB9 connector

-Female DB9 connector

-NA151 or similar load cell

-INA333 amplifier (w/ CNCDan mods)

-SPST switch

-Protoboard

-some wires


SOURCES:

CNCDan's sim racing peripherals projects: 

  https://github.com/dmcke5/H-Shifter/tree/main
  
  https://github.com/dmcke5/Load-Cell-Handbrake

PartsNotIncluded projects:

  https://www.partsnotincluded.com/how-to-build-a-diy-logitech-shifter-usb-adapter/
  
  https://www.partsnotincluded.com/how-to-build-a-diy-logitech-pedals-usb-adapter/

WIRING:

Connect parts per this diagram:

DB-9 PINOUTS

[X - DB9 PIN | ARDUINO PIN]

SHIFTER

1 - N/C

2 - Reverse Pin | 2

3 - connect to DB-9 pin 7

4 - X axis      | A6 (pin 4)

5 - N/C

6 - GND

7 - connect to DB-9 pin 3

8 - Y axis      | A7 (pin 6)

9 - +5V

PEDALS

1 - GND

2 - Throttle    | A3

3 - Brake       | A2

4 - Clutch      | A0

5 - N/C

6 - N/C

7 - N/C

8 - N/C

9 - +5V

HANDBRAKE ANALOG PIN TO A1

HANDBRAKE MODE SWITCH TO PIN 7

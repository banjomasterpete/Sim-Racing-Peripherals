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
-some wires

SOURCES:
CNCDan's sim racing peripherals projects: 
  https://github.com/dmcke5/H-Shifter/tree/main
  https://github.com/dmcke5/Load-Cell-Handbrake
PartsNotIncluded projects:
  https://www.partsnotincluded.com/how-to-build-a-diy-logitech-shifter-usb-adapter/
  https://www.partsnotincluded.com/how-to-build-a-diy-logitech-pedals-usb-adapter/

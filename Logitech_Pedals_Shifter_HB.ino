#include <SimRacing.h>
#include <Joystick.h>

/*
DB-9 PINOUTS
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
*/

bool HBdigital = false; //set to true if using handbrake as a digital output

const int Pin_HBdigital  = 7;
const int Pin_ShifterX   = A6;  // arduino pin 4
const int Pin_ShifterY   = A7;  // arduino pin 6
const int Pin_ShifterRev = 2;   

const int Pin_Gas    = A3; //RYaxis
const int Pin_Brake  = A2; //RXaxis
const int Pin_Clutch = A0; //Zaxis
const int Pin_HB     = A1; //Xaxis
SimRacing::LogitechPedals pedals(Pin_Gas, Pin_Brake, Pin_Clutch);

SimRacing::LogitechShifter shifter(
	Pin_ShifterX, Pin_ShifterY,
	Pin_ShifterRev
);

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,
  JOYSTICK_TYPE_JOYSTICK, 8, 0,        //type, num buttons (gears 1-6, reverse, HB digital), num hat switches
  true, false,                         // handbrake (X), no axes on Y
  pedals.hasPedal(SimRacing::Clutch),  // include Z axis for the clutch pedal
	pedals.hasPedal(SimRacing::Brake),   // include Rx axis for the brake pedal
	pedals.hasPedal(SimRacing::Gas),     // include Ry axis for the gas pedal
  false, false, false,                 // rudder, throttle, accelerator
  false, false                         // brake, steering
);

const int Gears[] = { 1, 2, 3, 4, 5, 6, -1 };
const int NumGears = sizeof(Gears) / sizeof(Gears[0]);

const int ADC_Max = 1023;

//handbrake variables
int lowerLimit = 20;
int upperLimit = 310;
int handbrakeCur;
int handbrakeLast = lowerLimit;
int threshold = 100;

void setup() {
  shifter.begin();
  pedals.begin();
  Joystick.begin(false);  // 'false' to disable auto-send

  Joystick.setXAxisRange(0, ADC_Max);
  Joystick.setZAxisRange(0, ADC_Max);
	Joystick.setRxAxisRange(0, ADC_Max);
	Joystick.setRyAxisRange(0, ADC_Max);

  pinMode (Pin_HBdigital, INPUT_PULLUP);

  if (digitalRead (Pin_HBdigital) == HIGH) {
    HBdigital = true;
  }

	updateJoystick();  // send initial state

}

void loop() {
  shifter.update();
  pedals.update();
  handbrakeCur = analogRead (Pin_HB);
  if (pedals.positionChanged() || shifter.gearChanged() || handbrakeCur != handbrakeLast) {  
    updateJoystick();
  }
}

void updateJoystick () {
  for (int i = 0; i < NumGears; i++) {
		if (shifter.getGear() == Gears[i]) {
			Joystick.pressButton(i);
		}
		else {
			Joystick.releaseButton(i);
		}
	}

	if (pedals.hasPedal(SimRacing::Gas)) {
		int gasPedal = pedals.getPosition(SimRacing::Gas, 0, ADC_Max);
		Joystick.setRyAxis(gasPedal);
	}

	if (pedals.hasPedal(SimRacing::Brake)) {
		int brakePedal = pedals.getPosition(SimRacing::Brake, 0, ADC_Max);
		Joystick.setRxAxis(brakePedal);
	}

	if (pedals.hasPedal(SimRacing::Clutch)) {
		int clutchPedal = pedals.getPosition(SimRacing::Clutch, 0, ADC_Max);
		Joystick.setZAxis(clutchPedal);
	}

  if (HBdigital == true) {
    if (handbrakeCur > threshold) {
      Joystick.pressButton(7);
    }
    else {
      Joystick.releaseButton(7);
    }
  }
  
  handbrakeLast = handbrakeCur;

  Joystick.setXAxis(map(handbrakeCur, lowerLimit, upperLimit, 0, ADC_Max));

  Joystick.sendState();
}
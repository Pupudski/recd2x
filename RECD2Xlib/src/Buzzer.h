#ifndef Buzzer_h
#define Buzzer_h

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

class Buzzer {
	public:
		Buzzer(int pin);
		void bootup();
		void arming();
		void disarming();
		void deploy();
		void idle();
		void error(int y);
		void debugRec();
		void debugDisIdle();
	private:
		int _pin;
};

#endif
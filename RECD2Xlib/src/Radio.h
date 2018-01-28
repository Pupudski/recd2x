#ifndef Radio_h
#define Radio_h

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

#include "RF24.h"
#include "Wire.h"

class Radio {
	public:
		Radio(int pinCE, int pinCS);
		bool begin();
		bool checkArm();
	private:
		RF24 _rf; //might be problematic pt1/2 (NOTE)
	    int _codeReceived;
		int _armCode = 111;
		int _disarmCode = 222;
		bool _output;
};

#endif
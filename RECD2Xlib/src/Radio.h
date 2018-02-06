#ifndef Radio_h
#define Radio_h


#include "Arduino.h"


#include "RF24.h"
#include "Wire.h"

class Radio {
	public:
		Radio(int pinCE, int pinCS);
		bool begin();
		int checkArm();
	private:
		RF24 _rf; //might be problematic pt1/2 (NOTE)
	  	int _codeReceived;
		int _armCode = 1;
		int _disarmCode = 2;
		int _offCode = 3;
		bool _output;
};

#endif
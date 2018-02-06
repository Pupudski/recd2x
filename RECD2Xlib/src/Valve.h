#ifndef Valve_h
#define Valve_h

#include "Arduino.h"
#include "Servo.h"

class Valve {
	public:
		Valve(int pin, int closedPos, int openPos);
		void begin();
		void open();
		void close();
	private:
		Servo _servo;
		int _closedPos;
		int _openPos;
		int _pin;
};

#endif
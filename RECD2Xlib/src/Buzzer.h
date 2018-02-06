#ifndef Buzzer_h
#define Buzzer_h

#include "Arduino.h"


class Buzzer {
	public:
		Buzzer(int pin);
		void bootup();
		void arming();
		void disarming();
		void deploy();
		void idle();
		void error(int y);
		void findMe();
		void playTone(int note);
		/*
		void debugRec();
		void debugDisIdle();
		*/
	private:
		int _pin;
};

#endif
#include "Buzzer.h"

Buzzer::Buzzer(int pin){
	pinMode(pin, OUTPUT);
	_pin = pin;
}
void Buzzer::bootup(){ //low, low, low-high (~1.4s)
	tone(_pin, 2300, 250);
    delay(500);
    tone(_pin, 2300, 250);
	delay(500);
    tone(_pin, 2300, 125);
	delay(250);
	tone(_pin, 2500, 125);
}
void Buzzer::arming(){ //upward siren x2 (~1.2s)
	for(int y=0;y<2;y++){
		for(int x=0;x<200;x++){
		  tone(_pin,2300+x);
		  delay(3);
		}
	}
	noTone(_pin);
}
void Buzzer::disarming(){ //downward siren x2 (~1.2s)
	for(int y=0;y<2;y++){
		for(int x=0;x<200;x++){
			tone(_pin, 2500 - x);
			delay(3);
		}
    }
    noTone(_pin);
}
void Buzzer::deploy(){ //up & down siren (~0.4s)
	for(int x=0;x<200;x++){
		tone(_pin, 2300 + x);
		delay(1);
	}
	for(int x=0;x<200;x++){
		tone(_pin, 2500 - x);
		delay(1);
	}
}
void Buzzer::idle(){ //tiny little blip
	tone(_pin, 2400, 20);
}
void Buzzer::findMe(){ //two quick blips
	tone(_pin, 2400, 100);
	delay(200);
	tone(_pin, 2400, 100);
	delay(200);
}
void Buzzer::error(int y){ //Fire Alarm-esque alternating honk x3 + beep error code repeatedly
	for(int x=0;x<3;x++){
		tone(_pin, 2300);
		delay(250);
		tone(_pin, 2500);
		delay(250);
	}
	delay(1000);
	while(1){
		for(int i=0;i<y;i++){
			tone(_pin, 2400, 250);
			delay(500);
		}
		delay(2000);
	}
}
void Buzzer::playTone(int note){
	tone(_pin, note, 100);
	delay(500);
}
/*
void Buzzer::debugRec(){ //meh
	tone(_pin, 2400, 100);
	delay(200);
	tone(_pin, 2400, 500);
}
void Buzzer::debugDisIdle(){ //meh
	tone(_pin, 2400, 20);
	delay(40);
	tone(_pin, 2400, 100);
}
*/
#include "Buzzer.h"

Buzzer::Buzzer(int pin){
	pinMode(pin, OUTPUT);
	_pin = pin;
}
void Buzzer::bootup(){ //short low-high beep
	tone(_pin, 2300, 125);
    delay(250);
    tone(_pin, 2500, 125);
}
void Buzzer::arming(){ //upward siren x2
	for(int y=0;y<2;y++){
		for(int x=0;x<200;x++){
		  tone(_pin,2300+x);
		  delay(4);
		}
	}
	noTone(_pin);
}
void Buzzer::disarming(){ //downward siren x2
	for(int y=0;y<2;y++){
		for(int x=0;x<200;x++){
			tone(_pin, 2500 - x);
			delay(4);
		}
    }
    noTone(_pin);
}
void Buzzer::deploy(){ //long loud honk
	tone(_pin, 2400, 500);
}
void Buzzer::idle(){ //tiny little blip
	tone(_pin, 2400, 20);
}
void Buzzer::error(int y){ //warble x3 + beep error code,
	for(int x=0;x<3;x++){ //delay 2 secs, repeat
		for(int a=0;a<125;a++){
			tone(_pin, 2300, 2);
			delay(4);
			tone(_pin, 2500, 2);
			delay(4);
		}
		delay(500);
	}
	while(1){
		for(int i=0;i<y;i++){
			tone(_pin, 2400, 250);
			delay(500);
		}
		delay(2000);
	}
}
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
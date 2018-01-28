#include "Valve.h"

Valve::Valve(int pin, int closedPos, int openPos){
	_pin = pin;
	_closedPos = closedPos;
	_openPos = openPos;
}
void Valve::begin() {
	_servo.attach(_pin);
	_servo.write(_closedPos);
}
void Valve::open(){
	_servo.write(_openPos);
}
void Valve::close(){
	_servo.write(_closedPos);
}

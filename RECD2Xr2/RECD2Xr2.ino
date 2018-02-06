/*
 Name:		RECD2Xr2.ino
 Created:	9/19/2017 8:24:20 PM
 Author:	Alex
*/

#include "RECD2Xlib.h"
#include "Arduino.h"

Buzzer buzz(9); //pin
Altimeter alt;
Radio radio(8, 10); //ce pin, cs pin
FlightLog flightLog(7, "FLIGHTDATA.txt", 5000); //pin, filename, save freq
Valve servo(3, 90, 60); //pin, closed pos, open pos

const float deployAlt = 243.84;
const int minSpdThresh = -3;
const int maxSpdThresh = 30;
const int minAltThresh = 50;
const float etaThresh = 1;
const int refresh = 20; //refresh rate in milliseconds

//=====================

bool deployed = false;
bool landed = false;
float prevTimeEst = 100;

float altitude = 0;
float spd = 0;
bool armed = false;
float timeEst = 0;
float lastSave = 0;
float lastCycle = 0;
int codeReceived = 0;

//#############################################################################

void(*resetFunc) (void) = 0;

bool checkDeploy() { //check if parachute should be deployed now.
	predictTime();
	if(spd < maxSpdThresh && altitude > minAltThresh){
		if(altitude > deployAlt){
			deployChute();
			flightLog.addMsg("OVER ALT");
		} else if(spd < minSpdThresh){
			deployChute();
			flightLog.addMsg("LOW SPD");
		} else if(timeEst < etaThresh){
			deployChute();
			flightLog.addMsg("PREDICT");
		}
	}
}

bool predictTime() { //predicts time (in s) until rocket will reach target altitude, stores it in variable 'timeEst', returns false if "nan"
	prevTimeEst = timeEst;
	timeEst = (spd - sqrt(sq(spd) - 19.6f * (deployAlt - altitude))) / 9.8f; //Quad. Eq with  a=grav/2,b=-spd,c=target-alt
	if (isnan(timeEst)) { //if the rocket will not reach target altitude, use previous time estimate, return false (<-sometimes cries wolf, not reliable)
		timeEst = prevTimeEst;
		return false;
	}
	return true;
}

void deployChute() {
	servo.open();
	buzz.deploy();
	flightLog.addMsg("CHUTE OUT");
	flightLog.save();
	deployed = true;
}

void waitForCycle() { //keeps the loop running at the same interval, checks for signals while waiting.
	flightLog.addDataTriple(altitude,spd,millis()); //Prints altitude, speed, and time in CSV form
	flightLog.checkSave();
	while (millis() - refresh < lastCycle) {
		if(radio.checkArm() == true){
			setArmedState();
		} else if () //TODO FIX ME PLS - doesn't actually do something useful atm.
	}
	lastCycle = millis();
}

void setArmedState(){
	armed = true;
	buzz.arming();
	flightLog.begin();
}
void turnOff(){
	armed = false;
	while(1){}/*
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  	noInterrupts();
  	sleep_enable();
  	interrupts();             // guarantees next instruction executed
  	sleep_cpu();              // sleep within 3 clock cycles of above*/
}

//######################################################################################

void setup() {
	alt.begin();
	radio.begin();
	servo.begin();
	buzz.bootup(); //plays bootup noise
	flightLog.save();
	/*Serial.begin(9600); //NOT HEADLESS*/
}

void loop() {
	if (!armed) {
		alt.calibrate();
		if(radio.checkArm() == true){
			setArmedState();
		}
	} else if(armed && !landed) {
		altitude = alt.getAlt();
		spd = alt.getSpd();/*
		Serial.print(altitude); //NOT HEADLESS
		Serial.print(","); //NOT HEADLESS
		Serial.print(spd); //NOT HEADLESS
		Serial.print(","); //NOT HEADLESS
		Serial.println(timeEst); //NOT HEADLESS*/
		if (!deployed) {
			checkDeploy();
		}
	} else if (landed){
		buzz.findMe();
		delay(3000);
	}
	if(radio.checkArm() == false){
		flightLog.addMsg("SHUTDOWN");
		flightLog.save();
		turnOff();
	}
	waitForCycle();
}
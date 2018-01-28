/*
 Name:		RECD2Xr2.ino
 Created:	9/19/2017 8:24:20 PM
 Author:	Alex
*/

#include "RECD2Xlib.h"

Buzzer buzz(9); //pin
Altimeter alt;
Radio radio(8, 10); //ce pin, cs pin
FlightLog flightLog(7, "FLIGHTDATA.txt", 5000); //pin, filename, save freq
Valve servo(3, 90, 60); //pin, closed pos, open pos

const float deployAlt = 0.5;
const float spdThresh = -3;
const float etaThresh = 0.1;
const int refresh = 20; //refresh rate in milliseconds

//=====================

bool deployed = false;
bool initial = true;
float prevTimeEst = 100;

float altitude = 0;
float spd = 0;
bool armed = false;
float timeEst = 0;
float lastSave = 0;
float lastCycle = 0;
int codeReceived = 0;

//#############################################################################
bool bootDebug() { //starts SD logger / serial monitor
	Serial.begin(9600);
	Serial.println();
	for (int q = 0; q<3; q++) {
		for (int p = 0; p<80; p++) {
			Serial.print("=");
		}
	}
	Serial.println();
	Serial.println("Debug booted.");
}

void(*resetFunc) (void) = 0;

bool checkDeploy() { //check if parachute should be deployed now.
	predictTime();
	if (altitude > deployAlt) { //target altitude exceeded
		deployChute();
	} else if (spd < spdThresh) { //speed is too low
		deployChute();
	} else if (timeEst < etaThresh && altitude > 100) { //about to reach target altitude
		deployChute();
	}
}

bool predictTime() { //predicts time until rocket will reach target altitude, stores it in variable 'timeEst'
	prevTimeEst = timeEst;
	timeEst = (spd - sqrt(sq(spd) - 19.6f * (deployAlt - altitude))) / 9.8f;
	if (isnan(timeEst)) { //if the rocket will not reach target altitude, use previous time estimate, return false
		timeEst = prevTimeEst;
		return false;
	}
	return true;
}

void deployChute() {
	buzz.deploy();
	servo.open();
	deployed = true;
}

void waitForCycle() { //keeps the loop running at the same interval, checks for signals while waiting.
	while (millis() - refresh < lastCycle) {
		radio.checkArm();
	}
	lastCycle = millis();
}

//######################################################################################

void setup() {
	alt.begin();
	flightLog.begin();
	radio.begin();
	servo.begin();
	buzz.bootup();
	Serial.begin(9600);
}

void loop() {
	if (!armed) {
		alt.calibrate();
	} else {
		altitude = alt.getAlt();
		spd = alt.getSpd();
		Serial.print(altitude);
		Serial.print(",");
		Serial.println(spd);
		if (!deployed) {
			checkDeploy();
		}
	}
	waitForCycle();
}

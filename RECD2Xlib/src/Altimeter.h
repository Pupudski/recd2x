#ifndef Altimeter_h
#define Altimeter_h
 
/*#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif
*/
#include "Arduino.h"
#include "MS5611.h"
#include "SimpleKalmanFilter.h"

class Altimeter {
public:
	Altimeter();
	bool begin();
	void calibrate();
	float getAlt();
	float getSpd();
private:
	MS5611 _ms5611;
	float _ground;
	float _altitude;
	float _prevAlt;
	float _spd;
	float _lastAltMeas;
	SimpleKalmanFilter _groundKalman;
	SimpleKalmanFilter _altKalman;
	SimpleKalmanFilter _spdKalman;
};

#endif
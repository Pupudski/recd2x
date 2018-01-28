#include "Altimeter.h"

Altimeter::Altimeter() : _groundKalman(1.0f,1.0f,0.03f) , _altKalman(1.0f,1.0f,0.3f) , _spdKalman(1.0f,1.0f,0.2f){
}
bool Altimeter::begin() {
	_ground = _groundKalman.updateEstimate(_ms5611.readPressure());
	return _ms5611.begin(MS5611_STANDARD);
}


void Altimeter::calibrate(){
	_ground = _groundKalman.updateEstimate(_ms5611.getAltitude(_ms5611.readPressure()));
}
float Altimeter::getAlt(){
	_altitude = _altKalman.updateEstimate(_ms5611.getAltitude(_ms5611.readPressure()) - _ground);
	return _altitude;
}
float Altimeter::getSpd(){
	if(_prevAlt == 0){
		_spd = _spdKalman.updateEstimate(0);
	}
	else{
		_spd = _spdKalman.updateEstimate((_altitude - _prevAlt)/((millis()-_lastAltMeas)/1000));
		_lastAltMeas = millis();
	}
	_prevAlt = _altitude;
	return _spd;
}
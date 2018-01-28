#include "FlightLog.h"

FlightLog::FlightLog(int pin, String filename, int autoSave){
	_pin = pin;
	_filename = filename;
	_saveFreq = autoSave;
}

void FlightLog::begin() {
	digitalWrite(_pin, HIGH);
	SD.begin(_pin);
	_datalog = SD.open(_filename, FILE_WRITE);
	for (int x = 0; x<100; x++) {
		_datalog.print("=");
	}
	_datalog.println();
}

void FlightLog::checkSave(){
	if(_lastSave + _saveFreq < millis()){
		_datalog.close();
		_datalog = SD.open(_filename, FILE_WRITE);
		_lastSave = millis();
	}
}

void FlightLog::addData(String data){
	_datalog.print(data);
	checkSave();
}

void FlightLog::addDataLn(String data){
	_datalog.println(data);
	checkSave();
}

void FlightLog::save(){
	_datalog.close();
	_datalog = SD.open(_filename, FILE_WRITE);
	_lastSave = millis();
}
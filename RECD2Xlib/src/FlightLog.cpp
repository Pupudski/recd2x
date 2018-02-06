#include "FlightLog.h"


FlightLog::FlightLog(int pin, String filename, int autoSave){
	_pin = pin;
	_filename = filename;
	_saveFreq = autoSave;
	_MsgPref = "==";
}

void FlightLog::begin() {
	digitalWrite(_pin, HIGH);
	SD.begin(_pin);
	_datalog = SD.open(_filename, FILE_WRITE);

	_datalog.println(); //Writes "==START" with empty lines either end upon startup.
	_datalog.print(_MsgPref);
	_datalog.println("START");
	_datalog.println();
}

void FlightLog::checkSave(){
	if(_lastSave + _saveFreq < millis()){
		_datalog.close();
		_datalog = SD.open(_filename, FILE_WRITE);
		_lastSave = millis();
	}
}

void FlightLog::addData(String data){ //Writes data, DOES NOT start new line
	_datalog.print(data);
}

void FlightLog::addDataLn(String data){ //Writes data, starts new line
	_datalog.println(data);
}

void FlightLog::addDataTriple(float data1, float data2, float data3){ //Writes 3 pieces of data in CSV format to SD card.
	_datalog.print(data1);
	_datalog.print(",");
	_datalog.print(data2);
	_datalog.print(",");
	_datalog.println(data3);
}

void FlightLog::addMsg(String data){ //Writes message with prefix, starts new line.
	_datalog.print(_MsgPref);
	_datalog.println(data);
}

void FlightLog::save(){
	_datalog.close();
	_datalog = SD.open(_filename, FILE_WRITE);
	_lastSave = millis();
}
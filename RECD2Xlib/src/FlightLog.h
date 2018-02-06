#ifndef FlightLog_h
#define FlightLog_h
 
#include "Arduino.h"

#include "SD.h"
#include "SPI.h"

class FlightLog {
	public:
		FlightLog(int pin, String filename, int autoSave);
		void begin();
		void addData(String data);
		void addDataLn(String data);
		void addMsg(String data);
		void save();
		void checkSave();
		void addDataTriple(float data1, float data2, float data3);
	private:
		File _datalog;
		String _filename;
		int _saveFreq;
		int _lastSave;
		int _pin;
		String _MsgPref;
};

#endif
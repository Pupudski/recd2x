#ifndef FlightLog_h
#define FlightLog_h
 
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

#include "SD.h"
#include "SPI.h"

class FlightLog {
	public:
		FlightLog(int pin, String filename, int autoSave);
		void begin();
		void addData(String data);
		void addDataLn(String data);
		void save();
	private:
		File _datalog;
		String _filename;
		int _saveFreq;
		int _lastSave;
		int _pin;
		void checkSave();
};

#endif
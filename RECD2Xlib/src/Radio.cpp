#include "Radio.h"

Radio::Radio(int pinCE, int pinCS): _rf(pinCE, pinCS){
}
bool Radio::begin() {
	_output = _rf.begin();
	byte _addresses[][6] = { "1Node","2Node" };
	_rf.openReadingPipe(1, _addresses[0]);
	_rf.startListening();
	return _output;
}
bool Radio::checkArm(){
	if(_rf.available()){
		_codeReceived = 0;
		while (_rf.available()) {
			_rf.read(&_codeReceived, sizeof(int));
	    }
		if(_codeReceived = _armCode){
			return true;
		}
		else if(_codeReceived = _disarmCode){
			return false;
		}
	}
	return false;
}

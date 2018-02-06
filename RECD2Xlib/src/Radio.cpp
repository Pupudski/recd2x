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
int Radio::checkArm(){
	if(_rf.available()){
		_codeReceived = 0;
		while (_rf.available()) {
			_rf.read(&_codeReceived, sizeof(int));
	    }
		if(_codeReceived == _armCode){
			return 1;
		}
		else if(_codeReceived == _disarmCode){
			return 2;
		}
		else if(_codeReceived == _turnOffCode){
			return 3;
		}
	}
	return 0;
}

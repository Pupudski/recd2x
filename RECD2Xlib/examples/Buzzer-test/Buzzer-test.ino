#include "Buzzer.h"
Buzzer buzz(9);

void setup(){
    buzz.bootup();
    delay(1000);
}

void loop(){
    buzz.idle();
    delay(980);
}
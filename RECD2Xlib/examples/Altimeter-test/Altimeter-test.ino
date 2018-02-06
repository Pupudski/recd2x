#include "Altimeter.h"
#include "Buzzer.h"

Altimeter alt;
Buzzer buzz(9);
float note;

void setup(){ //Calibrates altimeter, starts console.
    alt.begin();
    buzz.bootup();
    while (millis() < 5000){
        alt.calibrate();
    }
    Serial.begin(9600);
    buzz.arming();
}
void loop(){ //Prints altitude to console, plays tone depending on altitude.
    note = alt.getAlt() * 100 + 2400;
    if(note > 2500){
        note = 2500;
    } else if(note < 2300){
        note = 2300;
    }
    Serial.println(alt.getAlt());
    buzz.playTone(note);
}
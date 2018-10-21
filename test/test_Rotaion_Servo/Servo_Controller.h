#include "mbed.h"

class ServoControl{
private:
    DigitalOut _pin;
    Ticker tic;
    int pos;
    float width;
public:
    ServoControl(PinName pin);
    ~ServoControl();
    int setPos(int);
    int setPulseWidth(int);
    void setPulse();
	int readPos();
	int setRS(float);
};

ServoControl::ServoControl(PinName pin) : _pin(pin) {
    pos = 1500;
    width = 0.02;
    tic.attach(this, &ServoControl::setPulse, width);
}

ServoControl::~ServoControl(){};

int ServoControl::setPos(int input){
    if (input<900 || 2100<input)    return 1;
    pos = input;
    return 0;
}

int ServoControl::setPulseWidth(int input){
    if (input<16 || 24<input)   return 1;
    width = (float)input/1000.0;
    return 0;
}

void ServoControl::setPulse(){
    _pin = 1;
    wait_us(pos);
    _pin = 0;
}

int ServoControl::readPos(){
	return pos;
}

int ServoControl::setRS(float rps){
	/* 
	   GWS S35 STD rotation servo
	   Max torque: 4*10^-3 [N*m]
	   Max rotation speed: 0.617 [(rotation)/s]
	   Pulse width: 900~2100
	                900~1500: Clockwise
					1500~2100: Counter Clockwise
	*/
	float signe = (rps >= 0) ? 1.0 : -1.0;
	int pw = 1500;
	const float MAX_RS = 0.617;
	if (rps > MAX_RS)		pw = 900;
	else if (rps < -MAX_RS)	pw = 2100;
	else					pw = 1500 + signe*600*(fabs(rps)/MAX_RS);

	setPos(pw);
	return 0;
}

#include "mbed.h"
#include "Servo_Control.h"

DigitalOut led1(dp26);
DigitalOut led2(dp24);
DigitalIn sw1(dp28);
AnalogIn psd1(dp9);
AnalogIn psd2(dp10);

ServoControl s1(dp11);

int main() {
    char flag = 0;
	float rang = .0f;
	float min_rang = 100.0f;
	int min_direction = 0;
    while(1) {
        led1 = 1;
        led2 = 1;
        wait(1);
        led1 = 0;
        led2 = 0;
		wait(1);
		//Switch input
		for(;;) {
			if (sw1)	led1 = 1, flag = 1;
			else		led1 = 0;
			wait(1);
			if(flag)	break;
		}
		led1 = 0;
		flag = 0;

		for(int i=0; i<120; i++) {
		//PSD input
			s1.setPos(900 + i*10);
			wait(0.05);
			rang = psd1;
			if(min_rang >= rang) {
				min_direction = s1.readPos();
				min_rang = rang; 
				led2 = 1;
				wait(1);
			}
		}
		s1.setPos(min_direction);
		led2 = 1;
		wait(1);
		led2 = 0;
		s1.setPos(1500);
		min_rang = 100.0f;
		min_direction = .0f;
		/*
		GWS S35 STD srvo
		  900~1500: Clockwise
		  1500~2100: Counter Clockwise
		*/
    }
	return 0;
}

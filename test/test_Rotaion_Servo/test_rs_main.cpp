#include "mbed.h"
#include "Servo_Control.h"

DigitalOut led1(dp26);
DigitalOut led2(dp24);

int main() {
    ServoControl s1(dp11);
    ServoControl s2(dp13);
    ServoControl s3(dp14);
    
    while(1) {
        led1 = 1;
        led2 = 1;
        s1.setPos(1500);
        s2.setPos(1500);
        s3.setPos(1500);
        wait(1);
        /*
        myled = 0;
        s15.setPos(1200);
        s16.setPos(1200);
        wait(1);
        
        myled = 1;
        s15.setPos(1500);
        s16.setPos(1500);
        wait(1);
        
        myled = 0;
        s15.setPos(1800);
        s16.setPos(1800);
        wait(1);

		for(int i=0; i<120; i++) {
			led1 = 0;
			led2 = 1;
			s1.setPos(900 + i*10);
			s2.setPos(900 + i*10);
			s3.setPos(2100 - i*10);
			wait(0.05);
			led1 = 1;
			led2 = 0;
			wait(0.05);
		}
		*/
		/*
		GWS S35 STD srvo
		  900~1500: Clockwise
		  1500~2100: Counter Clockwise
		*/
    }
}

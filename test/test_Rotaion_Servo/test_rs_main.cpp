#include "mbed.h"
#include "Servo_Control.h"

DigitalOut myled(dp14);

int main() {
    ServoControl s15(dp15);
    ServoControl s16(dp16);
    
    while(1) {
        myled = 1;
        s15.setPos(1500);
        s16.setPos(1500);
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
*/
		for(int i=0; i<100; i++) {
			s15.setPos(900 + i*5);
			s16.setPos(2100 - i*5);
			wait(0.1);
		}
		/*
		GWS S35 STD srvo
		  900~1500: Clockwise
		  1500~2100: Counter Clockwise
		*/
    }
}

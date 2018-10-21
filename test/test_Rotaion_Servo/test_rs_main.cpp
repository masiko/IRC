#include "Servo_Controller.h"
#include "MotionController.h"

DigitalOut led1(dp26);
DigitalOut led2(dp24);

int main() {
/*	float status[5] = {0.08,.0,.0,.0,.0};
	float tstatus[5] = {.0,.0,.0,.0,.0};
*/
	ServoControl s1(dp11);
    ServoControl s2(dp13);
    ServoControl s3(dp14);
	
	MotionController mc;
	
	led1 = 1;
	led2 = 1;
	wait(1);
	
	s1.setPos(1500);
	s2.setPos(1500);
	s3.setPos(1500);

	led1 = 0;
	led2 = 0;
	s2.setRS(-0.4);
	s3.setRS(0.4);
	wait(2);

	while(1) {
		mc.CulMotion(0.08, 0.0);
		s2.setRS(-1.0*mc.GetWL());
		s3.setRS(mc.GetWR());
		
		led2 = 1;
		wait(0.01);
		led2 = 0;
		wait(0.01);
	}

	return 0;
		
		/*
		GWS S35 STD srvo
		  900~1500: Clockwise
		  1500~2100: Counter Clockwise
		*/
}

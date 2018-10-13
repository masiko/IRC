#include "mbed.h"
#include "Servo_Controller.h"
#include "MotionController.h"

DigitalOut led1(dp26);
DigitalOut led2(dp24);

int main() {
	float status[5] = {.0,.0,.0,.0,.0};
	float tstatus[5] = {.0,.0,.0,.0,.0};
    ServoControl s1(dp11);
    ServoControl s2(dp13);
    ServoControl s3(dp14);
	
	MotionController MC;
	 
	led1 = 1;
	led2 = 1;
	s1.setPos(1500);
	s2.setPos(1500);
	s3.setPos(1500);
	wait(1);

	while(1) {
		MC.SetCv(status);
		MC.SetTv(tstatus);
		MC.CulTargetMotion();
	}

		
		/*
		GWS S35 STD srvo
		  900~1500: Clockwise
		  1500~2100: Counter Clockwise
		*/
}

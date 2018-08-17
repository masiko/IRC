#include "mbed.h"
#include "Servo_Control.h"

DigitalOut led1(dp26);
DigitalOut led2(dp24);
DigitalIn sw1(dp28);
AnalogIn psd1(dp9);
AnalogIn psd2(dp10);

ServoControl s1(dp11);

Serial pc(USBTX, USBRX);
// pc: screen

int main() {
    char flag = 0;
	float rang = .0f;
	float min_rang = 0.0f;
	int min_direction = -1;
	const float threshold = 0.12;
	pc.baud(115200);
	pc.format(8,Serial::None,1);
    
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
		pc.printf("START=%d ",2);
		 
		for(int i=0; i<120; i++) {
		//PSD input
			s1.setPos(900 + i*10);
			wait(0.05);
			rang = psd2;
			pc.printf(" %d ",(int)(100.0f*rang));

			if(min_rang <= rang && rang > threshold) {
				min_direction = s1.readPos();
				min_rang = rang; 
				led2 = 1;
				wait(0.1);
				led2 = 0;
			}
		}
		if(min_direction >= 0){
			s1.setPos(min_direction);
			led2 = 1;
			wait(0.5);
			led2 = 0;
	//		s1.setPos(900 + (int)(1200.0f*min_rang));
			pc.printf("MIN = %d ",(int)(100.0f*min_rang));
			wait(0.5);
		}else{
			led1 = 1;
			wait(0.5);
			led1 = 0;
			wait(0.5);
		}
		s1.setPos(1500);
		rang = .0f;
		min_rang = 0.0f;
		min_direction = -1;
		/*
		GWS S35 STD srvo
		  900~1500: Clockwise
		  1500~2100: Counter Clockwise
		*/
    }
	return 0;
}

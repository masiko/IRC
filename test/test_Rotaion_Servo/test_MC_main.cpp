#include<stdio.h>
#include"MotionController.h"

int main(){
	MotionController mc;

	for(int i=0; i<200; i++) {
		printf("%d: ",i);
		mc.CulMotion(0.08f, 0.0f);
		printf("%.5f, %.5f\n", mc.GetWL(), mc.GetWR());
	}

	return 0;
}

#ifdef TEST_MC
#include<stdio.h>
#endif
#include"cmath"
#include"MotionController.h"

MotionController::MotionController(float itv, float j, float t, float r) {
	CONTROL_INTERVAL = itv;
	MAX_JERK = j;
	MAX_DOMG = (MAX_JERK*pow((double)CONTROL_INTERVAL,3.0))/3.0 * 2.0/t;
	TRACK = t;
	RADIUS = r;
	v0 = .0;
	omg0 = .0;
	acc0 = .0;
	wl0 = .0;
	wl0 = .0;
	resetflag = false;
	v1 = .0;
	omg1 = .0;
	acc1 = .0;
	wr1 = .0;
	wl1 = .0; 
}

bool MotionController::CulMotion(float iv, float iomg) {
	v1 = iv;
	omg1 = iomg;
#ifdef TEST_MC
	printf("v1=%.2f, omg1=%.2f/", v1, omg1);
#endif
	CulTargetMotion();
	return false;
}

bool MotionController::CulTargetMotion() {
	float v, omg;
	float dacc, domg;
	acc1 = (v1 - v0) / CONTROL_INTERVAL;
	dacc = (acc1 - acc0) / CONTROL_INTERVAL;
	domg = omg1 - omg0;
#ifdef TEST_MC
	printf("acc1=%.2f, dacc=%.2f/", acc1, dacc);
#endif
	v = CulLinearTransientMotion(dacc);
	omg = CulAngularTransientMotion(domg);
#ifdef TEST_MC
	printf("v=%.5f, omg=%.5f/", v, omg);
#endif
	float deno = 4*M_PI*RADIUS;
	wr1 = ( TRACK*omg + 2*v) / deno;
	wl1 = (-TRACK*omg + 2*v) / deno;

	UpdateCv(v,omg);
	return false;
}

float MotionController::CulLinearTransientMotion(float dacc) {
	if( -MAX_JERK < dacc && dacc < MAX_JERK )	return v1;
	float signe = (dacc)>=0 ? 1.0 : -1.0;
	float tv1 = signe*MAX_JERK*pow((double)CONTROL_INTERVAL,2.0) + acc0*CONTROL_INTERVAL + v0;
	return tv1;
}

float MotionController::CulAngularTransientMotion(float domg) {
	if( -MAX_DOMG < domg && domg < MAX_DOMG )	return omg1;
	float signe = (domg)>=0 ? 1.0 : -1.0;
	float tomg1 = signe*MAX_DOMG;
	return tomg1;
}

bool MotionController::UpdateCv(float tv, float tomg) {
	if(resetflag)	return true;
	acc0 = tv - v0;
	v0 = tv;
	omg0 = tomg;
	wr0 = wr1;
	wl0 = wl1;
	return false;
}

void MotionController::SetCv(float vec[5]) {
	v0 = vec[0];
	omg0 = vec[1];
	acc0 = vec[2];
	wr0 = vec[3];
	wl0 = vec[4];
}
 
void MotionController::SetTv(float vec[5]) {
	v1 = vec[0];
	omg1 = vec[1];
	acc1 = vec[2];
	wr1 = vec[3];
	wl1 = vec[4];
}

void MotionController::GetCv(float vec[5]) {
	vec[0] = v0;
	vec[1] = omg0;
	vec[2] = acc0;
	vec[3] = wr0;
	vec[4] = wl0;
}

void MotionController::GetTv(float vec[5]) {
	vec[0] = v1;
	vec[1] = omg1;
	vec[2] = acc1;
	vec[3] = wr1;
	vec[4] = wl1;
}

float MotionController::GetWR() {
	return wr1;
}

float MotionController::GetWL() {
	return wl1;
}

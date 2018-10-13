#include"cmath"
#include"MotionController.h"

MotionController::MotionController(float itv, float j, float t, float r) {
	CONTROL_INTERVAL = itv;
	MAX_JERK = j;
	MAX_DOMG = (MAX_JERK*powf(CONTROL_INTERVAL,3))/3 * 2/t;
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
	CulTargetMotion();
	return false;
}

bool MotionController::CulTargetMotion() {
	float v, omg;
	float dacc, domg;
	acc1 = (v1 - v0) / CONTROL_INTERVAL;
	dacc = (acc1 - acc0) / CONTROL_INTERVAL;
	domg = omg1 - omg0;

	v = CulLinearTransientMotion(dacc);
	omg = CulAngularTransientMotion(domg);

	float deno = 4*M_PI*RADIUS;
	wr1 = ( TRACK*omg + 2*v) / deno;
	wl1 = (-TRACK*omg + 2*v) / deno;
	return false;
}

float MotionController::CulLinearTransientMotion(float dacc) {
	if( -MAX_JERK < dacc && dacc < MAX_JERK )	return v1;
	float signe = (dacc)>=0 ? 1.0 : -1.0;
	float tv1 = signe*MAX_JERK*powf(CONTROL_INTERVAL,2) + acc0*CONTROL_INTERVAL + v0;
	return tv1;
}

float MotionController::CulAngularTransientMotion(float domg) {
	if( -MAX_DOMG < domg && domg < MAX_DOMG )	return omg1;
	float signe = (domg)>=0 ? 1.0 : -1.0;
	float tomg1 = signe*MAX_DOMG;
	return tomg1;
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

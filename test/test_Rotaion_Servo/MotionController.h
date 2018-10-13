#include<iostream>

class MotionController{
private:
//Control Parameters
	float CONTROL_INTERVAL;	// [s]
	float MAX_JERK;			// [m/s^3]
	float MAX_DOMG;			// [(rad)/s]
//Parameters of controlled model
	float TRACK;	// [m]
	float RADIUS;	// [m]
//Current values
	float v0;		// [m/s]
	float omg0;		// [(rad)/s]
	float acc0;		// [m/s^2]
	float wr0;		// [rps]
	float wl0;		// [rps]
	bool resetflag;
//Target values
	float v1;
	float omg1;
	float acc1;
	float wr1;
	float wl1;
public:
	MotionController() {
		CONTROL_INTERVAL = 0.02;
		MAX_JERK = 1.6;
		MAX_DOMG = 0.179;
		TRACK = 0.12;
		RADIUS = 0.05;
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
	};
	MotionController(float itv, float j, float t, float r);
	~MotionController(){};

	bool CulMotion(float v, float omg);
	bool CulTargetMotion();
	float CulLinearTransientMotion(float dacc);
	float CulAngularTransientMotion(float domg);
	void SetCv(float vec[5]);
	void SetTv(float vec[5]);
	void SetCv(char No, float val);	//0: v0, 1: omg0, 2: acc0, 3: wr0, 4: wl0
	void SetTv(char No, float val);	//0: v1, 1: omg1, 2: acc1, 3: wr1, 4: wl1  

	void GetCv(float vec[5]);
	void GetTv(float vec[5]);
	float GetWR();
	float GetWL();
};


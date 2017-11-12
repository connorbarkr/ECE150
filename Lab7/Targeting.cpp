#include <stdlib.h>
#include <math.h>

//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//


#ifndef MARMOSET_TESTING
#include <iostream>
using namespace std;
#endif

#define NaN std::numeric_limits<float>::quiet_NaN()
#define isNaN(X) (X != X) // NaN is the only float that is not equal to itself

//////////////////////////////////////////////////////////////
//
// Function declarations; do not remove

float bisectionHelper(const float left, const float right,
                      const float precision, const float minIntervalSize
                      ... );
float bisection(const float left, const float right,
                const float precision, const float minIntervalSize);




bool hitTargetGivenVelocity (const float h, const float v, const float m,
                             const float d, const float t, const float b,
                             const float w, float& theta);

bool hitTargetGivenAngle (const float h, const float m, const float theta,
                          const float d, const float t, const float b,
                          const float w, float& v);

//////////////////////////////////////////////////////////////
//
// Your code here ...
//


bool hitTargetGivenVelocity (const float h, const float v, const float m,
                             const float d, const float t, const float b,
                             const float w, float& theta) {
	return false;
}



bool hitTargetGivenAngle (const float h, const float m, const float theta,
                          const float d, const float t, const float b,
                          const float w, float& v) {
	// Your code here...
	float rads = (3.14 * theta) / 180;
	float seconds = sqrt(2 * (h - t + (d * tan(rads))) / 9.8);
	float velocity = (d / cos(rads)) * (1 / seconds);
	v = velocity;
	return velocity;
}



#ifndef MARMOSET_TESTING
int main() {

	// Some test driver code here ....

	float h = 50;
	float d = 60;
	float b = 40;
	float t = 0;
	float w = 30;
	float m = 1;

	float theta = 68.81;                         // Angle in degrees;
	float v = 45.21;

	cout << "Given angle: " << theta << endl;
	cout << "Target at (" << d << "," << t << ")" << endl;
	if (hitTargetGivenAngle (h, m, theta, d, t, b, w, v)) {
		cout << "required initial velocity: " << v << endl << endl;
	}
	else {
		cout << "cannot calculate the velocity\n\n";
	}

	cout << "Given initial velocity: " << v << endl;
	cout << "Target at (" << d << "," << t << ")" << endl;
	if (hitTargetGivenVelocity (h, v, m, d, t, b, w, theta)) {
		cout << "required angle: " << theta << endl << endl;
	}
	else {
		cout << "cannot calculate the angle\n\n";
	}

	return 0;
}
#endif

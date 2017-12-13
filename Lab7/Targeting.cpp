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

//////////////////////////////////////////////////////////////
//
// Function declarations; do not remove

float bisectionHelper(const float left, const float right,
                      const float precision, const float minIntervalSize,
                      int maxIterations, int currentIterations,
                      const float v, const float t, const float d,
                      const float h);

float bisection(const float left, const float right,
                const float precision, const float minIntervalSize,
                const float v, const float t, const float d,
                const float h);

float absolute(float number);

float degToRad(float angle);

float bisectionFunction(const float v, const float t, const float d,
                        const float h, float angle);

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

float degToRad(float angle) {
	return (angle * 3.14159265) / 180;
}

float absolute(float number) {
	if (number < 0) {
		return number * -1;
	}
	else {
		return number;
	}
}

float bisectionHelper(const float left, const float right,
                      const float precision, const float minIntervalSize,
                      int maxIterations, int currentIterations,
                      const float v, const float t, const float d,
                      const float h) {
	const float a = left;
	const float b = right;
	const float c = (a + b) / 2;
	if ((a > b) || precision < 0 || minIntervalSize <= 0 || (bisectionFunction(v, t, d, h, c) == -1) ||
	    (bisectionFunction(v, t, d, h, a) > 0 && bisectionFunction(v, t, d, h, b) > 0) ||
	    (bisectionFunction(v, t, d, h, a) < 0 && bisectionFunction(v, t, d, h, b) < 0)) {
		return -1;
	}
	if (currentIterations < maxIterations) {
		if ((absolute(bisectionFunction(v, t, d, h, c)) <= precision) || (absolute(b - a) < minIntervalSize)) {
			return c;
		}
		if (bisectionFunction(v, t, d, h, a) < 0) {
			if (bisectionFunction(v, t, d, h, c) < 0) {
				return bisectionHelper(c, b, precision, minIntervalSize, maxIterations, currentIterations + 1, v, t, d, h);
			}
			else {
				return bisectionHelper(a, c, precision, minIntervalSize, maxIterations, currentIterations + 1, v, t, d, h);
			}
		} else {
			if (bisectionFunction(v, t, d, h, c) >= 0) {
				return bisectionHelper(c, b, precision, minIntervalSize, maxIterations, currentIterations + 1, v, t, d, h);
			}
			else {
				return bisectionHelper(a, c, precision, minIntervalSize, maxIterations, currentIterations + 1, v, t, d, h);
			}
		}
		currentIterations++;
	}
	return -1;
};

float bisection(const float left, const float right,
                const float precision, const float minIntervalSize,
                const float v, const float t, const float d,
                const float h) {
	return bisectionHelper(left, right, precision, minIntervalSize, 10000000, 0, v, t, d, h);
}

float bisectionFunction(const float v, const float t, const float d,
                        const float h, float angle) {
	float vx = cos(degToRad(angle)) * v;                                                                                                 //initial x velocity
	float vy = sin(degToRad(angle)) * v;                                                                                                 // initial y velocity
	float dx = vx * ((-(sqrt(pow(vy, 2) + (2 * -9.8 * -(h - t)))) - vy) / -9.8);
	return (dx - d);
}

bool hitTargetGivenVelocity (const float h, const float v, const float m,
                             const float d, const float t, const float b,
                             const float w, float& theta) {
	if (v < 0 || h < 0 || d < 0 || b < 0 || w < 0) {
		return false;
	}
	float angle = 45;
	float vx = cos(degToRad(angle)) * v; //initial x velocity
	float vy = sin(degToRad(angle)) * v; // initial y velocity
	float dx;
	float dy;
	float left;
	float right;

	if ((dx = vx * ((-(sqrt(pow(vy, 2) + (2 * -9.8 * -(h - t)))) - vy) / -9.8)) >= d) {
		right = 89;
		left = angle;
		angle = bisection(left, right, 0.001, 0.002, v, t, d, h);
		if (angle < 0) {
			return false;
		}
		theta = angle;
		return true;
	} else {
		return false;
	}
	return false;
}



bool hitTargetGivenAngle (const float h, const float m, const float theta,
                          const float d, const float t, const float b,
                          const float w, float& v) {
	if (absolute(theta) >= 90 || h < 0 || d < 0 || b < 0 || w <= 0) {
		return false;
	}
	float rads = degToRad(theta);
	float seconds = sqrt(2 * (h - t + (d * tan(rads))) / 9.8);
	float velocity = (d / cos(rads)) * (1 / seconds);
	v = velocity;
	return true;
}



#ifndef MARMOSET_TESTING
int main() {

	// Some test driver code here ....

	float h = 50;
	float d = 60;
	float b = 40;
	float t = 30;
	float w = 30;
	float m = 1;
	float theta = 45;                         // Angle in degrees;
	float v = 25;

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

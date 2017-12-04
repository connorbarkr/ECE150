//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <stdlib.h>
#include <limits>
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
float bisectionHelper(float left, float right,
                      float precision, float minIntervalSize,
                      int maxIterations, int currentIterations,
                      float step, float k, float d, float t,
                      float angle, float m, float h);

float bisection(float left, float right,
                float precision, float minIntervalSize,
                float step, float k, float d, float t,
                float angle, float m, float h);

float absolute(float number);

float degToRad(float angle);

float bisectionFunction(float v, float step, float k, float d,
                        float t, float angle, float m, float h);

bool hitTargetGivenAngle (const float h, const float m, const float theta,
                          const float d, const float step, const float k,
                          const float t, const float b, const float w, float& v);

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

float bisectionHelper(float left, float right,
                      float precision, float minIntervalSize,
                      int maxIterations, int currentIterations,
                      float step, float k, float d, float t,
                      float angle, float m, float h) {
	const float a = left;
	const float b = right;
	const float c = (a + b) / 2;
	if ((a > b) || precision < 0 || minIntervalSize <= 0 ||
	    (bisectionFunction(a, step, k, d, t, angle, m, h) > 0 && bisectionFunction(b, step, k, d, t, angle, m, h) > 0) ||
	    (bisectionFunction(a, step, k, d, t, angle, m, h) < 0 && bisectionFunction(b, step, k, d, t, angle, m, h) < 0)) {
		return -1;
	}
	if (currentIterations < maxIterations) {
		if ((absolute(bisectionFunction(c, step, k, d, t, angle, m, h)) <= precision) || (absolute(b - a) < minIntervalSize)) {
			return c;
		}
		if (bisectionFunction(a, step, k, d, t, angle, m, h) < 0) {
			if (bisectionFunction(c, step, k, d, t, angle, m, h) < 0) {
				return bisectionHelper(c, b, precision, minIntervalSize, maxIterations, currentIterations + 1, step, k, d, t, angle, m, h);
			}
			else {
				return bisectionHelper(a, c, precision, minIntervalSize, maxIterations, currentIterations + 1, step, k, d, t, angle, m, h);
			}
		} else {
			if (bisectionFunction(c, step, k, d, t, angle, m, h) >= 0) {
				return bisectionHelper(c, b, precision, minIntervalSize, maxIterations, currentIterations + 1, step, k, d, t, angle, m, h);
			}
			else {
				return bisectionHelper(a, c, precision, minIntervalSize, maxIterations, currentIterations + 1, step, k, d, t, angle, m, h);
			}
		}
		currentIterations++;
	}
	return -1;
};

float bisection(float left, float right,
                float precision, float minIntervalSize,
                float step, float k, float d, float t,
                float angle, float m, float h) {
	return bisectionHelper(left, right, precision, minIntervalSize, 10000000, 0,
	                       step, k, d, t, angle, m, h);
}

float bisectionFunction(float v, float step, float k, float d,
                        float t, float angle, float m, float h) {
	const float g = 9.81;
	float dx = 0;
	float dy = h;
	float velocity = v;
	float vx = v * cos(degToRad(angle));
	float vy = v * sin(degToRad(angle));
	float dfx = k * velocity * vx;
	float dfy = k * velocity * vy;
	float ax = -dfx / m;
	float ay = (-m * g - dfy) / m;
	while (dy >= t || vy > 0) {
		dx += vx * step;
		dy += vy * step;
		vx += ax * step;
		vy += ay * step;
		velocity = sqrt(pow(vx, 2) + pow(vy, 2));
		dfx = k * velocity * vx;
		dfy = k * velocity * vy;
		ax = -dfx / m;
		ay = (-m * g - dfy) / m;
	}
	return (dx - d);
}

bool bunkertest(float v, float step, float k, float b,
                float t, float angle, float m, float h) {
	const float g = 9.81;
	float dx = 0;
	float dy = h;
	float velocity = v;
	float vx = v * cos(degToRad(angle));
	float vy = v * sin(degToRad(angle));
	float dfx = k * velocity * vx;
	float dfy = k * velocity * vy;
	float ax = -dfx / m;
	float ay = (-m * g - dfy) / m;
	while (dy > 0) {
		dx += vx * step;
		dy += vy * step;
		vx += ax * step;
		vy += ay * step;
		velocity = sqrt(pow(vx, 2) + pow(vy, 2));
		dfx = k * velocity * vx;
		dfy = k * velocity * vy;
		ax = -dfx / m;
		ay = (-m * g - dfy) / m;
	}
	if (dx < b) {
		return true;
	}
	return false;
}

bool hitTargetGivenAngle (const float h, const float m, const float theta,
                          const float d, const float step, const float k,
                          const float t, const float b, const float w, float& v) {
	if (absolute(theta) >= 90 || h < 0 || d < 0 || b < 0 || w <= 0 ||
	    m <= 0 || step <= 0 || k < 0) {
		return false;
	}
	float rads = degToRad(theta);
	float seconds = sqrt(2 * (h - t + (d * tan(rads))) / 9.81);
	float vmin = ((d / cos(rads)) * (1 / seconds)) - 1;
	float vmax = 100;
	float velocity;
	float left;
	float right;
	left = vmin;
	right = vmax;
	velocity = bisection(left, right, 0.01, 0.002, step, k, d, t, theta, m, h);
	v = velocity;
	bool hitsGround;
	if (bunkertest(velocity, step, k, b, t, theta, m, h)) {
		return false;
	}
	if (velocity == -1) {
		return false;
	}
	return true;
}

#ifndef MARMOSET_TESTING
int main() {

	// Some test driver code here ....
	float h = 10;
	float d = 60;
	float b = 40;
	float t = 70;
	float w = 30;
	float m = 0.5;
	float step = 0.01;
	float k = 0;
	float theta = 76.8; // Angle in degrees;
	float v = 0;

	cout << endl << "Given angle: " << theta << endl;
	cout << "Target at (" << d << "," << t << ")" << endl;
	if (hitTargetGivenAngle(h, m, theta, d, step, k, t, b, w, v)) {
		cout << "required initial velocity: " << v << endl << endl;
	}
	else {
		cout << "cannot calculate the velocity" << endl << endl;
	}

	return 0;
}
#endif

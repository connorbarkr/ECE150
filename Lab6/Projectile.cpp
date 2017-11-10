//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

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
// Replace "..." in bisectionHelper() with any parameter(s)
// you need to ensure termination when precision and
// minIntervalSize are too tightly specified.
//

bool projectileDestination(const float h, const float v, const float m,
                           const float theta, const float d,
                           const float t, const float b, const float w,
                           float& destX, float& destY);

//////////////////////////////////////////////////////////////
//
// Your code here ...
//
// Return std::numeric_limits<float>::quiet_NaN() (comes from
// <limits>) if cannot compute the root for some reason
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

bool projectileDestination(const float h, const float v, const float m,
                           const float theta, const float d,
                           const float t, const float b, const float w,
                           float& destX, float& destY) {
	if (m <= 0 || v < 0 || theta < 0 || theta > 180) { // edge cases
		return false;
	}
	float angle = theta;
	float vx = cos(degToRad(angle)) * v; //initial x velocity
	float vy = sin(degToRad(angle)) * v; // initial y velocity
	float dx;
	if (t < 0) {
		//cout << "t < 0" << endl;
		dx = vx * ((-(sqrt(pow(vy, 2) + (2 * -9.8 * -(h + t)))) - vy) / -9.8);
	} else {
		//cout << "t >= 0" << endl;
		dx = vx * ((-(sqrt(pow(vy, 2) + (2 * -9.8 * -(h - t)))) - vy) / -9.8);
	}
	if (angle > 90) {
		angle = 180 - angle;
		vx = cos(degToRad(angle)) * v;
		vy = sin(degToRad(angle)) * v;
		dx = vx * ((-(sqrt(pow(vy, 2) + (2 * -9.8 * -h))) - vy) / -9.8);
		destX = -dx;
		destY = 0;
		return true;
	}
	if (theta == 90 || vx == 0) { // case: {straight up or straight down}
		//cout << "case: {straight up or straight down}" << endl;
		destX = 0;
		destY = h;
		return true;
	} else if ((dx >= b && dx <= b + w) && t >= 0) { // case: {lands on top}
		//cout << "case: {lands on top}" << endl;
		destX = dx;
		destY = t;
		return true;
	} else if (dx < b) { // case: {x < building distance when y = building height}
		//cout << "case: {x < building distance when y = building height}" << endl;
		dx = vx * ((-(sqrt(pow(vy, 2) + (2 * -9.8 * -h))) - vy) / -9.8); // x pos when y == 0
		if (dx <= b) { // case: {x final is before the building}
			//cout << "case: {x final is before the building}" << endl;
			destX = dx;
			destY = 0;
			return true;
		}
	} else if (dx > b && dx < (b + w)) { //case: {hits wall}
		if (t < 0) {
			//cout << "case: {hits opposite wall}" << endl;
			float dy = h + (vy * ((b + w) / vx)) + (0.5 * -9.8 * pow(((b + w) / vx), 2));
			if (dy < t) {
				dy = t;
			} else if (dy > 0) {
				dx = vx * ((-(sqrt(pow(vy, 2) + (2 * -9.8 * -h))) - vy) / -9.8);
				destX = dx;
				destY = 0;
				return true;
			}
			destX = b + w;
			destY = dy;
			return true;
		}
		//cout << "case: {hits wall}" << endl;
		float dy = h + (vy * (b / vx)) + (0.5 * -9.8 * pow((b / vx), 2));         // height when ball hits wall
		//cout << "("<< b << ", " << dy << ")" << endl;
		destX = b;
		destY = dy;
		return true;
	} else if (dx > (b + w)) { //case: {overshoots}
		//cout << "case: {overshoots}" << endl;
		dx = vx * ((-(sqrt(pow(vy, 2) + (2 * -9.8 * -h))) - vy) / -9.8);
		destX = dx;
		destY = 0;
		return true;
	}
	return false;
}

//////////////////////////////////////////////////////////////
//
// Test Driver
//
// Do not remove the #ifndef and its associated #endif
// This is required so that when you submit your code,
// this test driver will be ignored by Marmoset
//

#ifndef MARMOSET_TESTING

#define isNaN(X) (X != X)  // NaN is the only float that is not equal to itself

int main(const int argc, const char* const argv[]) {

	// Some test driver code here ....

	float h = 50;
	float v = 18.4;
	float m = 1;
	float theta = 127;  // Angle in degrees; will need to be converted by function
	float d = 100;
	float t = 50;
	float b = 30;
	float w = 1;

	float hitsAtX;
	float hitsAtY;

	if (projectileDestination(h,v,m,theta,d,t,b,w,hitsAtX,hitsAtY))
		cout << "Projectile hit at (" << hitsAtX << ", " << hitsAtY << ")" <<endl;
	else
		cout << "Unable to calculate where projectile hits." << endl;
	return 0;
}

#endif

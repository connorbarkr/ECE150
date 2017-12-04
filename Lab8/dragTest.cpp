#include <iostream>
#include <math.h>

using namespace std;

float degToRad(float angle) {
	return (angle * 3.14159265) / 180;
}

float bisectionFunction(float v, float step, float k, float d,
                        float t, float angle, float m, float h) {
	// float velocity = v;
	// float theta = degToRad(angle);
	// float dx = 0;
	// float dy = h;
	// float vx;
	// float vy;
	// float ax;
	// float ay;
	// bool done = false;
	// while (!done) {
	//      vx = velocity * cos(theta);
	//      vy = velocity * sin(theta);
	//      ax = -((k * velocity * vx)/m);
	//      ay = (-((k * velocity * vy)/m)) - 9.81;
	//      dx = dx + (vx * step);
	//      dy = dy + (vy * step);
	//      vx = vx + (ax * step);
	//      vy = vy + (ay * step);
	//      theta = atan(vy / vx);
	//      velocity = sqrt(pow(vx, 2) + pow(vy, 2));
	//      if (dy >= t && vy < 0) {
	//              done = true;
	//      }
	// }
	// return dx;
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
	cout << dx << endl;
	return dx;
}

int main() {
	float h = 50;
	float d = 60;
	float b = 40;
	float t = 30;
	float w = 30;
	float m = 1;
	float step = 0.01;
	float k = 0.00;
	float theta = 45; // Angle in degrees;
	float v = 25;
	cout << bisectionFunction(v, step, k, d, t, theta, m, h) << endl;
	d = bisectionFunction(v, step, k, d, t, theta, m, h);
	float rads = degToRad(theta);
	float seconds = sqrt(2 * (h - t + (d * tan(rads))) / 9.8);
	float velocity = (d / cos(rads)) * (1 / seconds);
	cout << "Velocity: " << velocity << endl;
	return 0;
}

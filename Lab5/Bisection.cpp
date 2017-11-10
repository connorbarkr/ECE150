//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <stdlib.h>
#include <limits>

//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING
#include <iostream>
using namespace std;


// Sample function for which you need to find the root

float f(const float x) {
	return 3.2*x*x*x - 2.1*x - 23.0;
}

#endif

//////////////////////////////////////////////////////////////
//
// Function declarations; do not remove
// Replace "..." in bisectionHelper() with any parameter(s)
// you need to ensure termination when precision and
// minIntervalSize are too tightly specified.
//

float bisectionHelper(const float left, const float right,
                      const float precision, const float minIntervalSize,
                      int maxIterations, int currentIterations);
float bisection(const float left, const float right,
                const float precision, const float minIntervalSize);

//////////////////////////////////////////////////////////////
//
// Your code here ...
//
// Return std::numeric_limits<float>::quiet_NaN() (comes from
// <limits>) if cannot compute the root for some reason
//

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
                      int maxIterations, int currentIterations) {
	const float a = left;
	const float b = right;
	const float c = (a + b) / 2;
	if (a > b || precision < 0 || minIntervalSize <= 0 || f(c) != f(c) || (f(a) > 0 && f(b) > 0) || (f(a) < 0 && f(b) < 0))
		return std::numeric_limits<float>::quiet_NaN();
	if (currentIterations < maxIterations) {
		if ((absolute(f(c)) <= precision) || (absolute(b - a) < minIntervalSize)) {
			return c;
		}
		if (f(a) < 0) {
			if (f(c) < 0) {
				return bisectionHelper(c, b, precision, minIntervalSize, maxIterations, currentIterations + 1);
			}
			else {
				return bisectionHelper(a, c, precision, minIntervalSize, maxIterations, currentIterations + 1);
			}
		} else {
			if (f(c) >= 0) {
				return bisectionHelper(c, b, precision, minIntervalSize, maxIterations, currentIterations + 1);
			}
			else {
				return bisectionHelper(a, c, precision, minIntervalSize, maxIterations, currentIterations + 1);
			}
		}
		currentIterations++;
	}
	return std::numeric_limits<float>::quiet_NaN();
};

float bisection(const float left, const float right,
                const float precision, const float minIntervalSize) {
	return bisectionHelper(left, right, precision, minIntervalSize, 10000000, 0);
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
	float a = -100;
	float b = 80000;
	float x = bisection(a, b, 0.01, 0.0000002);
	cout << x << endl;
	return 0;
}

#endif

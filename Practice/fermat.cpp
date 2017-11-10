//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <limits>
//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING

#include <iostream>

using namespace std;

bool statistics(const float dataset[], const int size,
                float& min, float& avg, float& max,
                float& popSD, float& smplSD, float& mdn);

float minimum(const float dataset[], const int size);
float average(const float dataset[], const int size);
float maximum(const float dataset[], const int size);
float popStdDev(const float dataset[], const int size);
float smplStdDev(const float dataset[], const int size);
float median(const float dataset[], const int size);
#endif

//////////////////////////////////////////////////////////////
//
// Your code here ...
//

bool statistics(const float dataset[], const int size,
                float& min, float& avg, float& max,
                float& popSD, float& smplSD, float& mdn) {
	min = minimum(dataset, size);
	avg = average(dataset, size);
	max = maximum(dataset, size);
	popSD = popStdDev(dataset, size);
	smplSD = smplStdDev(dataset, size);
	mdn = median(dataset, size);
	if (size < 1) {
		return false;
	}
	return true;
}

float minimum(const float dataset[], const int size) {
	if (size < 1) {
		return std::numeric_limits<float>::quiet_NaN();
	}
	int i = 0;
	float min = dataset[0];
	while (i < size) {
		if (dataset[i] < min) {
			min = dataset[i];
		}
		i++;
	}
	return min;
}

float average(const float dataset[], const int size) {
	if (size < 1) {
		return std::numeric_limits<float>::quiet_NaN();
	}
	float sum = 0;
	for (int i = 0; i < size; i++) {
		sum+= dataset[i];
	}
	float avg = sum/size;
	return avg;
}

float maximum(const float dataset[], const int size) {
	if (size < 1) {
		return std::numeric_limits<float>::quiet_NaN();
	}
	int i = 0;
	float max = dataset[0];
	while (i < size) {
		if (dataset[i] > max) {
			max = dataset[i];
		}
		i++;
	}
	return max;
}

float stdavg(const float dataset[], const int size) {
	if (size < 1) {
		return std::numeric_limits<float>::quiet_NaN();
	}
	float stdavg = 0;
	for (int i = 0; i < size; i++) {
		float value = dataset[i];
		stdavg+= pow((value-(average(dataset, size))),2.0);
	}
	return stdavg;
}

float popStdDev(const float dataset[], const int size) {
	if (size < 1) {
		return std::numeric_limits<float>::quiet_NaN();
	}
	float popSD = sqrt((1.0/size)*(stdavg(dataset, size)));
	return popSD;
}

float smplStdDev(const float dataset[], const int size) {
	if (size < 1) {
		return std::numeric_limits<float>::quiet_NaN();
	}
	if (size == 1) {
		return std::numeric_limits<float>::infinity();
	}
	float smplSD = sqrt((1.0/(size-1)*(stdavg(dataset, size))));
	return smplSD;
}

float median(const float dataset[], const int size) {
	if (size < 1) {
		return std::numeric_limits<float>::quiet_NaN();
	}
	float arr[size];
	for (int i = 0; i < size; i++) {
		arr[i] = dataset[i];
	}
	for (int i = 0; i < size-1; i++) {
		for (int k = 0; k < size-1-i; k++) {
			if (arr[k] > arr[k+1]) {
				int temp = arr[k+1];
				arr[k+1] = arr[k];
				arr[k] = temp;
			}
		}
	}
	if (size % 2 == 0) {
		float median = (arr[(size/2)-1]+arr[size/2])/2.0;
		return median;
	}
	else {
		float median = arr[size/2];
		return median;
	}
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

int main(const int argc, const char* const argv[]) {
	int size = 7;
	float dataset[] = {1, 2, 4, 3, 5, 7, 6};
	float min = minimum(dataset, size);
	float avg = average(dataset, size);
	float max = maximum(dataset, size);
	float popStDev = popStdDev(dataset, size);
	float smplStDev = smplStdDev(dataset, size);
	float mdn = median(dataset, size);

	if (statistics(dataset, size, min, avg, max, popStDev, smplStDev, mdn)) {
		cout << "Minimum: " << min << endl
		     << "Average: " << avg << endl
		     << "Median:  " << mdn << endl
		     << "Maximum: " << max << endl
		     << "Population Standard Deviation: " << popStDev << endl
		     << "Sample Standard Deviation:     " << smplStDev << endl;
	}
	else
		cout << "Error: unable to compute statistics" << endl;

	return 0;
}

#endif

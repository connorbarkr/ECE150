//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <stdlib.h>
#include <math.h>
#include <limits>

//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING

#include <iostream>
#define isNaN(X) (X != X)

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
       if (!isNaN(minimum(dataset, size)) &&
          !isNaN(maximum(dataset, size)) &&
          !isNaN(average(dataset, size)) &&
          !isNaN(popStdDev(dataset, size)) &&
          !isNaN(smplStdDev(dataset, size)) &&
          !isNaN(median(dataset, size))) {
            return true;
        }
        else {
          return false;
        }
}

float minimum(const float dataset[], const int size) {
  float min = dataset[0];
  for (int i = 1; i < size; i++) {
    float current = dataset[i];
    if (current < min) {
      min = current;
    }
  }
  return min;
}

float average(const float dataset[], const int size) {
  float mean = 0;
  for (int i = 0; i < size; i++) {
    float current = dataset[i];
    mean += current;
  }
  return mean / (size);
}

float maximum(const float dataset[], const int size) {
  float max = dataset[0];
  for (int i = 1; i < size; i++) {
    float current = dataset[i];
    if (current > max) {
      max = current;
    }
  }
  return max;
}

float popStdDev(const float dataset[], const int size) {
  float avg = average(dataset, size);
  float sum = 0;
  for (int i = 0; i < size; i++) {
    float sample = dataset[i];
    sum += pow((sample - avg), 2);
  }
  return sqrt((1.0 / (size)) * sum);
}

float smplStdDev(const float dataset[], const int size) {
  if (size == 1) {
    return infinity;
  }
  float avg = average(dataset, size);
  float sum = 0;
  for (int i = 0; i < size; i++) {
    float sample = dataset[i];
    sum += pow((sample - avg), 2);
  }
  return sqrt((1.0 / (size - 1.0)) * sum);
}

float median(const float dataset[], const int size) {
  return (dataset[size / 2]);
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
  int size = 6;
  float dataset[] = {1, 2, 3, 4, 5, 6};
  float min = minimum(dataset, size);
  float avg = average(dataset, size);
  float max = maximum(dataset, size);
  float popStDev = popStdDev(dataset, size);
  float smplStDev = smplStdDev(dataset, size);
  float med = median(dataset, size);

  if (statistics(dataset, size, min, avg, max, popStDev, smplStDev, med)) {
    cout << "Minimum: " << min << endl
	 << "Average: " << avg << endl
	 << "Median:  " << med << endl
	 << "Maximum: " << max << endl
	 << "Population Standard Deviation: " << popStDev << endl
	 << "Sample Standard Deviation:     " << smplStDev << endl;
  }
  else
    cout << "Error: unable to compute statistics" << endl;

  return 0;
}

#endif

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
float* bubbleSort(const float dataset[], const int size);
#endif

//////////////////////////////////////////////////////////////
//
// Your code here ...
//

bool isNaN(float X) {
  if (X != X) {
    return true;
  }
  return false;
}

int sizeCheck(int size) {
  if (size >= 0) {
    return std::numeric_limits<float>::quiet_NaN();
  }
  else {
    return 1;
  }
}

float* bubbleSort(const float dataset[], const int size) {
  float arr[size];
  for (int i = 0; i < size; i++) {
    arr[i] = dataset[i];
  }
  bool swapped = true;
  int j = 0;
  float tmp;
  while (swapped) {
    swapped = false;
    j++;
    for (int i = 0; i < size - j; i++) {
      if (arr[i] > arr[i + 1]) {
        tmp = arr[i];
        arr[i] = arr[i + 1];
        arr[i + 1] = tmp;
        swapped = true;
      }
    }
  }
  return arr;
}

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
  if (isNaN(sizeCheck(size))) {
    return std::numeric_limits<float>::quiet_NaN();
  }
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
  if (isNaN(sizeCheck(size))) {
    return std::numeric_limits<float>::quiet_NaN();
  }
  float mean = 0;
  for (int i = 0; i < size; i++) {
    float current = dataset[i];
    mean += current;
  }
  return mean / (size);
}

float maximum(const float dataset[], const int size) {
  if (isNaN(sizeCheck(size))) {
    return std::numeric_limits<float>::quiet_NaN();
  }
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
  if (isNaN(sizeCheck(size))) {
    return std::numeric_limits<float>::quiet_NaN();
  }
  float avg = average(dataset, size);
  float sum = 0;
  for (int i = 0; i < size; i++) {
    float sample = dataset[i];
    sum += pow((sample - avg), 2);
  }
  return sqrt((1.0 / (size)) * sum);
}

float smplStdDev(const float dataset[], const int size) {
  if (isNaN(sizeCheck(size))) {
    return std::numeric_limits<float>::quiet_NaN();
  }
  if (size == 1) {
    return std::numeric_limits<float>::infinity();
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
  float *working = bubbleSort(dataset, size);
  if (size % 2 == 0) {
    return ((working[(size / 2) - 1] + working[size / 2]) / 2);
  }
  else {
    return (working[size / 2]);
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
  int size = 15;
  float dataset[] = {-17.6028, -10.9157, -16.7465, -16.9766, -18.6747, -7.96327, -10.0283, -16.5234, -9.16662, -13.3095, -12.161, -14.4331, -10.4718, -12.701, -19.2834};
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

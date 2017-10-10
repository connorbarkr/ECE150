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

int SWStats(const float dataset[], const int size,
	    const int currentSample, const int windowSize,
	    float& min, float& avg, float& max,
	    float& smplSD, float& mdn);

int SWMinimum(const float dataset[], const int size,
	      const int currentSample, const int windowSize,
	      float& minimum);
int SWAverage(const float dataset[], const int size,
	      const int currentSample, const int windowSize,
	      float& average);
int SWMaximum(const float dataset[], const int size,
	      const int currentSample, const int windowSize,
	      float& maximum);
int SWSmplStdDev(const float dataset[], const int size,
		 const int currentSample, const int windowSize,
		 float& smplStdDev);
int SWMedian(const float dataset[], const int size,
	     const int currentSample, const int windowSize,
	     float& median);
#endif

//////////////////////////////////////////////////////////////
//
// Your code here ...
//

float average(const float dataset[], const int size) {
  float mean = 0;
  for (int i = 0; i < size; i++) {
    float current = dataset[i];
    mean += current;
  }
	float d = size;
  return (mean / d);
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

int SWStats(const float dataset[], const int size,
	    const int currentSample, const int windowSize,
	    float& min, float& avg, float& max,
	    float& smplSD, float& mdn) {
				SWMinimum(dataset, size, currentSample, windowSize, min);
				SWMaximum(dataset, size, currentSample, windowSize, max);
				SWAverage(dataset, size, currentSample, windowSize, avg);
				SWMedian(dataset, size, currentSample, windowSize, mdn);
				SWSmplStdDev(dataset, size, currentSample, windowSize, smplSD);
				if (SWMinimum(dataset, size, currentSample, windowSize, min) >= 0 &&
				 		SWMaximum(dataset, size, currentSample, windowSize, max) >= 0 &&
						SWSmplStdDev(dataset, size, currentSample, windowSize, smplSD) >= 0 &&
						SWAverage(dataset, size, currentSample, windowSize, avg) >= 0 &&
						SWMedian(dataset, size, currentSample, windowSize, mdn) >= 0) {
							if (SWMinimum(dataset, size, currentSample, windowSize, min) > 0 &&
							 		SWMaximum(dataset, size, currentSample, windowSize, max) > 0 &&
									SWSmplStdDev(dataset, size, currentSample, windowSize, smplSD) > 0 &&
									SWAverage(dataset, size, currentSample, windowSize, avg) > 0 &&
									SWMedian(dataset, size, currentSample, windowSize, mdn) > 0) {
										return 1;
									}
					return 0;
				}
				return -1;
}

int SWMinimum(const float dataset[], const int size,
	      const int currentSample, const int windowSize,
	      float& minimum) {
					if (size < 1 || windowSize <= 0) {
 					 return -1;
 				  }
					minimum = dataset[currentSample];
		      if (currentSample < windowSize) {
						for (int i = 0; i < currentSample; i++) {
			        float current = dataset[i];
			        if (current < minimum) {
			          minimum = current;
			        }
						}
						if (windowSize > size || windowSize == 1) {
							return 1;
						}
						return 0;
					}
					for (int j = currentSample; j > currentSample - windowSize; j--) {
	          float current = dataset[j];
	          if (current < minimum) {
	            minimum = current;
	          }
					}
					if (windowSize > size || windowSize == 1) {
						return 1;
					}
					return 0;
}

int SWAverage(const float dataset[], const int size,
	      const int currentSample, const int windowSize,
	      float& average) {
					if (size < 1 || windowSize <= 0) {
 					 return -1;
 				  }
					average = 0;
					if (currentSample < windowSize) {
		        for (int i = 0; i < windowSize; i++) {
							if (i > currentSample) {
								average += dataset[0];
							}
							else {
								average += dataset[i];
							}
						}
						average = (average / windowSize);
						if (windowSize > size || windowSize == 1) {
							return 1;
						}
						return 0;
					}
					for (int i = currentSample; i > currentSample - windowSize; i--) {
	          float current = dataset[i];
	          average += current;
					}
					average = (average / windowSize);
					if (windowSize > size || windowSize == 1) {
						return 1;
					}
					return 0;
}

int SWMaximum(const float dataset[], const int size,
	      const int currentSample, const int windowSize,
	      float& maximum) {
					if (size < 1 || windowSize <= 0) {
 					 return -1;
 				  }
					maximum = dataset[currentSample];
					if (currentSample < windowSize) {
						for (int i = 0; i < currentSample; i++) {
			        float current = dataset[i];
			        if (current > maximum) {
			          maximum = current;
			        }
						}
						if (windowSize > size || windowSize == 1) {
							return 1;
						}
						return 0;
					}
					for (int j = currentSample; j > currentSample - windowSize; j--) {
	          float current = dataset[j];
	          if (current > maximum) {
	            maximum = current;
	          }
					}
					if (windowSize > size || windowSize == 1) {
						return 1;
					}
					return 0;
}

int SWSmplStdDev(const float dataset[], const int size,
		 const int currentSample, const int windowSize,
		 float& smplStdDev) {
			 if (size < 2 || windowSize <= 0) {
				 return -1;
			 }
			 float arr[windowSize];
			 if (currentSample - windowSize < 0) {
				 for (int i = 0; i < windowSize; i++) {
					 if (i <= currentSample) {
						 arr[i] = dataset[i];
					 }
					 else {
						 arr[i] = dataset[0];
					 }
				 }
			 }
			 else {
				 int k = 0;
				 for (int i = currentSample; i > currentSample - windowSize; i--) {
					 arr[k] = dataset[i];
					 k++;
				 }
			 }
			 float avg = average(arr, windowSize);
		   float variance = 0;
		   for (int i = 0; i < windowSize; i++) {
		     float sample = arr[i];
		     variance += (pow((sample - avg), 2));
		   }
			 variance = variance / (windowSize - 1);
			 if (currentSample == 0) {
				 smplStdDev = 0;
			 }
			 else {
				 smplStdDev = sqrt(variance);
			 }
			 if (windowSize > size || windowSize == 1) {
				 return 1;
			 }
		   return 0;
}

int SWMedian(const float dataset[], const int size,
	     const int currentSample, const int windowSize,
	     float& median) {
				 if (size < 1 || windowSize <= 0) {
					return -1;
				 }
				 float arr[windowSize];
				 if (currentSample - windowSize < 0) {
					 for (int i = 0; i < windowSize; i++) {
						 if (i <= currentSample) {
							 arr[i] = dataset[i];
						 }
						 else {
							 arr[i] = dataset[0];
						 }
					 }
				 }
				 else {
					 int k = 0;
					 for (int i = currentSample; i > currentSample - windowSize; i--) {
						 arr[k] = dataset[i];
						 k++;
					 }
				 }
				 float *working = bubbleSort(arr, windowSize);
				 if (windowSize % 2 == 0) {
					 median = ((working[(windowSize / 2) - 1] + working[windowSize / 2]) / 2);
					 if (windowSize > size || windowSize == 1) {
						 return 1;
					 }
			     return 0;
			   }
			   else {
					 median = (working[windowSize / 2]);
					 if (windowSize > size || windowSize == 1) {
						 return 1;
					 }
			     return 0;
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
  int size = 2;
  float dataset[] = {17.6028, 10.9157};
  int windowSize = 4;
  int currentSample = 0;
	float min;
	float max;
	float avg;
	float mdn;
	float smplSD;

	SWMinimum(dataset, size, currentSample, windowSize, min);
	SWMaximum(dataset, size, currentSample, windowSize, max);
	SWAverage(dataset, size, currentSample, windowSize, avg);
	SWMedian(dataset, size, currentSample, windowSize, mdn);
	SWSmplStdDev(dataset, size, currentSample, windowSize, smplSD);

  cout << "Sample \t Minimum \t Average \t Median \t Maximum \t Sample Standard Deviation" << endl;

  while (currentSample < size) {
    int retCode = SWStats(dataset, size, currentSample, windowSize, min, avg, max, smplSD, mdn);
    if (retCode >= 0) {
      cout << currentSample << "\t " << min << "\t " << avg << "\t " << mdn << "\t " << max << "\t " << smplSD << endl;
      if (retCode > 0)
	cerr << "Warning: something weird happened, but we computed stats anyway ... YMMV" << endl;
    }
    else {
      cerr << "Error: unable to compute sliding-window statistics; exiting" << endl;
      return(-1);
    }
    ++currentSample;
  }
  return 0;
}

#endif

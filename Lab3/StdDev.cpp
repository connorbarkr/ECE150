#include <stdlib.h>
#include <iostream>
#include <math.h>

using namespace std;

float mean(int argc, const char * argv[]) {
  float mean = 0;
  for (int i = 1; i < argc; i++) {
    float current = atof(argv[i]);
    mean += current;
  }
  return mean / (argc - 1);
}

float minimum(int argc, const char * argv[]) {
  float min = atof(argv[1]);
  for (int i = 2; i < argc; i++) {
    float current = atof(argv[i]);
    if (current < min) {
      min = current;
    }
  }
  return min;
}

float maximum(int argc, const char * argv[]) {
  float max = atof(argv[1]);
  for (int i = 2; i < argc; i++) {
    float current = atof(argv[i]);
    if (current > max) {
      max = current;
    }
  }
  return max;
}

float sampleStandard(int argc, const char * argv[]) {
  float avg = mean(argc, argv);
  float sum = 0;
  for (int i = 1; i < argc; i++) {
    float sample = atof(argv[i]);
    sum += pow((sample - avg), 2);
  }
  return sqrt((1.0 / (argc - 2.0)) * sum);
}

float popStandard(int argc, const char * argv[]) {
  float avg = mean(argc, argv);
  float sum = 0;
  for (int i = 1; i < argc; i++) {
    float sample = atof(argv[i]);
    sum += pow((sample - avg), 2);
  }
  return sqrt((1.0 / (argc - 1.0)) * sum);
}

int main(int argc, const char * argv[]) {
  if ((argc - 1) > 0) {
    int a = argc - 1;
    float b = minimum(argc, argv);
    float c = mean(argc, argv);
    float d = maximum(argc, argv);
    float e = popStandard(argc, argv);
    float f = sampleStandard(argc, argv);
    cout << "Number of floating-point numbers: " << a << endl;
    cout << "Minimum floating-point number: " << b << endl;
    cout << "Average floating-point number: " << c << endl;
    cout << "Maximum floating-point number: " << d << endl;
    cout << "Population standard deviation: " << e << endl;
    if (argc - 1 > 1) {
      cout << "Sample standard deviation: " << f << endl;
    }
    else {
      cout << "Sample standard deviation: infinity" << endl;
    }
    return 0;
  }
  else {
    cerr << "Error: Unable to compute statistics over data set because there is insufficient data." << endl;
    return -1;
  }
}

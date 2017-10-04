// Created by Connor Barker

#include <stdlib.h>
#include <iostream>

using namespace std;

float pow(float number, int power) {
  float result = number;
  for (int i = 1; i < power; i++) {
    result *= number;
  }
  return result;
}

float abs(float number) {
  if (number < 0) {
    return number * -1;
  }
  else {
    return number;
  }
}

int main(int argc, const char * argv[]) {
  if (argc >= 4) {
    float number = atof(argv[1]);
    int root = atoi(argv[2]);
    float precision = atof(argv[3]);
    float result = number / root;
    float previous;

    if (argc > 4) {
      cerr << "Warning: Expected 3 arguments, recieved " << argc - 4 << ". Discarding extra args." << endl;
    }
    if (root < 2) {
      cerr << "Error: Unable to compute Nth root because the root is out of range." << endl;
      return -1;
    }
    if (((abs(root) % 2) == 0) && number < 0) {
      cerr << "Error: Unable to compute Nth root because the even root of a negative number cannot be found." << endl;
      return -1;
    }
    if (precision <= 0 || precision >= 1) {
      cerr << "Error: Unable to compute Nth root because the precision is out of bounds (0 < precision < 1)" << endl;
      return -1;
    }

    do {
      previous = result;
      result = (((root - 1.0 ) / root) * previous) + (number / (root * pow(previous, root - 1)));
    } while (abs(result - previous) >= precision);

    cout << "Root(" << number << "," << root << ") = " << result << endl;
    cout << "(with precision " << abs(result - previous) << ")" << endl;

    return 0;
  } else {
    cerr << "Error: Unable to compute Nth root because not enough arguments were passed." << endl;
    return -1;
  }
}

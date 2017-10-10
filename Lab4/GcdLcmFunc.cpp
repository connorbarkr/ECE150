//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <stdlib.h>

//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING

#include <iostream>

using namespace std;

int greatestCommonDenominator(const int, const int);
int leastCommonMultiple(const int, const int);
#endif

//////////////////////////////////////////////////////////////
//
// Your code here ...
//

int greatest(int a, int b) {
  if (a > b) {
    return a;
  } else {
    return b;
  }
}

int least(int a, int b) {
  if (a < b) {
    return a;
  } else {
    return b;
  }
}

int greatestCommonDenominator(const int a, const int b) {
  if (a < 1 || b < 1) {
    return -1;
  }
  int result = 0;
  int i = 1;
  int r;
  int c = greatest(a, b);
  int d = least(a, b);
  if (c == 0) {
    return d;
  } else if (d == 0) {
    return c;
  }
  while (i > 0) {
    i++;
    int r = c % d;
    int x = (c - r) / d;
    c = d;
    d = r;
    if (d == 0) {
      result += c;
      i = 0;
    }
  }
  return result;
}

int leastCommonMultiple(const int a, const int b) {
  if (a < 1 || b < 1) {
    return -1;
  }
  int c = greatest(a, b);
  int d = least(a, b);
  int result = (c / greatestCommonDenominator(c, d)) * d;
  return result;
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

  if (argc < 3) {
    cerr << "Error: Usage: " << argv[0] << "<num1> <num2>; exiting" << endl;
    return -1;
  }

  int gcd = greatestCommonDenominator(atoi(argv[1]),atoi(argv[2]));
  if (gcd < 0) {
    cerr << "Error: unable to compute GCD(" << argv[1] << "," << argv[2] << ")" << endl;
  }
  else {
    cout << "GCD(" << argv[1] << "," << argv[2] << ") = " << gcd << endl;
  }

  int lcm = leastCommonMultiple(atoi(argv[1]),atoi(argv[2]));
  if (lcm < 0) {
    cerr << "Error: unable to compute LCM(" << argv[1] << "," << argv[2] << ")" << endl;
  }
  else {
    cout << "LCM(" << argv[1] << "," << argv[2] << ") = " << lcm << endl;
  }

  return 0;
}

#endif

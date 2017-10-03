#include <stdlib.h>
#include <iostream>

using namespace std;

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

int gcd(int greatest, int least) {
  int result = 0;
  int i = 1;
  int r;
  int a = greatest;
  int b = least;
  if (a == 0) {
    return b;
  } else if (b == 0) {
    return a;
  }
  while (i > 0) {
    i++;
    int r = a % b;
    int x = (a - r) / b;
    a = b;
    b = r;
    if (b == 0) {
      result += a;
      i = 0;
    }
  }
  return result;
}

int lcm(int a, int b) {
  int result = (a / gcd(a, b)) * b;
  cout << "LCM(" << a << ", " << b << ") = " << result << endl;
  return 0;
}

int main(int argc, const char * argv[]) {
  if (argc >= 3) {
    int a = greatest(atoi(argv[1]), atoi(argv[2]));
    int b = least(atoi(argv[1]), atoi(argv[2]));
    if (argc > 3) {
      cerr << "Warning: Expected 2 arguments, recieved " << (argc - 3) << ". Discarding extra args." << endl;
    }
    if (a <= 0 || b <= 0) {
      cerr << "Error: Unable to compute GCD and/or LCM because inputs must be natural numbers." << endl;
      return -1;
    }

    cout << "GCD(" << a << ", " << b << ") = " << gcd(a, b) << endl;
    lcm(a, b);

  } else {
    cerr << "Error: Unable to compute GCD and/or LCM because not enough arguments were passed." << endl;
    return -1;
  }
  return 0;
}

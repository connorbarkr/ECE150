#include <stdlib.h>
#include <iostream>
using namespace std;

int main(int argc, const char * argv[]) {
  if ((argc - 1) > 0) {
    float min = atof(argv[1]);
    float max = atof(argv[1]);
    float avg = atof(argv[1]);

    for (int x = 2; x < argc; x++) {
      float current = atof(argv[x]);
      if (current < min) {
        min = current;
      }
      if (current > max) {
        max = current;
      }
      avg += current;
    }

    cout << "Number of floating-point numbers: " << (argc - 1) << endl;
    cout << "Minimum floating-point number: " << min << endl;
    cout << "Average floating-point number: " << (avg/(argc - 1)) << endl;
    cout << "Maximum floating-point number: " << max << endl;
  }
  else {
    cerr << "Unable to compute statistics over data set because there isn't enough data." << endl;
  }

  return 0;
}

#include <stdlib.h>
#include <iostream>
using namespace std;

int main(int argc, const char * argv[]) {
  if ((argc - 1) > 0) {
    float min = atof(argv[1]);
    float max = atof(argv[1]);
    float avg;

    cout << "Sample\tValue\tMinimum\tAverage\tMaximum" << endl;
    for (int x = 1; x < argc; x++) {
      float current = atof(argv[x]);
      if (current < min) {
        min = current;
      } else if (current > max) {
        max = current;
      }
      avg += current;
      cout << x << "\t" << current << "\t" << min << "\t" << (avg / x) << "\t" << max << endl;
    }
  } else {
    cerr << "Unable to compute statistics over data set because there isn't enough data." << endl;
  }
  return 0;
}

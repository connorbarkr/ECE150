//
//  EWMA.cpp
//
//
//  Created by Connor Barker on 20/09/2017.
//
//

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cmath>

using namespace std;

int main(int argc, const char * argv[]) {
  if (argc < 5) {
    cerr << "Error: unable to compute statistics over data set because there isn't enough data." << endl;
  }
  if (atof(argv[1]) <= 0 || atof(argv[1]) >= 1) {
    cerr << "Error: alpha value must be 0 < a < 1." << endl;
  }
  if (atoi(argv[2]) < 1) {
    cerr << "Error: age limit must be a whole number greater than 0." << endl;
  }
  else {
    float alpha = atof(argv[1]);
    int limit = atoi(argv[2]);
    float min = atof(argv[3]);
    float max = atof(argv[3]);
    float EWMA = atof(argv[3]);
    int minCounter = 0;
    int maxCounter = 0;

    cout << "Sample\tValue\tMinimum\tEWMA\tMaximum" << endl;

    for (int x = 3; x < argc; x++) {
      float sample = atof(argv[x]);
      if (sample > max || maxCounter == limit) {
        max = sample;
        maxCounter = 0;
      }
      if (sample < min || minCounter == limit) {
        min = sample;
        minCounter = 0;
      }
      if (x > 0) {
        EWMA = (alpha * sample) + ((1 - alpha) * EWMA);
      }
      cout << x << "\t" << sample << "\t" << min << "\t" << EWMA << "\t" << max << endl;
      minCounter++;
      maxCounter++;
    }
    return 0;
  }
  return 0;
}

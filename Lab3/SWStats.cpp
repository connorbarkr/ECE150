//Created by Connor Barker on 2/10/17

#include <stdlib.h>
#include <iostream>
#include <math.h>

using namespace std;

int main(int argc, const char * argv[]) {
  if ((argc - 3) > 0) {
    int WS = atoi(argv[1]);
    float min = atof(argv[2]);
    float max = atof(argv[2]);
    float avg = 0;
    float k = 0;
    float sample;

    if (WS <= 0) {
      cerr << "Error: Unable to compute statistics over data set because the window size must be a natural number." << endl;
      return -1;
    }

    if (WS == 1 || WS > argc - 2) {
      cerr << "Warning: Window size is either 1 or greater than the number of inputted variables. Continuing." << endl;
    }

    cout << "Window Size: " << WS << endl;
    cout << "Sample\tValue\tSWMinimum\tSWAverage\tSWMaximum" << endl;
    for (int i = 2; i < argc; i++) {
      k = 0;
      if (i < (WS + 2)) {
        sample = atof(argv[i]);
        if (sample < min) {
          min = sample;
        }
        if (sample > max) {
          max = sample;
        }
        for (int j = 2; k < WS; j++) {
          if (j > i) {
            j = 2;
          }
          avg += atof(argv[j]);
          k++;
        }
        avg = avg / WS;
        cout << i - 1 << "\t" << sample << "\t" << min << "\t\t" << avg << "\t\t" << max << endl;
        avg = 0;
      }
      else {
        min = atof(argv[i]);
        max = atof(argv[i]);
        avg = 0;
        sample = atof(argv[i]);
        for (int j = (i + 1) - WS; j <= i; j++) {
          float current = atof(argv[j]);
          if (current < min) {
            min = current;
          }
          if (current > max) {
            max = current;
          }
          avg += current;
        }
        avg = avg / WS;
        cout << i - 1 << "\t" << sample << "\t" << min << "\t\t" << avg << "\t\t" << max << endl;
      }
    }
    return 0;
  }
  else {
    cerr << "Error: Unable to compute statistics over data set because there is insufficient data." << endl;
    return -1;
  }
}

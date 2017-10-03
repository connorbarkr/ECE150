//
//  ECBraking.cpp
//
//
//  Created by Connor Barker on 20/09/2017.
//
//

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <iomanip>

using namespace std;

int main(int argc, const char * argv[]) {
  if (argc >= 4) {

    if (argc > 4) {
      cerr << "Warning: Expecting three command-line arguments. Discarding extra arguments." << endl;
    }

    float velocity = atof(argv[1]);
    float distance = atof(argv[2]);
    float acceptable = abs(atof(argv[3]));
    float minDecel;
    float maxTime;
    float finalVelocity;
    float timeToCollision;

    if (distance < 0 && velocity < 0) {
      distance *= -1;
      velocity *= -1;
    }

    minDecel = (-(velocity * velocity))/(2 * distance);
    maxTime = (2 * distance) / velocity;
    finalVelocity = sqrt((pow(velocity, 2)) + (-2 * acceptable * distance));
    timeToCollision = 2 * distance / (finalVelocity + velocity);

    if (velocity == 0 || (distance <= 0 && velocity >= 0) || (distance >= 0 && velocity <= 0)) {
      cout << "There is no possibility of collision because distance and velocity have opposite signs, the car is already at the object, or the car is stationary." << endl;
      return 0;
    }
    if (abs(minDecel) > acceptable) {
      cout << "Crash will occur in " << abs(timeToCollision) << " seconds at velocity " << abs(finalVelocity) << " m/s; Deploying airbags." << endl;
      return 0;
    }
    cout << "Initial car velocity: " << velocity << " m/s" << endl;
    cout << "Distance to obstacle: " << distance << " m" << endl;
    cout << "Minimum deceleration: " << abs(minDecel) << " m/s/s" << endl;
    cout << "Maximum stopping time: " << maxTime << " s" << endl;
    return 0;
  }
  else {
    cerr << "Error: insufficient arguments." << endl;
    return 0;
  }
}

//
//  Braking.cpp
//  
//
//  Created by Connor Barker on 13/09/2017.
//
//

#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, const char * argv[]) {
    float velocity = atof(argv[1]);
    float distance = atof(argv[2]);
    float minDecel;
    float maxTime;
    
    minDecel = (-(velocity*velocity))/(2*distance);
    maxTime = (2*distance)/velocity;
    
    cout << "Initial car velocity: " << velocity << " m/s" << endl;
    cout << "Distance to obstacle: " << distance << " m" << endl;
    cout << "Minimum deceleration: " << minDecel << " m/s/s" << endl;
    cout << "Maximum stopping time: " << maxTime << " s" << endl;
    return 0;
}

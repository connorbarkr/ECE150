//
//  Logic.cpp
//  
//
//  Created by Connor Barker on 13/09/2017.
//
//

#include <stdlib.h>
#include <iostream>

using namespace std;

int main(int argc, const char * argv[]) {
    int P = atoi(argv[1]);
    int Q = atoi(argv[2]);
    
    cout << "P: " << P << endl;
    cout << "Q: " << Q << endl;
    cout << "P AND Q: " << (P && Q) << endl;
    cout << "P OR Q: " << (P || Q) << endl;
    cout << "NOT P: " << (!P) << endl;
    cout << "NOT Q: " << (!Q) << endl;
    return 0;
}

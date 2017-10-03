//
//  main.cpp
//  DataTypes
//
//  Created by Connor Barker on 13/09/2017.
//  Copyright © 2017 Eskimopies. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <float.h>
#include <limits.h>

using namespace std;

int main(int argc, const char * argv[]) {
    char a;
    short int b;
    int c;
    long int d;
    long long int e;
    unsigned char f;
    unsigned short int g;
    unsigned int h;
    unsigned long int i;
    unsigned long long int j;
    float k;
    double l;
    long double m;
    
    int x;
    unsigned int y;
    x = atoi(argv[1]);
    y = x;
    int shiftTimes = (sizeof(x)*8) - 1;
    int mostSignificantX = ((x >> shiftTimes) && 01);
    
    cout << "The value of x is " << x << endl;
    cout << "The value of y is " << y << endl;
    cout << "The most significant bit of x is " << mostSignificantX << endl;
    cout << "The most significant bit of y is " << (y >> shiftTimes) << endl;
    
    cout << "Type: \"signed char\"; Size: " << sizeof(a) << " bytes; Minimum value: " << SCHAR_MIN << " ; Maximum value: " << SCHAR_MAX << endl;
    cout << "Type: \"unsigned char\"; Size: " << sizeof(f) << " bytes; Minimum value: " << 0 << " ; Maximum value: " << UCHAR_MAX << endl;
    cout << "Type: \"short int\"; Size: " << sizeof(b) << " bytes; Minimum value: " << SHRT_MIN << " ; Maximum value: " << SHRT_MAX << endl;
    cout << "Type: \"unsigned short int\"; Size: " << sizeof(g) << " bytes; Minimum value: " << 0 << " ; Maximum value: " << USHRT_MAX << endl;
    cout << "Type: \"int\"; Size: " << sizeof(c) << " bytes; Minimum value: " << INT_MIN << " ; Maximum value: " << INT_MAX << endl;
    cout << "Type: \"unsigned int\"; Size: " << sizeof(h) << " bytes; Minimum value: " << 0 << " ; Maximum value: " << UINT_MAX << endl;
    cout << "Type: \"long int\"; Size: " << sizeof(d) << " bytes; Minimum value: " << LONG_MIN << " ; Maximum value: " << LONG_MAX << endl;
    cout << "Type: \"unsigned long int\"; Size: " << sizeof(i) << " bytes; Minimum value: " << 0 << " ; Maximum value: " << ULONG_MAX << endl;
    cout << "Type: \"long long int\"; Size: " << sizeof(e) << " bytes; Minimum value: " << LLONG_MIN << " ; Maximum value: " << LLONG_MAX << endl;
    cout << "Type: \"unsigned long long int\"; Size: " << sizeof(j) << " bytes; Minimum value: " << 0 << " ; Maximum value: " << ULLONG_MAX << endl;
    cout << "Type: \"float\"; Size: " << sizeof(k) << " bytes; Minimum value: " << FLT_MIN << " ; Maximum value: " << FLT_MAX << endl;
    cout << "Type: \"double\"; Size: " << sizeof(l) << " bytes; Minimum value: " << DBL_MIN << " ; Maximum value: " << DBL_MAX << endl;
    cout << "Type: \"long double\"; Size: " << sizeof(m) << " bytes; Minimum value: " << LDBL_MIN << " ; Maximum value: " << LDBL_MAX << endl;
    return 0;
}

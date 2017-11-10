//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING
#include <iostream>
using namespace std;
#endif

//////////////////////////////////////////////////////////////
//
// Function declarations; do not remove
// Replace "..." in bisectionHelper() with any parameter(s)
// you need to ensure termination when precision and
// minIntervalSize are too tightly specified.
//

bool stringToInt(const char input[], int& value);

//////////////////////////////////////////////////////////////
//
// Your code here ...
//
// Return std::numeric_limits<float>::quiet_NaN() (comes from
// <limits>) if cannot compute the root for some reason
//

enum inputType { INT, SIGN, NOTINT, UNKNOWN, DONE };

int absoluteInt(int number) {
	if (number < 0) {
		return number * -1;
	}
	else {
		return number;
	}
}

long long absoluteLL(long long number) {
	if (number < 0) {
		return number * -1;
	}
	else {
		return number;
	}
}

int toInt(char inputChar) {
	if (inputChar == '0') return 0;
	if (inputChar == '1') return 1;
	if (inputChar == '2') return 2;
	if (inputChar == '3') return 3;
	if (inputChar == '4') return 4;
	if (inputChar == '5') return 5;
	if (inputChar == '6') return 6;
	if (inputChar == '7') return 7;
	if (inputChar == '8') return 8;
	if (inputChar == '9') return 9;
}

long long toLong(char inputChar) {
	if (inputChar == '0') return 0;
	if (inputChar == '1') return 1;
	if (inputChar == '2') return 2;
	if (inputChar == '3') return 3;
	if (inputChar == '4') return 4;
	if (inputChar == '5') return 5;
	if (inputChar == '6') return 6;
	if (inputChar == '7') return 7;
	if (inputChar == '8') return 8;
	if (inputChar == '9') return 9;
}

bool signCheck(char inputChar) {
	if (inputChar == '-') {
		return true;
	}
	return false;
}

int check(const char input[], int currentIteration) {
	char inputChar = input[currentIteration];
	if (inputChar == '0' ||
	    inputChar == '1' ||
	    inputChar == '2' ||
	    inputChar == '3' ||
	    inputChar == '4' ||
	    inputChar == '5' ||
	    inputChar == '6' ||
	    inputChar == '7' ||
	    inputChar == '8' ||
	    inputChar == '9') {
		return 3;
	}
	if (inputChar == '-' ||
	    inputChar == '+') {
		return 2;
	}
	if (inputChar == '\0') {
		return 1;
	}
	return 0;
}

bool stringHelper(const char input[], int& value, int currentIteration, const inputType type, int number, bool negative, long long checknum) {
	char inputChar = input[currentIteration];
	switch (type) {
	case UNKNOWN:
		if (check(input, currentIteration) == 1) return stringHelper(input, value, currentIteration, NOTINT, number, negative, checknum); // case DONE (notint)
		if (check(input, currentIteration) == 2) return stringHelper(input, value, currentIteration, SIGN, number, negative, checknum); // case SIGN
		if (check(input, currentIteration) == 3) return stringHelper(input, value, currentIteration, INT, number, negative, checknum); // case INT
		if (check(input, currentIteration) == 0) return stringHelper(input, value, currentIteration, NOTINT, number, negative, checknum); // case NOTINT
	case SIGN:
		if (signCheck(inputChar)) {
			negative = true;
		}
		if (check(input, currentIteration + 1) == 1) return stringHelper(input, value, currentIteration + 1, NOTINT, number, negative, checknum);
		if (check(input, currentIteration + 1) == 2) return stringHelper(input, value, currentIteration + 1, NOTINT, number, negative, checknum);
		if (check(input, currentIteration + 1) == 3) return stringHelper(input, value, currentIteration + 1, INT, number, negative, checknum);
		if (check(input, currentIteration + 1) == 0) return stringHelper(input, value, currentIteration + 1, NOTINT, number, negative, checknum);
	case INT:
		checknum = (checknum * 10) + toLong(inputChar);
		number = (number * 10) + toInt(inputChar);
		if ((absoluteInt(number) > absoluteLL(checknum)) || (absoluteLL(checknum) > absoluteInt(number))) return stringHelper(input, value, currentIteration + 1, NOTINT, number, negative, checknum);
		if (check(input, currentIteration + 1) == 1) return stringHelper(input, value, currentIteration + 1, DONE, number, negative, checknum);
		if (check(input, currentIteration + 1) == 2) return stringHelper(input, value, currentIteration + 1, NOTINT, number, negative, checknum);
		if (check(input, currentIteration + 1) == 3) return stringHelper(input, value, currentIteration + 1, INT, number, negative, checknum);
		if (check(input, currentIteration + 1) == 0) return stringHelper(input, value, currentIteration + 1, NOTINT, number, negative, checknum);
	case NOTINT:
		return false;
	case DONE:
		value = number;
		if (negative) value *= -1;
		return true;
	}
}

bool stringToInt(const char input[], int& value) {
	return stringHelper(input, value, 0, UNKNOWN, 0, false, 0);
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

#define isNaN(X) (X != X)  // NaN is the only float that is not equal to itself

int main(const int argc, const char* const argv[]) {

	// Some test driver code here ....
	int argv1;
	if (argc < 2) {
		cerr << "Error: Usage: " << argv[0] << " <int>" << endl;
		return -1;
	}

	if (stringToInt(argv[1],argv1))
		cout << "argv[1] is an int with value: " << argv1 <<endl;
	else
		cout << "argv[1] is not an int." << endl;
	return 0;
}

#endif

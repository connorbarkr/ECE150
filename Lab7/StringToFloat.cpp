//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
// You are allowed float.h

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

bool stringToFloat(const char input[], float& value);

//////////////////////////////////////////////////////////////
//
// Your code here ...

enum STATETYPE { START, SIGN, INT, DECIMAL, FLOAT, POWER, TERMINAL };

float power(float number, float power) {
	float result = number;
	if (power == 0) {
		return 1;
	}
	for (int i = 1; i < power; i++) {
		result *= number;
	}
	return result;
}

int signCheck(char inputChar) {
	if (inputChar == '-') {
		return 1;
	}
	else if (inputChar == '+') {
		return 2;
	}
	return -1;
}

bool nullCheck(char inputChar) {
	if (inputChar == '\0') return true;
	return false;
}

float toFloat(char inputChar) {
	if (((inputChar - 48) >= 0) && ((inputChar - 48) <= 9)) return ((float) inputChar - 48);
	return -1;
}

long double toLD(char inputChar) {
	if (((inputChar - 48) >= 0) && ((inputChar - 48) <= 9)) return ((long double) inputChar - 48);
	return -1;
}

bool stringToFloat(const char input[], float& value) {
	bool valid = true;
	STATETYPE STATE = START;
	long double verify = 0;
	float result = 0;
	int c = 0;
	bool neg = false;
	bool expNeg = false;
	int ec = 0;
	float dp = 0;

	while (valid && STATE != TERMINAL) {
		switch (STATE) {
		case START:
			if (signCheck(input[c]) > 0) {
				STATE = SIGN;
				break;
			}
			if (input[c] == '.') {
				STATE = DECIMAL;
				break;
			}
			if (toFloat(input[c]) >= 0) {
				STATE = INT;
				break;
			}
			valid = false;
			break;
		case SIGN:
			if (signCheck(input[c]) == 1) {
				neg = true;
			}
			c++;
			if (input[c] == '.') {
				STATE = DECIMAL;
				break;
			}
			if (toFloat(input[c]) >= 0) {
				STATE = INT;
				break;
			}
			valid = false;
			break;
		case INT:
			verify = (verify * 10.0) + toLD(input[c]);
			result = (result * 10.0) + toFloat(input[c]);
			c++;
			if (input[c] == '.') {
				STATE = DECIMAL;
				break;
			}
			if (toFloat(input[c]) >= 0) {
				STATE = INT;
				break;
			}
			if (input[c] == 'e') {
				STATE = POWER;
				break;
			}
			if (nullCheck(input[c])) {
				STATE = TERMINAL;
				break;
			}
			valid = false;
			break;
		case DECIMAL:
			c++;
			if (toFloat(input[c]) >= 0) {
				STATE = FLOAT;
				break;
			}
			if (nullCheck(input[c])) {
				STATE = TERMINAL;
				break;
			}
			valid = false;
			break;
		case FLOAT:
			dp++;
			verify += (((long double) (1.0/(power(10.0, dp)))) * toLD(input[c]));
			result += (((float) (1.0/(power(10.0, dp)))) * toFloat(input[c]));
			c++;
			if (input[c] == 'e') {
				STATE = POWER;
				break;
			}
			if (toFloat(input[c]) >= 0) {
				STATE = FLOAT;
				break;
			}
			if (nullCheck(input[c])) {
				STATE = TERMINAL;
				break;
			}
			valid = false;
			break;
		case POWER:
			if (toFloat(input[c]) >= 0) {
				ec += (ec * 10) + toFloat(input[c]);
			}
			cout << ec << endl;
			c++;
			if (signCheck(input[c]) > 0) {
				if (signCheck(input[c]) == 1) expNeg = true;
				STATE = POWER;
				break;
			}
			if (toFloat(input[c]) >= 0) {
				STATE = POWER;
				break;
			}
			if (nullCheck(input[c])) {
				STATE = TERMINAL;
				break;
			}
			valid = false;
			break;
		}
	}
	if (valid && STATE == TERMINAL) {
		if (neg) {
			result *= -1.0;
			verify *= -1.0;
		}
		if (expNeg) {
			result /= power(10, ec);
			verify /= power(10, ec);
		}
		else {
			result *= power(10, ec);
			verify *= power(10, ec);
		}
		value = result;
		return true;
	}
	return false;
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
int main(const int argc, const char* const argv[]) {

	// Some test driver code here ....
	float argv1;

	if (argc < 2) {
		cerr << "Error: Usage: " << argv[0] << " <float>" << endl;
		return -1;
	}

	if (stringToFloat(argv[1],argv1))
		cout << "argv[1] is a float with value: " << argv1 <<endl;
	else
		cout << "argv[1] is not a float. argv[1]: " <<argv[1] << endl;
	return 0;
}

#endif

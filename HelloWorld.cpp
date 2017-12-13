#include <iostream>

using namespace std;

int power(int number, int exponent) {
	int result = number;
	for (int i = 1; i < exponent; i++) {
		result *= result;
	}
	return result;
}

int main(const int argc, const char* const argv[]) {
	// Code below
	cout << power(5, 15) << endl;
	return 0;
}

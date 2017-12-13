#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;

int intToArray(int num, int data[], int index) {
	cout << "called" << endl;
	if (num == 0) {
		return 0;
	}
	data[index] = num % 10;
	return 1 + intToArray(num/10, data, index+1);
}

int intToArray1(int num, int data[], int index) {
	while (num != 0) {
		data[index] = num % 10;
		num = num/10;
		index++;
	}
	return index;
}

int main() {
	int x= 314159;
	int data[10]= {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
	cout << intToArray1(x, data, 0) << endl;
}

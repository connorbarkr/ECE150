//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <limits>

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
// #defines, enum, and function declarations; do not remove
//

#define isNaN(X) (X != X)  // NaN is the only float that is not equal to itself
#define NaN std::numeric_limits<float>::quiet_NaN() // (comes from <limits>)

enum sortType { ASCENDING, DESCENDING, UNKNOWN, UNSORTED };

bool isSorted(const float data[], const int currentDataItem, const sortType typeOfSort);
bool sorted(const float data[]);

//////////////////////////////////////////////////////////////
//
// Your code here ...
//
//

bool isSorted(const float data[], const int currentDataItem, const sortType typeOfSort) {
	bool sort = true;
	int size = 0;
	while (data[size] == data[size]) {
		size++;
	}
	if (data[0] != data[0]) {
		return false;
	}

	if (data[currentDataItem + 1] == data[currentDataItem + 1]) {
		switch (typeOfSort) {
		case UNKNOWN:
			if (data[currentDataItem] < data[currentDataItem + 1]) {
				return isSorted(data, currentDataItem + 1, ASCENDING);
			} else {
				return isSorted(data, currentDataItem + 1, DESCENDING);
			}
		case ASCENDING:
			if (data[currentDataItem] <= data[currentDataItem + 1]) {
				return isSorted(data, currentDataItem + 1, ASCENDING);
			} else {
				return isSorted(data, currentDataItem, UNSORTED);
			}
		case DESCENDING:
			if (data[currentDataItem] >= data[currentDataItem + 1]) {
				return isSorted(data, currentDataItem + 1, DESCENDING);
			} else {
				return isSorted(data, currentDataItem, UNSORTED);
			}
		case UNSORTED:
			if ((data[currentDataItem] > data[currentDataItem + 1]) && (data[currentDataItem] < data[currentDataItem] + 1)) {
				sort = false;
				break;
			}
			sort = false;
			break;
		}
	}
	return sort;
}

bool sorted(const float data[]) {
	return isSorted(data, 0, UNKNOWN);
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
	float data[] = {-293.21, -120.3, -9.2, 4, 4, -53.23, -230.43, -840.324, NaN};

	if (sorted(data))
		cout << "Data is sorted" << endl;
	else
		cout << "Data is not sorted" << endl;

	return 0;
}

#endif

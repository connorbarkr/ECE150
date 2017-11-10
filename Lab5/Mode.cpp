//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

// int modes = 0;
// int mode_max = 0;
// int working[size];
// int j = 0;
// map<int, int> mapped;
// vector<int> keys;
// for (int i = 0; i < size; i++) {
//      working[i] = dataset[i];
// }
// bool sorted = sort(working, size);
// for (int i = 0; i < size; i++) {
//      if (mapped.find(working[i]) == mapped.end()) mapped[working[i]] = 0;
//      mapped[working[i]]++;
// }
// for(map<int,int>::iterator it = mapped.begin(); it != mapped.end(); ++it) {
//      keys.push_back(it->first);
// }
// for (int i = 0; i < mapped.size(); i++) {
//      if (mapped[keys[i]] > mode_max) mode_max = mapped[keys[i]];
// }
// for (int i = 0; i < mapped.size(); i++) {
//      if (mapped[keys[i]] == mode_max) {
//              modes += 1;
//              mode[j] = keys[i];
//              j++;
//      }
// }
// if (!sorted) return -1;
// return modes;

#include <stdlib.h>
// #include <map>
// #include <vector>

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

int range(const int dataset[], const int size);
int mode(const int dataset[], const int size, int mode[]);
bool sort(int dataset[], const int size);

//////////////////////////////////////////////////////////////
//
// Your code here ...
//  Return -1 if there there are any problems with the dataset.
//


void swap(int *xp, int *yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void selection(int arr[], int size) {
	int maxIndex = 0, temp = 0, index = 0;
	for (index = maxIndex; index < size; index++) {
		if (arr[index] > arr[maxIndex]) {
			maxIndex = index;
		}
	}
	temp = arr[size - 1];
	arr[size - 1] = arr[maxIndex];
	arr[maxIndex] = temp;

	if (size > 1) {
		selection(arr, --size);
	}
}


bool sort(int dataset[], const int size) {
	int workingsize = size;
	if (size < 1) {
		return false;
	}
	selection(dataset, workingsize);
	return true;
}



int range(const int dataset[], const int size) {
	int working[size];
	for (int i = 0; i < size; i++) {
		working[i] = dataset[i];
	}
	bool sorted = sort(working, size);
	int ran = working[size - 1] - working[0];
	if (sorted && ran > 0) return ran;
	return -1;
}

int mode(const int dataset[], const int size, int mode[]) {
	if (size < 1) {
		return -1;
	}
	int modalmax = 0;
	int count = 0;
	int** working = new int*[size];
	for (int i = 0; i < size; i++) {
		working[i] = new int[2];
		working[i][0] = dataset[i];
		working[i][1] = 1;
	}
	for (int i = 0; i < size; i++) {
		if ((working[i][1] != -1) && (i != size - 1)) {
			for (int j = i + 1; j < size; j++) {
				if (working[j][0] == working[i][0]) {
					working[j][1] = -1;
				}
			}
		}
	}
	for (int i = 0; i < size; i++) {
		if ((working[i][1] != -1) && (i != size - 1)) {
			for (int j = i + 1; j < size; j++) {
				if (working[j][0] == working[i][0]) {
					working[i][1]++;
				}
			}
		}
	}
	for (int i = 0; i < size; i++) {
		if (working[i][1] > modalmax) modalmax = working[i][1];
	}
	for (int i = 0; i < size; i++) {
		if (working[i][1] == modalmax) {
			mode[count] = working[i][0];
			count++;
		}
	}
	return count;
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
	int data[] = {9999, 10000, 9995, 10000, 9996, 9998, 9995, 9997, 10000, 9998, 9997, 9996, 9995, 9997, 9998};
	int size = 15;
	int modeArray[4];
	sort(data, size);
	int rng = range(data, size);
	int modes = mode(data, size, modeArray);
	cout << "range: " << rng << " number of Modes: " << modes << " Modes are this: ";
	for(int i = 0; i<modes; i++) {
		cout<< modeArray[i];
		if(i<modes-1) {
			cout << ", ";
		}
	}
	cout<<endl;
	return 0;
}

#endif

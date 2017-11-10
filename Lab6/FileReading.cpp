//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <fstream>

//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING
#include <iostream>
using namespace std;
#endif

using namespace std;
//////////////////////////////////////////////////////////////
//
// Function declarations; do not remove
// Replace "..." in bisectionHelper() with any parameter(s)
// you need to ensure termination when precision and
// minIntervalSize are too tightly specified.
//

int histogram(const char filename[], int histogram[10],
              const int minAcceptableID, const int maxAcceptableID,
              int*& rejects);

//////////////////////////////////////////////////////////////
//
// Your code here ...
//
// Return -1 if you cannot compute the histogram for any
// reason;
// Return 0 if the histogram is correct and there are no
// rejections;
// Return the number of rejects if there are rejected
// records from the file
//

int toInt(char inputChar) {
	if (((inputChar - 48) >= 0) && ((inputChar - 48) <= 9)) return inputChar - 48;
	if (inputChar == ' ' ||
	    inputChar == ',' ||
	    inputChar == '\t' ||
	    inputChar == '\n') {
		return -1;
	}
	if (inputChar == '-') {
		return -2;
	}
	return -3;
}

int bucketIt(int grade) {
	if (grade >= 0 && grade < 10) return 0;
	if (grade >= 10 && grade < 20) return 1;
	if (grade >= 20 && grade < 30) return 2;
	if (grade >= 30 && grade < 40) return 3;
	if (grade >= 40 && grade < 50) return 4;
	if (grade >= 50 && grade < 60) return 5;
	if (grade >= 60 && grade < 70) return 6;
	if (grade >= 70 && grade < 80) return 7;
	if (grade >= 80 && grade < 90) return 8;
	if (grade >= 90 && grade <= 100) return 9;
	return -1;
}

int* parseLine(char line[], const int maxAcceptableID,
               const int minAcceptableID, int*& rejects,
               int fileLineNumber) {
	int returnArray[2] = {0};
	int currentIndex = 0;
	int studentId = 0;
	int grade = 0;
	bool negative = false;
	while (toInt(line[currentIndex]) < 0) {
		++currentIndex;
	}
	while (studentId < maxAcceptableID) {
		if (toInt(line[currentIndex]) < 0) {
			break;
		}
		studentId = (studentId * 10) + toInt(line[currentIndex]);
		++currentIndex;
	}
	while (toInt(line[currentIndex]) < 0) {
		++currentIndex;
	}
	if (toInt(line[currentIndex]) == 10) {
		negative = true;
		++currentIndex;
	}
	while (grade <= 100) {
		if (toInt(line[currentIndex]) < 0) {
			break;
		}
		grade = (grade * 10) + toInt(line[currentIndex]);
		++currentIndex;
	}
	if (studentId < minAcceptableID || studentId > maxAcceptableID || grade > 100) {
		studentId = fileLineNumber;
		grade = -1;
	}
	for (int i = 0; i < currentIndex; i++) {
		if (toInt(line[i]) == -2) {
			grade = -1;
		}
		if (toInt(line[i]) == -3) {
			returnArray[0] = 0;
			returnArray[1] = -2;
			return returnArray;
		}
	}
	returnArray[0] = studentId;
	returnArray[1] = grade;
	return returnArray;
}

int histogram(const char filename[], int histogram[10],
              const int minAcceptableID, const int maxAcceptableID,
              int*& rejects) {
	if (minAcceptableID > maxAcceptableID) {
		return -1;
	}
	if (&histogram[0] == NULL) {
		return -1;
	}
	const int maxLineLength = 100;
	char line[maxLineLength];
	bool done = false;
	int fileLineNumber = 0;
	int rejectSize = 0;
	int *tempArray;
	ifstream infile;
	infile.open(filename);
	for (int i = 0; i < 10; i++) {
		histogram[i] = 0;
	}
	if (!infile.is_open()) {
		return -1;
	}
	while (!done) {
		++fileLineNumber;
		if (!infile.getline(line, maxLineLength)) {
			if (infile.eof()) {
				done = true;
			}
			else {
				return -1;
			}
		}
		if (done == false) {
			int *working = parseLine(line, maxAcceptableID, minAcceptableID, rejects, fileLineNumber);
			int id = working[0];
			int grade = working[1];
			if (grade == -2) {
				return -1;
			}
			if (grade < 0) {
				if (rejectSize > 0) {
					tempArray = new int [rejectSize];
					for (int i = 0; i < rejectSize; i++) {
						tempArray[i] = rejects[i];
					}
				}
				++rejectSize;
				rejects = new int [rejectSize];
				if (grade < 0) {
					for (int i = 0; i < rejectSize - 1; i++) {
						rejects[i] = tempArray[i];
					}
				}
				rejects[rejectSize - 1] = fileLineNumber;
			}
			int bucket = bucketIt(grade);
			if (bucket >= 0) {
				histogram[bucket]++;
			}
		}
	}
	return rejectSize;
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
	if (argc < 2) {

	}
	const int numBuckets = 10;
	const int bucketRange = 100/numBuckets;
	int buckets[numBuckets];
	int* rejectedRecords;
	int retCode = histogram(argv[1], buckets, 20700000, 20799999, rejectedRecords);
	if (retCode < 0) {
		cout << "Unable to compute histogram." << endl;
	}
	else {
		for (int i = 0; i < numBuckets; ++i)
			if (i != numBuckets-1)
				cout << "Number [" << i*bucketRange << "," << (((i+1)*bucketRange)-1) << "]: " << buckets[i] << endl;
			else
				cout << "Number [" << i*bucketRange << "," << (((i+1)*bucketRange)) << "]: " << buckets[i] << endl;
		if (retCode > 0) {
			cout << "Number of rejected records: " << retCode << endl;
			cout << "Rejected records are:";
			for (int i = 0; i < retCode; ++i)
				cout << " " << rejectedRecords[i];
			cout << endl;
			delete[] rejectedRecords;
		}
	}

	return 0;
}

#endif

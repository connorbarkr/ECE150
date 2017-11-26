//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <fstream>
#include <math.h>

//////////////////////////////////////////////////////////////
//
// local #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING
#include <iostream>
#endif

using namespace std;

//////////////////////////////////////////////////////////////
//
// struct definitions
//
#ifndef MARMOSET_TESTING
struct Student {
	int studentID;
	int grade;
};

struct Dataset {
	int numStudents;
	Student* students;
};

struct Rejects {
	int numRejects;
	int* rejects;
};

struct Mode {
	int numModes;
	int* modes;
};

struct Statistics {
	int minimum;
	float average;
	int maximum;
	float popStdDev;
	float smplStdDev;
	Mode mode;
	int histogram[10];
};
#endif

//////////////////////////////////////////////////////////////
//
// Function declarations; do not remove
//
int readCSV(const char filename[],const int minAcceptableID,
            const int maxAcceptableID,Dataset& data,
            Rejects& rejects);

int computeStatistics(Dataset& data, Statistics& stats);

int writeCSV(const char filename[], const Statistics& stats);

//////////////////////////////////////////////////////////////
//
// Function definitions. PLEASE USE HELPER FUNCTIONS
//

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

char* changeExtension(const char filename[], int type) {
	char *newname;
	int c = 0;
	if (type == 1) {
		while (filename[c] != '\0' && filename[c] != '.') {
			c++;
		}
		newname = new char [c + 3];
		for (int i = 0; i < c; i++) {
			newname[i] = filename[i];
		}
		newname[c] = '.';
		newname[c + 1] = 'c';
		newname[c + 2] = 's';
		newname[c + 3] = 'v';
	}
	else if (type == 2) {
		while (filename[c] != '\0' && filename[c] != '.') {
			c++;
		}
		newname = new char [c + 4];
		for (int i = 0; i < c; i++) {
			newname[i] = filename[i];
		}
		newname[c] = '.';
		newname[c + 1] = 's';
		newname[c + 2] = 't';
		newname[c + 3] = 'a';
		newname[c + 4] = 't';
	}
	return newname;
}

bool minimum(int dataset[], int size, Statistics &stats) {
	if (size <= 0) return false;
	int min = dataset[0];
	for (int i = 1; i < size; i++) {
		int current = dataset[i];
		if (current < min) {
			min = current;
		}
	}
	stats.minimum = min;
	return true;
}

bool maximum(int dataset[], int size, Statistics &stats) {
	if (size <= 0) return false;
	int max = dataset[0];
	for (int i = 1; i < size; i++) {
		int current = dataset[i];
		if (current > max) {
			max = current;
		}
	}
	stats.maximum = max;
	return true;
}

bool average(int dataset[], int size, Statistics &stats) {
	if (size <= 0) return false;
	float mean = 0;
	for (int i = 0; i < size; i++) {
		float current = (float) dataset[i];
		mean += current;
	}
	stats.average =  mean / ((float) size);
	return true;
}

bool popStdDev(int dataset[], int size, Statistics& stats) {
	if (size <= 0) return false;
	float avg = stats.average;
	float sum = 0;
	for (int i = 0; i < size; i++) {
		float sample = (float) dataset[i];
		sum += pow((sample - avg), 2);
	}
	stats.popStdDev = (sqrt((1.0 / (size)) * sum));
	return true;
}

bool smplStdDev(int dataset[], int size, Statistics& stats) {
	if (size <= 1) return false;
	float avg = stats.average;
	float sum = 0;
	for (int i = 0; i < size; i++) {
		float sample = (float) dataset[i];
		sum += pow((sample - avg), 2);
	}
	stats.smplStdDev = sqrt((1.0 / (size - 1.0)) * sum);
	return true;
}

bool histogram(int dataset[], int size, Statistics& stats) {
	if (size <= 0) return false;
	for (int i = 0; i < size; i++) {
		int bucket = bucketIt(dataset[i]);
		if (bucket >= 0) {
			stats.histogram[bucket]++;
		}
	}
	return true;
}

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

bool mode(int dataset[], int size, Statistics &stats) {
	int *mode = new int [1];
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
			count++;
		}
	}
	stats.mode.numModes = count;
	stats.mode.modes = new int [count];
	count = 0;
	for (int i = 0; i < size; i++) {
		if (working[i][1] == modalmax) {
			stats.mode.modes[count] = working[i][0];
			count++;
		}
	}
	return true;
}

int* parseLine(char line[], const int maxAcceptableID,
               const int minAcceptableID, int fileLineNumber) {
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

int readCSV(const char filename[],const int minAcceptableID,
            const int maxAcceptableID, Dataset& data,
            Rejects& rejects){
	if (minAcceptableID > maxAcceptableID) {
		return -1;
	}
	char *newname = changeExtension(filename, 1);
	const int maxLineLength = 100;
	char line[maxLineLength];
	bool done = false;
	int fileLineNumber = 0;
	rejects.numRejects = 0;
	data.numStudents = 0;
	int *tempRejects;
	Student *tempStudents;
	ifstream infile;
	infile.open(newname);
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
			int *working = parseLine(line, maxAcceptableID, minAcceptableID, fileLineNumber);
			int id = working[0];
			int grade = working[1];
			if (grade == -2) {
				return -1;
			}
			if (grade < 0) {
				if (rejects.numRejects > 0) {
					tempRejects = new int [rejects.numRejects];
					for (int i = 0; i < rejects.numRejects; i++) {
						tempRejects[i] = rejects.rejects[i];
					}
				}
				++rejects.numRejects;
				rejects.rejects = new int [rejects.numRejects];
				if (grade < 0) {
					for (int i = 0; i < rejects.numRejects - 1; i++) {
						rejects.rejects[i] = tempRejects[i];
					}
				}
				rejects.rejects[rejects.numRejects - 1] = fileLineNumber;
			} else {
				Student current;
				current.studentID = working[0];
				current.grade = working[1];
				if (data.numStudents > 0) {
					tempStudents = new Student [data.numStudents];
					for (int i = 0; i < data.numStudents; i++) {
						tempStudents[i] = data.students[i];
					}
				}
				++data.numStudents;
				data.students = new Student [data.numStudents];
				for (int i = 0; i < data.numStudents - 1; i++) {
					data.students[i] = tempStudents[i];
				}
				data.students[data.numStudents - 1] = current;
			}
		}
	}
	return rejects.numRejects;
}

int computeStatistics(Dataset& data, Statistics& stats) {
	int *dataset = new int [data.numStudents];
	int size = data.numStudents;
	for (int i = 0; i < data.numStudents; i++) {
		dataset[i] = data.students[i].grade;
	}
	if (!mode(dataset, size, stats)) return -1;
	if (!minimum(dataset, size, stats)) return -1;
	if (!average(dataset, size, stats)) return -1;
	if (!maximum(dataset, size, stats)) return -1;
	if (!popStdDev(dataset, size, stats)) return -1;
	if (!smplStdDev(dataset, size, stats)) return -1;
	if (!histogram(dataset, size, stats)) return -1;
	return 0;
}

int writeCSV(const char filename[], const Statistics& stats) {
	char *newname = changeExtension(filename, 2);
	ofstream outfile;
	outfile.open(newname);
	if(!outfile.is_open()) {
		return -1;
	}
	outfile << "Minimum: " << stats.minimum << '\n';
	outfile << "Average: " << stats.average << '\n';
	outfile << "Maximum: " << stats.maximum << '\n';
	outfile << "Population Standard Deviation: " << stats.popStdDev << '\n';
	outfile << "Sample Standard Deviation: " << stats.smplStdDev << '\n';
	outfile << "Modes: ";
	for (int i = 0; i < stats.mode.numModes; i++) {
		if (i != stats.mode.numModes - 1) {
			outfile << stats.mode.modes[i] << ", ";
		}
		else {
			outfile << stats.mode.modes[i] << '\n';
		}
	}
	outfile << "Histogram:" << '\n';
	outfile << "[0-9]: " << stats.histogram[0] << '\n';
	outfile << "[10-19]: " << stats.histogram[1] << '\n';
	outfile << "[20-29]: " << stats.histogram[2] << '\n';
	outfile << "[30-39]: " << stats.histogram[3] << '\n';
	outfile << "[40-49]: " << stats.histogram[4] << '\n';
	outfile << "[50-59]: " << stats.histogram[5] << '\n';
	outfile << "[60-69]: " << stats.histogram[6] << '\n';
	outfile << "[70-79]: " << stats.histogram[7] << '\n';
	outfile << "[80-89]: " << stats.histogram[8] << '\n';
	outfile << "[90-100]: " << stats.histogram[9] << '\n';
	outfile.close();
	return 0;
}
//////////////////////////////////////////////////////////////
//
// Test Driver
//
// Do not remove the #ifndef and its associated #endif
//

#ifndef MARMOSET_TESTING

#define isNaN(X) (X != X)  // NaN is the only float that is not equal to itself

int main(const int argc, const char* const argv[]) {

	// Some test driver code here ....
	int minAcceptableID = 0;
	int maxAcceptableID = 2000000;

	Dataset data = {0};
	Rejects rejects = {0};
	Statistics stats = {0};

	if(readCSV(argv[1], minAcceptableID, maxAcceptableID, data, rejects) < 0)
	{
		std::cout << ".csv file could not be read" << std::endl;
	}

	if (computeStatistics(data, stats) < 0)
	{
		std::cout << "Stats could not be computed" << std::endl;
	}

	if (writeCSV(argv[1], stats) < 0)
	{
		std::cout << ".stat file could not be written" << std::endl;
	}

	std::cout << "Average: " << stats.average << std::endl;
	std::cout << "Minimum: " << stats.minimum << std::endl;
	std::cout << "Maximum: " << stats.maximum << std::endl;
	std::cout << "Population standard deviation: " << stats.popStdDev << std::endl;
	std::cout << "Sample standard deviation: " << stats.smplStdDev << std::endl;


	for (unsigned char i = 0; i < stats.mode.numModes; i++)
	{
		std::cout << "Mode: " << stats.mode.modes[i] << std::endl;
	}

	for (unsigned char i = 0; i < 10; i++)
	{
		std::cout << "Histogram bin [" << (i*10) << ", " << ((((i+1)*10) - 1) + i/9) << "]: " << stats.histogram[i] << std::endl;
	}
	return 0;
}

#endif

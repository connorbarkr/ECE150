//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

//////////////////////////////////////////////////////////////
//
// local #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING
#include <iostream>
#endif

//////////////////////////////////////////////////////////////
//
// struct definitions 
//

struct Student{
	int studentID;
	int grade;
};

struct Dataset{
	int numStudents;
	Student* students;
};

struct Rejects{
	int numRejects;
	int* rejects;
};

struct Mode{
	int numModes;
	int* modes;
};

struct Statistics{
	int   minimum;
	float average;
	int   maximum;
	float popStdDev;
	float smplStdDev;
	Mode  mode;
	int   histogram[10];
};

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
int readCSV(const char filename[],const int minAcceptableID, 
				const int maxAcceptableID,Dataset& data, 
				Rejects& rejects){
	//Your code here ...
	return -1;
}

int computeStatistics(Dataset& data, Statistics& stats){
	//Your code here ...
	return -1;
}

int writeCSV(const char filename[], const Statistics& stats){
	//Your code here ...
	return -1;
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

	std::cout << std::endl << "Implement some more appropriate tests in main()" << std::endl << std::endl;

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

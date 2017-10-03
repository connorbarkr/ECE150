#include <iostream>

using namespace std;

int main(const int argc, const char* const argv[])
{
    cout << "Welcome to UW Engineering, " << argv[1] << "." << endl;

    cout << "Your University of Waterloo E-mail address is: " << argv[2] << "@uwaterloo.ca" << endl;

    cout << "The value stored in argc is " << argc << "." << endl;
 
    cout << "The variable \"argc\" contains a count of the arguments passed to this program." << endl;

    return 0;
}

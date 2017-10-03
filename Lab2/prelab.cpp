#include <stdlib.h>
#include <iostream>
using namespace std;

int main(int argc, const char * argv[]) {
  int x = 1;
  int y = 0;

  while (x < 10)
    y += x++;

  cout << "y = " << y << endl;

  /*
  if (x >= y)
    cout << "x is bigger than y; ";
  if (x == y)
    cout << "x equals y; ";
  cout << "isn't that interesting?" << endl;
  */

  return 0;
}

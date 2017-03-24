
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int main(int argc, char *argv[])
{
  int num1 = atoi(argv[1]);
  int num2 = atoi(argv[2]);
  int numbits = atoi(argv[3]);

  for (int i = numbits - 1; i >= 0; i--)
  {
    if (num1 - pow(2, i) >= 0)
    {
      cout << "1";
      num1 -= pow(2, 1);
    }

    else
    {
      cout << "0";
    } 
  }

  cout << "\t";

  for (int i = numbits - 1; i >= 0; i--)
  {
    if (num2 - pow(2, i) >= 0)
    {
      cout << "1";
      num2 -= pow(2, i);
    }

    else
    {
      cout << "0";
    }
  }

  cout << "\t";
  
  return 0;
}

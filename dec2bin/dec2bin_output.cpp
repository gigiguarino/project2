
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int main(int argc, char *argv[])
{
  int num = atoi(argv[1]);
  int numbits = atoi(argv[2]);

  for (int i = numbits - 1; i >= 0; i--)
  {
    if (num - pow(2, i) >= 0)
    {
      cout << "1";
      num -= pow(2, 1);
    }

    else
    {
      cout << "0";
    } 
  }

  cout << "\n";


  return 0;
}

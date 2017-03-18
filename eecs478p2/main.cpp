#include <iostream>

using namespace std;

#include "circuit.h"

void usage(const char* exename);


int main(int argc, char **argv)
{
  // default values
  unsigned int numBits = 0;
  string outFilename = "";
  
  Circuit c;
  
  // parsing inputs
  if (argc < 2)
  {
    usage(argv[0]);
  }
  
  if (argv[1] == string("-h") || argv[1] == string("-help"))
  {
    usage(argv[0]);
  }
  for (int i = 1; i < argc; ++i)
  {
    if (argv[1] == string("-h") || argv[1] == string("-help"))
    {
      usage(argv[0]);
    }
    else if (argv[i] == string("-add"))
    {
      if (i+2 < argc)
      {
        numBits = static_cast<unsigned>(atoi(argv[++i]));
        outFilename = argv[++i];
        if (!c.createADDModule("a", "b", "cin", "s", "cout", numBits))
        {
          cout << "Adder module successfully created." << endl;
          c.setName("adder");
          c.setPIs("a", 0, numBits);
          c.setPIs("b", 0, numBits);
          c.setPI("cin");
          c.setPOs("s", 0, numBits);
          c.setPO("cout");
          //          c.print();   // optional
          c.writeBLIF(outFilename);
        }
        else cout << "Problem creating adder module." << endl;
      }
      else
      {
        cout << "option -add requires two arguments" << endl;
        usage(argv[0]);
      }
    }
    else if (argv[i] == string("-sub"))
    {
      if (i+2 < argc)
      {
        numBits = static_cast<unsigned>(atoi(argv[++i]));
        outFilename = argv[++i];
        if (!c.createSUBModule("a", "b", "s", numBits))
        {
          cout << "Subtractor module successfully created." << endl;
          c.setName("subtractor");
          c.setPIs("a", 0, numBits);
          c.setPIs("b", 0, numBits);
          c.setPOs("s", 0, numBits);
          //          c.print();   // optional
          c.writeBLIF(outFilename);
        }
        else cout << "Problem creating substractor module." << endl;
      }
      else
      {
        cout << "option -sub requires two arguments" << endl;
        usage(argv[0]);
      }
    }
    else if (argv[i] == string("-mult"))
    {
      if (i+2 < argc)
      {
        numBits = static_cast<unsigned>(atoi(argv[++i]));
        outFilename = argv[++i];
        if (!c.createMULTModule("a", "b", "s", numBits))
        {
          cout << "multiplier module successfully created." << endl;
          c.setName("multiplier");
          c.setPIs("a", 0, numBits);
          c.setPIs("b", 0, numBits);
          c.setPOs("s", 0, 2*numBits);
          //          c.print();   // optional
          c.writeBLIF(outFilename);
        }
        else cout << "Problem creating multiplier module." << endl;
      }
      else
      {
        cout << "option -mult requires two arguments" << endl;
        usage(argv[0]);
      }
    }
    else if (argv[i] == string("-shift"))
    {
      if (i+3 < argc)
      {
        numBits = static_cast<unsigned>(atoi(argv[++i]));
        unsigned int numShift = static_cast<unsigned>(atoi(argv[++i]));
        outFilename = argv[++i];
        if (!c.createSHIFTModule("orig", "out", numBits, numShift))
        {
          cout << "Shifter module successfully created." << endl;
          c.setName("shifter");
          c.setPIs("orig", 0, numBits);
          c.setPOs("out", 0, numBits+numShift);
//          c.print();   // optional
          c.writeBLIF(outFilename);
        }
        else cout << "Problem creating shifter module." << endl;
      }
      else
      {
        cout << "option -shift requires three arguments" << endl;
        usage(argv[0]);
      }
    }
    else if (argv[i] == string("-absmin9x12y"))
    {
      if (i+1 < argc)
      {
        outFilename = argv[++i];
        if (!c.createABSMIN9X12YModule("x", "y", "z"))
        {
          cout << "abs(min(9x, 12y)) module successfully created." << endl;
          // your code here
        }
        else cout << "Problem creating abs(min(9x, 12y)) module." << endl;
      }
      else
      {
        cout << "option -absmin9x12y requires one argument" << endl;
        usage(argv[0]);
      }
    }
      else
    {
      cout << "unrecognized command" << argv[i] << endl;
      usage(argv[0]);
    }
  }
  
  return 0;
}

void usage(const char* exename)
{
  cout << "Usage: " << exename << " [options]" << endl;
  cout << endl;
  cout << "Available Options: " << endl;
  cout << "-h or -help                           Print this message and exit" << endl;
  cout << "-add <uint> <outFilename>             Save <uint>-bit adder module in BLIF format to <outFilename>" << endl;
  cout << "-sub <uint> <outFilename>             Save <uint>-bit subtractor module in BLIF format to <outFilename>" << endl;
  cout << "-mult <uint> <outFilename>             Save <uint>-bit multiplier module in BLIF format to <outFilename>" << endl;
  cout << "-shift <uint1> <uint2> <outFilename>  Save <uint1>-bit number shifted by <uint2> bits in BLIF format to <outFilename>" << endl;
  cout << "-absmin9x12y <outFilename>                    Save abs(min(9x, 12y)) module in BLIF format to <outFilename>" << endl;
  cout << endl;
  cout << "Example: " << exename << " -add 32 adder32.blif should create a 32-bit adder module in adder32.blif." << endl;
  cout << endl;
  
  exit(0);
}


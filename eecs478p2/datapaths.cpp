#include "circuit.h"



int Circuit::createABSMIN9X12YModule(const string &input1, const string &input2, const string &output)
{
  // 3 select bit mux that selects according to this:
  // 000 -> 9x --> both are positive, 12y is larger
  // 001 -> 12y --> both are positive, 9x is larger
  // 010 -> 12y --> only y is negative, 12y is larger
  // 011 -> 12y --> only y is negative, 9x is larger
  // 100 -> 12y --> both are negative, 12y is larger
  // 101 -> 9x --> both are negative, 9x is larger
  // 110 -> 9x --> only x is negative, 12y is larger
  // 111 -> 9x --> only x is negative, 9x is larger
    
    
  Node* node;
  string name;
  
  // create input1 nodes
  for (unsigned int i = 0; i < 16; ++i)
  {
    stringstream sstr;
    sstr << i;
    name = input1 + "[" + sstr.str() + "]";
    
    node = createNode(name);
  }
  
  // create input2 nodes
  for (unsigned int i = 0; i < 16; ++i)
  {
    stringstream sstr;
    sstr << i;
    name = input2 + "[" + sstr.str() + "]";
    
    node = createNode(name);
  }
  
  // create output nodes
  for (unsigned int i = 0; i < 20; ++i)
  {
    stringstream sstr;
    sstr << i;
    name = output + "[" + sstr.str() + "]";
    
    node = createNode(name);
  }
  
  Node* zeroNode = createNode("ZERO");
  createZERONode(zeroNode);
  
  Node* oneNode = createNode("ONE");
  createONENode(oneNode);
  
  // create number nine
  // make it 16 bits
  for (unsigned int i = 0; i < 16; ++i)
  {
    stringstream sstr;
    sstr << i;
    name = "nine[" + sstr.str() + "]";
    
    node = createNode(name);
    
    if (i == 0 || i == 3)
    {
      createBUF1Node(oneNode, node);
    }
    
    else
    {
      createBUF1Node(zeroNode, node);
    }
    
  }
  
  // create number 12
  // make it 16 bits
  for (unsigned int i = 0; i < 16; ++i)
  {
    stringstream sstr;
    sstr << i;
    name = "twelve[" + sstr.str() + "]";
    
    node = createNode(name);
    
    if (i == 3 || i == 2)
    {
      createBUF1Node(oneNode, node);
    }
    
    else
    {
      createBUF1Node(zeroNode, node);
    }
  }
  
  // get first bit of x
  stringstream sstr1;
  sstr1 << 15;
  name = input1 + "[" + sstr1.str() + "]";
  Node* first_bit_x = findNode(name);
  assert(first_bit_x != NULL);

  // select 1 is first bit of x
  Node* select1 = findNode(name);
  assert(select1 != NULL);

  // get first bit of y
  stringstream sstr2;
  sstr2 << 15;
  name = input2 + "[" + sstr2.str() + "]";
  Node* first_bit_y = findNode(name);
  assert(first_bit_y != NULL);

  // select 2 is first bit of x XOR first bit of y
  Node* select2 = createNode("sel2");
  createXOR2Node(first_bit_x, first_bit_y, select2);

  Node* node1;
  Node* node2;

  // take absolute values of both inputs
  // need to do this for multiplication
  // muliplier takes in unsigned values
  createABSModule(input1, "one", 16);
  createABSModule(input2, "two", 16);

  
  // 9 * abs(x)
  createMULTModule("one", "nine", "f9x", 16);
  //12 * abs(y)
  createMULTModule("two", "twelve", "f12y", 16);

  // subtract 9x from 12y to see who is larger
  createSUBModule("f12y", "f9x", "diff", 32);
  
  // if the diff is negative
  // then 9x > 12y is true
  // 9x > 12y can be represented by the first bit of diff
  
  // select three is 9x > 12y 
  Node* select3 = findNode("diff[31]");
  assert(select3 != NULL);

  Node* out;
  for (unsigned int i = 0; i < 20; ++i)
  {
    // node1 = 9x[]
    // node2 = 12y[]
    // out = output node

    stringstream sstr;
    sstr << i;

    name = "f9x[" + sstr.str() + "]";
    node1 = findNode(name);
    assert(node1 != NULL);

    name = "f12y[" + sstr.str() + "]";
    node2 = findNode(name);
    assert(node2 != NULL);

    name = output + "[" + sstr.str() + "]";
    out = findNode(name);
    assert(out != NULL);
    
    // use select bits to select correct output
    createMUX8Node(select1, select2, select3, 
                   node1, node2, node2, node2, 
                   node2, node1, node1, node1, out);
  }
 
  return 0;
}


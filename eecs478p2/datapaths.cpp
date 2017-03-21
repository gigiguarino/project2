#include "circuit.h"


// input is two's complement
// multiply takes in one's complement numbers
// maybe have a conditional at the beginning to account for whether they're negative or not?

// test 2 and 4 not passing
// test 9 and 11 not passing
// select bits 000, 110
// 000 -- x is pos, y is pos, 9x < 12y
// 110 -- x is neg, y is pos, 9x < 12y

int Circuit::createABSMIN9X12YModule(const string &input1, const string &input2, const string &output)
{
  // 3 select bit mux that selects according to this:
  // 000 -> 9x
  // 001 -> 12y
  // 010 -> 12y
  // 011 -> 12y
  // 100 -> 12y
  // 101 -> 9x
  // 110 -> 9x
  // 111 -> 9x
  // first select bit is x[numBits-1]
  // second select bit is xor2(x[numBits-1], y[numBits-1])
  // third select bit is 9x > 12y?
    
    
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
  
  // 9 times x
  // 12 times y
  
  Node* zeroNode = createNode("ZERO");
  createZERONode(zeroNode);
  
  Node* oneNode = createNode("ONE");
  createONENode(oneNode);
  
  // create number nine
  // make it twenty bits
  for (unsigned int i = 0; i < 20; ++i)
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
  // make it 20 bits
  for (unsigned int i = 0; i < 20; ++i)
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
  
  stringstream sstr1;
  sstr1 << 15;
  name = input1 + "[" + sstr1.str() + "]";
  Node* first_bit_x = findNode(name);
  assert(first_bit_x != NULL);

  Node* select1 = findNode(name);
  assert(select1 != NULL);
  
  stringstream sstr2;
  sstr2 << 15;
  name = input2 + "[" + sstr2.str() + "]";
  Node* first_bit_y = findNode(name);
  assert(first_bit_y != NULL);


  Node* select2 = createNode("sel2");
  createXOR2Node(first_bit_x, first_bit_y, select2);

  Node* node1;
  Node* node2;

  // create absolute values of inputs
  // make them both 20 bits
  for (unsigned int i = 0; i < 20; ++i)
  {
    stringstream sstr;
    sstr << i;
    
    if (i < 16)
    {
      // create new abs nodes for input1
      name = input1 + "_abs[" + sstr.str() + "]";
      node2 = createNode(name);
    }

    else
    {
      // two's complement carries over
      node1 = first_bit_x;
      
      // create new abs nodes for input1
      name = input1 + "_abs[" + sstr.str() + "]";
      node2 = createNode(name);
      createBUF1Node(node1, node2);
      
      // fill in the rest of input1 so it's 20 bits   
      name = input1 + "[" + sstr.str() + "]";
      node2 = createNode(name);
      createBUF1Node(node1, node2);
    }
  }
  
  createABSModule(input1, input1 + "_abs", 20);
  
  for (unsigned int i = 0; i < 20; ++i)
  {
    stringstream sstr;
    sstr << i;
    
    if (i < 16)
    {
      // create new abs nodes for input2
	    name = input2 + "_abs[" + sstr.str() + "]";
      node2 = createNode(name);
    }
  
    else
    {
      // two's complement carries over
      node1 = first_bit_y;
   
      // new abs nodes for input2   
      name = input2 + "_abs[" + sstr.str() + "]";
      node2 = createNode(name);
      createBUF1Node(node1, node2);
      
      // new input2 nodes to fill 20 bits
      name = input2 + "[" + sstr.str() + "]";
      node2 = createNode(name);
      createBUF1Node(node1, node2);
    }  
  }
  
  createABSModule(input2, input2 + "_abs", 20);
  
  // 9x
  createMULTModule(input1 + "_abs", "nine", "f9x", 20);
  //12y
  createMULTModule(input2 + "_abs", "twelve", "f12y", 20);
  createSUBModule("f12y", "f9x", "diff", 20);
  
  // if the diff is negative
  // then 9x > 12y is true
  // 9x > 12y can be represented by the first bit of diff
  

  Node* select3 = findNode("diff[19]");
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

    createMUX8Node(select1, select2, select3, node1, node2, node2, node2, node2, node1, node1, node1, out);
  }
  
  
  return 0;
}


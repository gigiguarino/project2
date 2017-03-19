#include "circuit.h"

int Circuit::createABSMIN9X12YModule(const string &input1, const string &input2, const string &output)
{
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
  
  Node* node1;
  Node* node2;
  
  Node* zeroNode = createNode("ZERO");
  createZERONode(zeroNode);
  
  Node* oneNode = createNode("ONE");
  createONENode(oneNode);
  
  // create number nine
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
  
  createMULTModule(input1, "nine", "f9x", 16);
  createMULTModule(input2, "twelve", "f12y", 20);
  
  for (unsigned int i = 16; i < 20; ++i)
  {
    stringstream sstr;
    sstr << i;
    name = "f9x[" + sstr.str() + "]";
    node = createNode(name);
    createBUF1Node(zeroNode, node);
  }
  
  createSUBModule("f12y", "f9x", "diff", 20);
  
  // if the diff is negative
  // then f12y is bigger
  
  // do a mux
  // if the first bit is 0, choose f12y
  // if the first bit is 1, choose f9x
  
  node = findNode("diff[19]");
  assert(node != NULL);
  
  Node* node3;
  
  for (unsigned int i = 0; i < 20; ++i)
  {
    stringstream sstr;
    sstr << i;
    
    name = "f9x[" + sstr.str() + "]";
    node1 = findNode(name);
    assert(node != NULL);
    
    name = "f12y[" + sstr.str() + "]";
    node2 = findNode(name);
    assert(node != NULL);
    
    name = "f[" + sstr.str() + "]";
    node3 = createNode(name);
    
    createMUX2Node(node, node2, node1, node3);
  }
  
  createABSModule("f", output, 20);
  
  return 0;
}


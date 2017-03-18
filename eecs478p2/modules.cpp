#include "circuit.h"


int Circuit::createADDModule(const string &input1, const string &input2, const string &cin, const string &output, const string &cout1, unsigned int numBits)
{
  Node* node;
  
  // create input1 nodes
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    string name = input1 + "[" + sstr.str() + "]";
    
    node = createNode(name);
  }
  
  // create input2 nodes
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    string name = input2 + "[" + sstr.str() + "]";
    
    node = createNode(name);
  }
  
  // create cin node
  node = createNode(cin);
  
  // create output nodes
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    string name = output + "[" + sstr.str() + "]";
    
    node = createNode(name);
  }
  
  // create cout node
  node = createNode(cout1);
  
  
  
  // truth table
  // in1[] in2[] cin[] cout[] out[]
  //  0 0 0   0 0
  //  0 0 1   0 1
  //  0 1 0   0 1
  //  0 1 1   1 0
  //  1 0 0   0 1
  //  1 0 1   1 0
  //  1 1 0   1 0
  //  1 1 1   1 1
  
  // out --> (xor3(x,y,z) or (and(x,y) and and(y,z)) = d or (e and f) = d or g
  // cout --> (x or y) and (x or z) and (y or z) = h and i and j = h and k
  
  Node* x;
  Node* y;
  Node* z;
  
  Node* out;
  
  Node* f1 = createNode("f1");
  Node* f2 = createNode("f2");
  Node* f3 = createNode("f3");
  Node* f4 = createNode("f4");
  Node* f5 = createNode("f5");
  Node* f6 = createNode("f6");
  Node* f7 = createNode("f7");
  Node* f8 = createNode("f8");
  
  Node* cout_node = findNode(cout1);
  
  x = findNode(cin);
  assert(x != NULL);

  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    string name;
    
    sstr << i;
    name = input1 + "[" + sstr.str() + "]";
    y = findNode(name);
    assert(y != NULL);
    
    name = input2 + "[" + sstr.str() + "]";
    z = findNode(name);
    assert(z != NULL);
    
    name = output + "[" + sstr.str() + "]";
    out = findNode(name);
    assert(out != NULL);
  
    createXOR3Node(x,y,z,f1);
    createAND2Node(x,y,f2);
    createAND2Node(y,z,f3);
    createAND2Node(f2,f3,f4);
    createOR2Node(f1,f4,out);
    
    createOR2Node(x,y,f5);
    createOR2Node(y,z,f6);
    createOR2Node(x,z,f7);
    createAND2Node(f5,f6,f8);
    
    if (i != numBits-1)
    {
      createAND2Node(f8,f7,x);
    }
    else
    {
      createAND2Node(f8,f7,cout_node);
    }
  }

  return 0;
}

int Circuit::createSUBModule(const string &input1, const string &input2, const string &output, unsigned int numBits)
{
  
  Node* node;
 
  // create input1 nodes
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    string name = input1 + "[" + sstr.str() + "]";
    
    node = createNode(name);
  }
  
  // create input2 nodes
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    string name = input2 + "[" + sstr.str() + "]";
    
    node = createNode(name);
  }
  
  // create output nodes
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    string name = output + "[" + sstr.str() + "]";
    
    node = createNode(name);
  }
  
  // create an adder module that adds the inverse version of input2 and input1 and 1
  
  Node* node1;
  Node* node2;
  
  Node* oneNode = createNode("ONE");
  createONENode(oneNode);
  
  Node* zeroNode = createNode("ZERO");
  createZERONode(zeroNode);
  
  // create inverse input2 nodes and call it input3
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    string name = input2 + "[" + sstr.str() + "]";
    node1 = findNode(name);
    assert(node1 != NULL);
    
    name = "f1[" + sstr.str() + "]";
    node2 = createNode(name);
    
    createINVNode(node1,node2);
  }
  
  createADDModule("f1", input1, "ONE", "f2", "f3", numBits);
  
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    string name = "f2[" + sstr.str() + "]";
    node1 = findNode(name);
    assert(node1 != NULL);
    
    name = "f4[" + sstr.str() + "]";
    node2 = createNode(name);
    
    
    createINVNode(node1,node2);
  }
  
  createADDModule("f4", "ONE", "ZERO", output, "f3", numBits);
  
  return 0;
}


// i made this function
// takes the absolute value of a two's complement number
int Circuit::createABSModule(const string &input, const string &output, unsigned int numBits)
{
  Node* node;
  Node* node1;
  Node* node2;
  
  string name;
  
  // get input nodes
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    name = input + "[" + sstr.str() + "]";
    node = createNode(name);
  }
  
  // get output nodes
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    name = output + "[" + sstr.str() + "]";
    node = createNode(name);
  }
  
  // take first bit
  // xor it with all bits in number
  // add the first bit to it
  
  stringstream sstr;
  sstr << numBits - 1;
  name = input + "[" + sstr.str() + "]";
  node2 = findNode(name);
  assert(node2 != NULL);
  
  Node* zeroNode = createNode("ZERO");
  createZERONode(zeroNode);
  
  for (unsigned int i = 0; i < numBits-1; ++i)
  {
    stringstream sstr;
    sstr << i;
    name = "f1[" + sstr.str() + "]";
    node1 = createNode(name);
    
    sstr << i;
    string name = input + "[" + sstr.str() + "]";
    node = findNode(name);
    assert(node != NULL);
    
    createXOR2Node(node, node2, node1);
  }
  
  sstr << 0;
  name = "f2[" + sstr.str() + "]";
  node = createNode(name);
  
  for (unsigned int i = 1; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    name = "f2[" + sstr.str() + "]";
    node = createNode(name);
    createZERONode(node);
  }
  
  createADDModule("f1", "f2", "ZERO", "output", "cout", numBits);
  
  return 0;
}

int Circuit::createMULTModule(const string &input1, const string &input2, const string &output, unsigned int numBits)
{
  Node* node;
  
  // create input1 nodes
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    string name = input1 + "[" + sstr.str() + "]";
    node = createNode(name);
  }
  
  // create input2 nodes
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    string name = input2 + "[" + sstr.str() + "]";
    node = createNode(name);
  }
  
  // create output nodes
  for (unsigned int i = 0; i < numBits*2; ++i)
  {
    stringstream sstr;
    sstr << i;
    string name = output + "[" + sstr.str() + "]";
    node = createNode(name);
  }
  
  Node* shifted = createNode("shifted");
  Node* add = createNode("add");
  Node* zeroNode = createNode("ZERO");
  createZERONode(zeroNode);
  
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    string name = input1 + "[" + sstr.str() + "]";
    node = findNode(name);
    
    createSHIFTModule(input1, "shifted", numBits, i);
    shifted = findNode("shifted");
    
    createMUX2Node(node, zeroNode, shifted, add);
    createADDModule(output, "add", "ZERO", output, "f1", numBits);
  }
  
  return 0;
}

int Circuit::createSHIFTModule(const string &input, const string &output, unsigned int numBits, unsigned int numShift)
{
  Node* node;
  // create input nodes
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    string name = input + "[" + sstr.str() + "]";
    
    node = createNode(name);
  }
  
  // create output nodes
  for (unsigned int i = 0; i < numBits+numShift; ++i)
  {
    stringstream sstr;
    sstr << i;
    string name = output + "[" + sstr.str() + "]";
    
    node = createNode(name);
  }
  
  // assign '0's to the least numShift bits
  Node* zeroNode = createNode("ZERO");
  createZERONode(zeroNode);
  
  for (unsigned int i = 0; i < numShift; ++i)
  {
    stringstream sstr;
    sstr << i;
    string name = output + "[" + sstr.str() + "]";
    
    Node* outNode = findNode(name);
    assert(outNode != NULL);
    
    createBUF1Node(zeroNode, outNode);
  }
  
  // assign inputs to the remaining numBits bits
  for (unsigned int i = numShift; i < numBits+numShift; ++i)
  {
    string name;
    
    // find input node[i-numShift]
    stringstream inStr;
    inStr << i-numShift;
    name = input + "[" + inStr.str() + "]";
    Node* inNode = findNode(name);
    assert(inNode != NULL);
    
    // find output node[i]
    stringstream outStr;
    outStr << i;
    name = output + "[" + outStr.str() + "]";
    Node* outNode = findNode(name);
    assert(outNode != NULL);
    
    // assign
    createBUF1Node(inNode, outNode);
  }
  
  return 0;
}


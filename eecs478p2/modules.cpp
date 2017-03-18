#include "circuit.h"


int Circuit::createADDModule(const string &input1, const string &input2, const string &cin, const string &output, const string &cout1, unsigned int numBits)
{
  Node* node;
  string name;
  
  // create input1 nodes
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    name = input1 + "[" + sstr.str() + "]";
    node = createNode(name);
  }
  
  // create input2 nodes
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    name = input2 + "[" + sstr.str() + "]";
    node = createNode(name);
  }
  
  // create cin node
  node = createNode(cin);
  
  // create output nodes
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    name = output + "[" + sstr.str() + "]";
    node = createNode(name);
  }
  
  // create cout node
  node = createNode(cout1);
 
  // nodes we have
  // input1[]
  // input2[]
  // output[]
  // cin
  // cout
  
  // create internal cout nodes
  for (unsigned int i = 0; i < numBits; ++i)
  {
      stringstream sstr;
      sstr << i;
      name = "cout_i[" + sstr.str() + "]";
      node = createNode(name);
  } 
  
  // create internal f1, f2, and f3 nodes
  for (unsigned int i = 0; i < numBits; ++i)
  {
      stringstream sstr;
      sstr << i;
      name = "f1[" + sstr.str() + "]";
      node = createNode(name);
      name = "f2[" + sstr.str() + "]";
      node = createNode(name);
      name = "f3[" + sstr.str() + "]";
      node = createNode(name);
  }
  
  Node* a; // input1
  Node* b; // input2
  Node* c; // cin
  Node* d; // f1
  Node* e; // f2
  Node* f; // f3
  Node* g; // out
  Node* h; // cout

  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;

    stringstream sstr1;
    sstr1 << i-1;

    name = input1 + "[" + sstr.str() + "]";
    a = findNode(name);
    assert(a != NULL);

    name = input2 + "[" + sstr.str() + "]";
    b = findNode(name);
    assert(b != NULL);

    if (i == 0)
    {
      c = findNode(cin);
      assert(c != NULL);
    }

    else
    {
      name = "cout_i[" + sstr1.str() + "]";
      c = findNode(name);
      assert(c != NULL);
    }

    name = "f1[" + sstr.str() + "]";
    d = findNode(name);
    assert(d != NULL);

    name = "f2[" + sstr.str() + "]";
    e = findNode(name);
    assert(e != NULL);
    
    name = "f3[" + sstr.str() + "]";
    f = findNode(name);
    assert(f != NULL);

    name = output + "[" + sstr.str() + "]";
    g = findNode(name);
    assert(g != NULL);

    name = "cout_i[" + sstr.str() + "]";
    h = findNode(name);
    assert(h != NULL);
      
    // d = a xor b
    // e = a and b
    // f = d and c
    // g = d xor c
    // h = f xor e  
      
    createXOR2Node(a, b, d, numBits);
    createAND2Node(a, b, e, numBits);
    createAND2Node(d, c, f, numBits);
    createXOR2Node(d, c, g, numBits);
    createXOR2Node(f, e, h, numBits);
  }

  // create a buffer from the latest h
  // to cout
  
  node = findNode(cout);
  assert(node != NULL);

  createBUF1Node(h, node);
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


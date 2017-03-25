#include "circuit.h"


int Circuit::createADDModule(const string &input1, const string &input2, const string &cin, const string &output, const string &cout, unsigned int numBits)
{
  Node* node;
  string name;
  
  // create input1 nodes
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    name = input1 + "[" + sstr.str() + "]";
    node = findNode(name);
    if (node == NULL)
    {
      node = createNode(name);
    }
  }
  
  // create input2 nodes
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    name = input2 + "[" + sstr.str() + "]";
    node = findNode(name);
    if (node == NULL)
    {
      node = createNode(name);
    }
  }
  
  // create cin node
  node = createNode(cin);
  
  // create output nodes
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    name = output + "[" + sstr.str() + "]";
    node = findNode(name);
    if (node == NULL)
    {
      node = createNode(name);
    }
  }
  
  // create cout node
  node = createNode(cout);
 
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
      name = output + "_h[" + sstr.str() + "]";
      node = createNode(name);
  } 
  
  // create internal f1, f2, and f3 nodes
  for (unsigned int i = 0; i < numBits; ++i)
  {
      stringstream sstr;
      sstr << i;
      name = output + "_d[" + sstr.str() + "]";
      node = createNode(name);
      name = output + "_e[" + sstr.str() + "]";
      node = createNode(name);
      name = output + "_f[" + sstr.str() + "]";
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
      name = output + "_h[" + sstr1.str() + "]";
      c = findNode(name);
      assert(c != NULL);
    }

    name = output + "_d[" + sstr.str() + "]";
    d = findNode(name);
    assert(d != NULL);

    name = output + "_e[" + sstr.str() + "]";
    e = findNode(name);
    assert(e != NULL);
    
    name = output + "_f[" + sstr.str() + "]";
    f = findNode(name);
    assert(f != NULL);

    name = output + "[" + sstr.str() + "]";
    g = findNode(name);
    assert(g != NULL);

    name = output + "_h[" + sstr.str() + "]";
    h = findNode(name);
    assert(h != NULL);
      
    // d = a xor b
    // e = a and b
    // f = d and c
    // g = d xor c
    // h = f or e  
      
    createXOR2Node(a, b, d);
    createAND2Node(a, b, e);
    createAND2Node(d, c, f);
    createXOR2Node(d, c, g);
    createOR2Node(f, e, h);

    if (i == numBits-1)
    {
      // create a buffer from the latest h
      // to cout
        
      node = findNode(cout);
      assert(node != NULL);
      createBUF1Node(h, node);
    }
  }

  return 0;
}

int Circuit::createSUBModule(const string &input1, const string &input2, const string &output, unsigned int numBits)
{
  Node* node;
  string name;
 
  // create input1 nodes
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    name = input1 + "[" + sstr.str() + "]";
    node = findNode(name);
    if (node == NULL)
    {
      node = createNode(name);
    }
  }
  
  // create input2 nodes
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    name = input2 + "[" + sstr.str() + "]";
    node = findNode(name);
    if (node == NULL)
    {
      node = createNode(name);
    }
  }
  
  // create output nodes
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    name = output + "[" + sstr.str() + "]";
    node = findNode(name);
    if (node == NULL)
    {
      node = createNode(name);
    }
  }
  
  
  Node* node1;
  Node* node2;
  
  Node* oneNode = createNode("ONE");
  createONENode(oneNode);
  
  // create inverse of input2
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;

    name = input2 + "[" + sstr.str() + "]";
    node1 = findNode(name);
    assert(node != NULL);

    name = input2 + "_inv[" + sstr.str() + "]";
    node2 = createNode(name);
    
    createINVNode(node1, node2);
  }

  // add inverse of input2, and 1, to input1
  // this adds the two's complement of input2 to input1
  createADDModule(input1, input2 + "_inv", "ONE", output, "dc", numBits);

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
    node = findNode(name);
    if (node == NULL)
    {
      node = createNode(name);
    }
  }
  
  // get output nodes
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    name = output + "[" + sstr.str() + "]";
    node = findNode(name);
    if (node == NULL)
    {
      node = createNode(name);
    }
  }
  
  // take first bit
  // xor it with all bits in number
  // add the first bit to it
  
  stringstream sstr;
  sstr << numBits - 1;

  // first bit
  name = input + "[" + sstr.str() + "]";
  node2 = findNode(name);
  assert(node2 != NULL);
  
  Node* zeroNode = createNode("ZERO");
  createZERONode(zeroNode);
  
  for (unsigned int i = 0; i < numBits-1; ++i)
  {
    stringstream sstr;
    sstr << i;

    name = output + "_f1[" + sstr.str() + "]";
    node1 = createNode(name);
    
    name = input + "[" + sstr.str() + "]";
    node = findNode(name);
    assert(node != NULL);
    
    createXOR2Node(node, node2, node1);
  }
  
  // create number to add to the xored number
  // first bit of input gets added
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    
    name = output + "_f2[" + sstr.str() + "]";
    node = createNode(name);
    
    if (i == 0)
    {
      createBUF1Node(node2, node);
    }
    
    else
    {
      createZERONode(node);
    }
  }
  
  // add xored number with first bit to create output
  createADDModule(output + "_f1", output + "_f2", "ZERO", output, "dc", numBits);
  
  return 0;
}

int Circuit::createMULTModule(const string &input1, const string &input2, const string &output, unsigned int numBits)
{
  Node* node;
  string name;
  
  // create input1 nodes
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    name = input1 + "[" + sstr.str() + "]";
    node = findNode(name);
    if (node == NULL)
    {
      node = createNode(name);
    }
  }
  
  // create input2 nodes
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    name = input2 + "[" + sstr.str() + "]";
    node = findNode(name);
    if (node == NULL)
    {
      node = createNode(name);
    }
  }
  
  // create output nodes
  for (unsigned int i = 0; i < numBits*2; ++i)
  {
    stringstream sstr;
    sstr << i;
    name = output + "[" + sstr.str() + "]";
    node = findNode(name);
    if (node == NULL)
    {
      node = createNode(name);
    }
  }
  
  Node* node1;
  Node* node2;
  Node* zeroNode = createNode("ZERO");
  createZERONode(zeroNode);
  
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr1;
    sstr1 << i;
    
    // create in_sum nodes
    // in_sum will be added to every iteration
    if (i == 0)
    {
      for (unsigned int j = 0; j < numBits*2; ++j)
      {
        stringstream sstr2;
        sstr2 << j;
        
        name = output + "_in_sum" + sstr1.str() + "[" + sstr2.str() + "]";
        node = createNode(name);
      }
    }
    
    // take bit of second input
    name = input2 + "[" + sstr1.str() + "]";
    node1 = findNode(name);
    assert(node1 != NULL);
    
    for (unsigned int j = 0; j < numBits; ++j)
    {
      stringstream sstr2;
      sstr2 << j;
      
      name = input1 + "[" + sstr2.str() + "]";
      node2 = findNode(name);
      assert(node2 != NULL);
      
      name = output + "_pp" + sstr1.str() + "[" + sstr2.str() + "]";
      node = createNode(name);
      
      // AND second input's bit with each of first inputs bits
      // this creates our partial product
      createAND2Node(node1, node2, node);
    }
    
    // shift the partial product the desired amount
    createSHIFTModule(output + "_pp" + sstr1.str(), 
                      output + "_pps" + sstr1.str(), numBits, i);
    
    // fill remaining parts of shifted nodes
    // with zeros
    for (unsigned int j = numBits+i; j < numBits*2; ++j)
    {
      stringstream sstr2;
      sstr2 << j;
      
      name = output + "_pps" + sstr1.str() + "[" + sstr2.str() + "]";
      node = createNode(name);
      createZERONode(node);
    }
    
    // add partial product to sum
    createADDModule(output + "_pps" + sstr1.str(), 
                    output + "_in_sum" + sstr1.str(), "ZERO", 
                    output + "_out_sum" + sstr1.str(), "dc" + sstr1.str(), 
                    numBits*2);
    
    // create buffers from out_sum to in_sum
    for (unsigned int j = 0; j < numBits*2; ++j)
    {
      stringstream sstr2;
      sstr2 << j;
      
      stringstream sstr3;
      sstr3 << i + 1;
      
      name = output + "_out_sum" + sstr1.str() + "[" + sstr2.str() + "]";
      node1 = findNode(name);
      assert(node1 != NULL);
      
      name = output + "_in_sum" + sstr3.str() + "[" + sstr2.str() + "]";
      node2 = createNode(name);
      
      createBUF1Node(node1, node2);
    }
  }
  
  // create buffer from out_sum[numBits-1] to output
  for (unsigned int i = 0; i < numBits*2; ++i)
  {
    stringstream sstr;
    sstr << i;
    
    stringstream sstr1;
    sstr1 << numBits-1;
    
    name = output + "_out_sum" + sstr1.str() + "[" + sstr.str() + "]";
    node = findNode(name);
    assert(node != NULL);
    
    name = output + "[" + sstr.str() + "]";
    node1 = findNode(name);
    assert(node != NULL);
    
    createBUF1Node(node, node1);
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
    node = findNode(name);
    if (node == NULL)
    {
      node = createNode(name);
    }
  }
  
  // create output nodes
  for (unsigned int i = 0; i < numBits+numShift; ++i)
  {
    stringstream sstr;
    sstr << i;
    string name = output + "[" + sstr.str() + "]";
    node = findNode(name);
    if (node == NULL)
    {
      node = createNode(name);
    }
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


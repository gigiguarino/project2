#include "circuit.h"

// creates a constant '1' node
int Circuit::createONENode(Node* node)
{
  assert(node != NULL);
  
  node->clearTT();
  node->clearFanin();
  
  node->type = ONE_NODE;
  return 0;
}

// creates a constant '0' node
int Circuit::createZERONode(Node* node)
{
  assert(node != NULL);
  
  node->clearTT();
  node->clearFanin();
  
  node->type = ZERO_NODE;  
  return 0;
}

// creates a 1-input BUFFER node
int Circuit::createBUF1Node(Node* input, Node* output)
{
  assert(input != NULL);
  assert(output != NULL);
  
  output->clearTT();
  output->clearFanin();
  
  output->addFanin(input);
  output->tt.setNumVars(1);
  
  output->tt.addEntry("1");
  return 0;
}

// i created this function
// takes the inverse of the input
int Circuit::createINVNode(Node* input, Node* output)
{
  assert(input != NULL);
  assert(output != NULL);
  
  output->clearTT();
  output->clearFanin();
  
  output->addFanin(input);
  output->tt.setNumVars(1);
  
  output->tt.addEntry("0");
  return 0;
}

// creates a 2-input OR node
int Circuit::createOR2Node(Node* input1, Node* input2, Node* output)
{
  assert(input1 != NULL);
  assert(input2 != NULL);
  assert(output != NULL);
  
  output->clearTT();
  output->clearFanin();
  
  output->addFanin(input1);
  output->addFanin(input2);
  output->tt.setNumVars(2);
  
  output->tt.addEntry("-1");
  output->tt.addEntry("1-");
  return 0;
}

// creates a 2-input AND node
int Circuit::createAND2Node(Node* input1, Node* input2, Node* output)
{
  assert(input1 != NULL);
  assert(input2 != NULL);
  assert(output != NULL);
  
  output->clearTT();
  output->clearFanin();
  
  output->addFanin(input1);
  output->addFanin(input2);
  output->tt.setNumVars(2);
  
  output->tt.addEntry("11");
  return 0;
}

// xor2
// i made this function
int Circuit::createXOR2Node(Node* input1, Node* input2, Node* output)
{
  assert(input1 != NULL);
  assert(input2 != NULL);
  assert(output != NULL);
  
  output->clearTT();
  output->clearFanin();
  
  output->addFanin(input1);
  output->addFanin(input2);
  output->tt.setNumVars(2);
  
  output->tt.addEntry("10");
  output->tt.addEntry("01");
  return 0;
}

// creates a 3-input XOR node
int Circuit::createXOR3Node(Node* input1, Node* input2, Node* input3, Node* output)
{
  assert(input1 != NULL);
  assert(input2 != NULL);
  assert(input3 != NULL);
  assert(output != NULL);
  
  output->clearTT();
  output->clearFanin();
  
  output->addFanin(input1);
  output->addFanin(input2);
  output->addFanin(input3);
  output->tt.setNumVars(3);
  
  output->tt.addEntry("100");
  output->tt.addEntry("010");
  output->tt.addEntry("001");
  return 0;
}

// i made this function
// mux2
int Circuit::createMUX2Node(Node* select1, Node* input1, Node* input2, Node* output)
{
  assert(select1 != NULL);
  assert(input1 != NULL);
  assert(input2 != NULL);
  assert(output != NULL);
  
  
  // two input mux
  // one select bit
  // 0 selects input1
  // 1 selects input2
 
  output->clearTT();
  output->clearFanin();
  
  output->tt.setNumVars(3);
  
  output->addFanin(select1);
  output->addFanin(input2);
  output->addFanin(input1);
  
  output->tt.addEntry("0-1");
  output->tt.addEntry("11-");
  return 0;
}

// creates a 4-input MUX node (with two select bits)
// ordering from msb to lsb is:
// select2 select1
// input4 input3 input2 input1
int Circuit::createMUX4Node(Node* select1, Node* select2,
                            Node* input1, Node* input2, Node* input3, Node* input4, Node* output)
{
  assert(select1 != NULL);
  assert(select2 != NULL);
  assert(input1 != NULL);
  assert(input2 != NULL);
  assert(input3 != NULL);
  assert(input4 != NULL);
  assert(output != NULL);
 
  // four input mux
  // two select bits
  // 00 selects input1
  // 01 selects input2
  // 10 selects input3
  // 11 selects input4
  
  output->clearTT();
  output->clearFanin();
  
  output->tt.setNumVars(6);
  
  output->addFanin(select2);
  output->addFanin(select1);
  output->addFanin(input4);
  output->addFanin(input3);
  output->addFanin(input2);
  output->addFanin(input1);
  
  output->tt.addEntry("00---1");
  output->tt.addEntry("01--1-");
  output->tt.addEntry("10-1--");
  output->tt.addEntry("111---");
  return 0;
}


// creates a 8-input MUX node
// with 3 select bits
// i created this to help with my datapath module
int Circuit::createMUX8Node(Node* select1, Node* select2, Node* select3, 
                            Node* input1, Node* input2, Node* input3, Node* input4,
                            Node* input5, Node* input6, Node* input7, Node* input8,
                            Node* output)
{
  assert(select1 != NULL);
  assert(select2 != NULL);
  assert(select3 != NULL);
  assert(input1 != NULL);
  assert(input2 != NULL);
  assert(input3 != NULL);
  assert(input4 != NULL);
  assert(input5 != NULL);
  assert(input6 != NULL);
  assert(input7 != NULL);
  assert(input8 != NULL);
  assert(output != NULL);

  // eight input mux
  // three select bits
  // 000 selects input1
  // 001 selects input2
  // 010 selects input3
  // 011 selects input4
  // 100 selects input5
  // 101 selects input6
  // 110 selects input7
  // 111 selects input8
    
  output->clearTT();
  output->clearFanin();

  output->tt.setNumVars(11);

  output->addFanin(select1);
  output->addFanin(select2);
  output->addFanin(select3);
  output->addFanin(input8);
  output->addFanin(input7);
  output->addFanin(input6);
  output->addFanin(input5);
  output->addFanin(input4);
  output->addFanin(input3);
  output->addFanin(input2);
  output->addFanin(input1);

  output->tt.addEntry("000-------1");
  output->tt.addEntry("001------1-");
  output->tt.addEntry("010-----1--");
  output->tt.addEntry("011----1---");
  output->tt.addEntry("100---1----");
  output->tt.addEntry("101--1-----");
  output->tt.addEntry("110-1------");
  output->tt.addEntry("1111-------");
  
    
  return 0;
}



#include <iostream>
#include <string>
#include <cmath>
#include <deque>
#include <sstream>
#include <stdlib.h>
using namespace std;

int main(int argc, char *argv[]){
  
  if (argc != 3){
    cerr << "error: number of inputs" << endl;
    return 0;
  }
  
  int numbits = atoi(argv[1]);
  string type = string(argv[2]);

  deque<deque<string> > outputs;
  deque<string> empty;
  empty.push_front(""); 


  if (type == "mult"){
    for (int i = 0; i < 2*numbits; i++){
      outputs.push_front(empty);
    }
  }
  else if (type == "add" || type == "sub"){
    for (int i = 0; i < numbits; i++){
      outputs.push_front(empty);
    }
  }
  else {
    for (int i = 0; i < 20; i++)
    {
      outputs.push_front(empty);
    }
  }
  
  if (type == "add"){
    outputs.push_front(empty);
  }

  // print header of blif
  cout << ".model ";
  if (type == "add"){
    stringstream sstr;
    sstr << numbits;
    cout << "adder" + sstr.str() + "\n";  
  }
  else if (type == "sub"){
    stringstream sstr;
    sstr << numbits;
    cout << "sub" + sstr.str() + "\n";
  }
  else if (type == "mult"){
    stringstream sstr;
    sstr << numbits;
    cout << "mult" + sstr.str() + "\n";
  }
  else if (type == "datapath"){
    cout << "absmin9x12y\n";
  } 
  else{
    cerr << "error: unknown type" << endl;
    exit(3);
  }

  // print inputs and outputs of blif
  cout << endl;
  cout << ".inputs ";
  string input = "";
  string a;
  string b;
  if (type != "datapath"){
    for (int i = numbits-1; i >= 0; i--){
      stringstream sstr;
      sstr << i;
      a = "a[" + sstr.str() + "] ";
      cout << a;
      input += a;
    }
    for (int i = numbits-1; i >= 0; i--){
      stringstream sstr;
      sstr << i;
      b = "b[" + sstr.str() + "] ";
      cout << b;
      input += b; 
    }
    if (type == "add"){
      cout << "cin\n";
      input += "cin";
    }
  }
  else{
    for (int i = 15; i >= 0; i--){
      stringstream sstr;
      sstr << i;
      cout << "x[" + sstr.str() + "] ";
    }
    for (int i = 15; i >= 0; i--){
      stringstream sstr;
      sstr << i;
      cout << "y[" + sstr.str() + "] ";
    }
    cout << "\n";
  }
  cout << endl;
  cout << ".outputs ";
  if (type != "datapath" && type != "mult"){
    for (int i = 0; i < numbits; i++){
      stringstream sstr;
      sstr << i;
      cout << "s[" + sstr.str() + "] "; 
    }
    if (type == "add")
    {
      cout << "cout";
    }
  }
  else if (type != "mult") {
    for (int i = 0; i < 20; i++){
      stringstream sstr;
      sstr << i;
      cout << "z[" + sstr.str() + "] ";
    }
  }
  else{
    for (int i = 0; i < 2*numbits; i++){
      stringstream sstr;
      sstr << i;
      cout << "s[" + sstr.str() + "] ";
    }
  }
  cout << endl << endl;

  // fill outputs vectors with strings of binary input
  int maxnum = 0;
  int leastnum = 0;
  int result = 0;
  int current_result = 0;
  int num = 0;
  int num1 = 0;
  int num2 = 0;
  string inputs = "";
  string input1 = "";
  string input2 = "";
  
  if (type != "datapath" && type != "sub"){
    maxnum = pow(2, numbits);
    for (int i = 0; i < maxnum; i++){
      for(int j = 0; j < maxnum; j++){
        if (type == "add"){
          result = i + j;    
        }
        else if (type == "mult"){
          result = i * j;
        }
        num1 = i;
        num2 = j;
        input1 = "";
        input2 = "";
        for (int k = numbits - 1; k >= 0; k--){
          num = pow(2,k);
          if (num1 - num >= 0){
            num1 -= num;
            input1 += "1";
          }
          else{
            input1 += "0";
          }
          if (num2 - num >= 0){
            num2 -= num;
            input2 += "1";
          }
          else{
            input2 += "0";
          }
        }
        inputs = input1 + input2;
        string new_input = inputs;
        if (type == "add"){
          for (int d = 0; d < 2; d++){
            new_input = inputs;
            if (d == 0){
              new_input += "0";
              current_result = result;
              for (int k = numbits; k >= 0; k--){
                num = pow(2,k);
                if (current_result - num >= 0){
                  outputs[k].push_front(new_input);
                  current_result -= num;
                }
              }
            }
            else{
              new_input += "1";
              current_result = result+1;
              for (int k = numbits; k >= 0; k--){
                num = pow(2,k);
                if (current_result - num >= 0){
                  outputs[k].push_front(new_input);
                  current_result -= num;
                }
              }
            }
          }
        }
        else {
          current_result = result;
          for (int k = numbits*2 - 1; k >= 0; k--){
            num = pow(2,k);
            if (current_result - num >= 0){
              outputs[k].push_front(inputs);
              current_result -= num;
            }
          }
        }
      }
    }
  }
  else if (type == "datapath"){
    maxnum = pow(2,16);
    int ninex;
    int twelvey;
    for (int i = 0; i < maxnum; i++)
    {
      for (int j = 0; j < maxnum; j++)
      {
        cout << i << " " << j << endl;
        input1 = "";
        input2 = "";
        num1 = i;
        num2 = j;
        ninex = 9*num1;
        twelvey = 12*num2;
        if (ninex < twelvey)
        {
          if (ninex < 0)
          {
            result = ninex*(-1);
          }
          
          else
          {
            result = ninex;
          }
        }
        else
        {
          if (twelvey < 0)
          {
            result = twelvey*(-1);
          }
          
          else
          {
            result = twelvey;
          }
        }
        
        for (int k = 15; k >= 0; k--){
          num = pow(2,k);
          if (num1 - num >= 0){
            num1 -= num;
            input1 += "1";
          }
          else{
            input1 += "0";
          }
          if (num2 - num >= 0){
            num2 -= num;
            input2 += "1";
          }
          else{
            input2 += "0";
          }
        }
        
        inputs = input1 + input2;
        
        for (int k = 20; k >= 0; k--){
          num = pow(2,k);
          if (result - num >= 0){
            outputs[k].push_front(inputs);
            result -= num;
          }
        }
      }
    }
  }
  else if (type == "sub"){
    maxnum = pow(2, numbits-1);
    leastnum = pow(2, numbits-1)*(-1);
    unsigned int helper = 0;
    for (int i = leastnum; i < maxnum; i++){
      for(int j = leastnum; j < maxnum; j++){
        input1 = "";
        input2 = "";
        num1 = i;
        num2 = j;
        result = i - j;
        if (i < 0)
        {
          input1 += "1";
          num1 = unsigned(num1);
          helper = 0;
          for (int l = 0; l < numbits-1; l++)
          {
            helper += pow(2,l);
          }
          num1 &= helper;
        }
        else
        {
          input1 += "0";
          num1 = i;
        }
        if (j < 0)
        {
          input2 += "1";
          num2 = unsigned(num2);
          helper = 0;
          for (int l = 0; l < numbits-1; l++)
          {
            helper += pow(2,l);
          }
          num2 &= helper;
        }
        else
        {
          input2 += "0";
          num2 = j;
        }
        for (int k = numbits - 2; k >= 0; k--){
          num = pow(2,k);
          if (num1 - num >= 0){
            num1 -= num;
            input1 += "1";
          }
          else{
            input1 += "0";
          }
          if (num2 - num >= 0){
            num2 -= num;
            input2 += "1";
          }
          else{
            input2 += "0";
          }
        }
        inputs = input1 + input2;
        string new_input = inputs;
        unsigned int result_help = result;
        unsigned int new_result = 0;
        if (result < 0)
        {
          outputs[numbits-1].push_front(inputs);
          // and result_help with a number that is
          // all 0's except for the last (numbits - 1)
          for (int l = 0; l < numbits-1; l++)
          {
            new_result += pow(2,l);
          }
          result_help &= new_result;
          for (int k = numbits*2 - 1; k >= 0; k--)
          {
            num = pow(2,k);
            if (signed(result_help) - num >= 0)
            {
              outputs[k].push_front(inputs);
              result_help -= num;
            }
          }
        }
        else
        {
          for (int k = numbits*2 - 1; k >= 0; k--){
            num = pow(2,k);
            if (result - num >= 0){
              outputs[k].push_front(inputs);
              result -= num;
            }
          }
        }
      }
    }
  }
  

  
  
  


  if (type != "datapath" && type != "mult"){
    for (int i = 0; i < numbits; i++){
      stringstream sstr;
      sstr << i;
      cout << ".names ";
      cout << input << "";
      cout << "s[" + sstr.str() + "]\n";
      while (!outputs[i].empty()){
        if (outputs[i].front() == ""){
          outputs[i].pop_front();
        }
        else{
          cout << outputs[i].front() << " 1\n";
          outputs[i].pop_front();
        } 
      }
      cout << endl;
    }
    
    if (type == "add"){
      cout << ".names ";
      cout << input << "";
      cout << "cout" << endl;
      while (!outputs[numbits].empty()){
        if (outputs[numbits].front() == ""){
          outputs[numbits].pop_front();
        }
        else{
          cout << outputs[numbits].front() << " 1\n";
          outputs[numbits].pop_front();
        }
      }
      
      cout << endl;
    }
  }
  
  else if (type == "mult")
  {
    for (int i = 0; i < 2*numbits; i++){
      if (outputs[i].front() != "" && !outputs[i].empty())
      { 
        stringstream sstr;
        sstr << i;
        cout << ".names ";
        cout << input << "";
        cout << "s[" + sstr.str() + "]\n";
        while (!outputs[i].empty()){
          if (outputs[i].front() == ""){
            outputs[i].pop_front();
          }
          else{
            cout << outputs[i].front() << " 1\n";
            outputs[i].pop_front();
          }
        }
        cout << endl;
      }
      else
      {
        if (outputs[i].front() == "")
        {
          outputs[i].pop_front();
        }
      }
    }
  }
  
  else if (type == "datapath")
  {
    for (int i = 0; i < 20; i++)
    {
      if (outputs[i].front() != "" && !outputs[i].empty()) 
      {
        stringstream sstr;
        sstr << i;
        cout << ".names ";
        cout << input << "";
        cout << "y[" + sstr.str() + "]\n";
        while (!outputs[i].empty()){
          if (outputs[i].front() == ""){
            outputs[i].pop_front();
          }
          else{
            cout << outputs[i].front() << " 1\n";
            outputs[i].pop_front();
          }
        }
        cout << endl;
      }
      else
      {
        if (outputs[i].front() == "")
        {
          outputs[i].pop_front();
        }
      }
    }
  }
  
  cout << ".end" << endl;

  return 0;
}







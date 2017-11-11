#include <iostream>
#include <cassert>
#include <fstream>

#include "errors.h"

using namespace std;

int charToNum(char alphabetic_char){
  int result = alphabetic_char - 'A';
  return result;
}

int validateParameters(){
  return 0;
}

int validateConfiguration(string filename){
  ifstream in_stream;
  ofstream out_stream;

  in_stream.open(filename);
  if (in_stream.fail())
  {
    return ERROR_OPENING_CONFIGURATION_FILE;
  }
  return 0;
}

int runAssertions() {
  assert(charToNum('A') == 0);
  assert(charToNum('B') == 1);
  assert(charToNum('D') == 3);
  assert(charToNum('Y') == 24);
  assert(charToNum('Z') == 25);
  assert(validateConfiguration("plugboards/I.pb") == 0);

  return 0;
}

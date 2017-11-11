#include <iostream>
#include <cassert>
#include <fstream>
#include <vector>

#include "errors.h"

using namespace std;

int charToNum(char alphabetic_char){
  int result = alphabetic_char - 'A';
  return result;
}

int validateParameters(){
  return 0;
}

int validateConfiguration(string config_filename){
  vector<int> numbers;
  int number;
  ifstream in_stream;

  in_stream.open(config_filename);
  if (in_stream.fail())
  {
    cout << "Configuration file cannot be opened." << endl;
    return ERROR_OPENING_CONFIGURATION_FILE;
  }

  while (!in_stream.eof())
  {
  // add contents of file into numbers array
    while (in_stream >> number) {
      numbers.push_back(number);
    }

  // check that there is no dup of contacts


  // check that there are an even number of numbers


  // check that number is between 0 and 25


  // check that file only contains numeric characters


  }
  in_stream.close();
    return NO_ERROR;
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

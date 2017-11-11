#include <iostream>
#include <string>
#include <fstream>
#include "errors.h"
#include "main.h"

using namespace std;

int main(int argc, char** argv){
  if (!(argc >= 3)) {
    cout << "Insufficient number of parameters" << endl;
    return INSUFFICIENT_NUMBER_OF_PARAMETERS;
  }

  for (int i = 1; i < argc; i++){
    string config_filename = argv[i];
    if (!can_open_file(config_filename)){
      cout << "Configuration file cannot be opened" << endl;
      return ERROR_OPENING_CONFIGURATION_FILE;
    } else if (!contains_only_nums(config_filename)) {
      cout << "Configuration file does not contain only numbers" << endl;
      return NON_NUMERIC_CHARACTER;
    } else if (!contains_valid_indexes(config_filename)){
      cout << "Configuration file contains an invalid index" << endl;
      return INVALID_INDEX;
    }
  }
  // specific checks for configuration files
  // if (!valid_plugboard_config(config_filename)){
  //
  // }


  return NO_ERROR;
}

int* get_configuration(string config_filename){
  string token;
  static int numbers[52];
  ifstream in_stream(config_filename.c_str());

  int n = 0;
  while(getline(in_stream, token, ' ')) {
    numbers[n] = stoi(token);
    n++;
  }

  in_stream.close();
  return numbers;
}

bool can_open_file(string config_filename){
  ifstream in_stream(config_filename.c_str());

  if (in_stream.fail())
  {
    cout << "Configuration file cannot be opened." << endl;
    return false;
  }
  in_stream.close();

  return true;
}

bool is_num(string token){
  for (int i = 0; i < token.length(); i++) {
    if (!isdigit(token[i])){
      return false;
    }
  }
  return true;
}

bool contains_only_nums(string config_filename){
  string token;
  ifstream in_stream(config_filename.c_str());

  while(getline(in_stream, token, ' ')) {
    if (!is_num(token)){
      return false;
    }
  }
  in_stream.close();
  return true;
}

bool contains_valid_indexes(string config_filename){
  string token;
  ifstream in_stream(config_filename.c_str());

  while(getline(in_stream, token, ' ')) {
    if (!((stoi(token) >= 0) && (stoi(token) <= 25))){
      return false;
    }
  }

  in_stream.close();
  return true;
}

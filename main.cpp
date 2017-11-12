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
    string ext = get_extension(config_filename);
    if (!can_open_file(config_filename)){
      cout << "Configuration file cannot be opened" << endl;
      return ERROR_OPENING_CONFIGURATION_FILE;
    } if (!contains_only_nums(config_filename)) {
        cout << "Configuration file does not contain only numbers" << endl;
        return NON_NUMERIC_CHARACTER;
      } else if (!contains_valid_indexes(config_filename)){
        cout << "Configuration file contains an invalid index" << endl;
        return INVALID_INDEX;
      } else if (ext == "pb" && !valid_plugboard_configuration(config_filename)) {
        cout << "Impossible plugboard configuration" << endl;
        return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
      } else if (ext == "pb" && !valid_plugboard_parameters(config_filename)) {
        cout << "Incorrect number of plugboard parameters" << endl;
        return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
      } else if (ext == "rot" && !valid_rotor_mapping(config_filename)){
        cout << "Invalid rotor mapping" << endl;
        return INVALID_ROTOR_MAPPING;
      } else if (ext == "rot" && !valid_rotor_start_position(config_filename)){
        cout << "No rotor starting position" << endl;
        return NO_ROTOR_STARTING_POSITION;
      } else if (ext == "rf" && !valid_reflector_mapping(config_filename)){
        cout << "Invalid reflector mapping" << endl;
        return INVALID_REFLECTOR_MAPPING;
      } else if (ext == "rf" && !valid_reflector_parameters(config_filename)){
        cout << "Incorrect number of reflector parameters" << endl;
        return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
      }
  }

  return NO_ERROR;
}

int* get_configuration(string config_filename){
  string token;
  int numbers[52];
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
      if (!isspace(token[i])) {
        return false;
      }
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

string get_extension(string config_filename){
  int i_dot = rfind(config_filename, ".");
  if (i_dot == npos) {
    return "";
  }
  return config_filename.substr(i_dot + 1, config_filename.length());
}


bool valid_plugboard_configuration(string config_filename){
  return true;
}

bool valid_plugboard_parameters(string config_filename){
  return true;
}

bool valid_rotor_mapping(string config_filename){
  return true;
}

bool valid_rotor_start_position(string config_filename){
  return true;
}

bool valid_reflector_mapping(string config_filename){
  return true;
}

bool valid_reflector_parameters(string config_filename){
  return true;
}

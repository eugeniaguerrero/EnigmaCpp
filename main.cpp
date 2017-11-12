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
    string token;
    int j = 0;
    int numbers[26];

    ifstream in_stream(config_filename.c_str());
    while(getline(in_stream, token, ' ')) {
      if (!can_open_file(in_stream)){
        cout << "Configuration file cannot be opened" << endl;
        return ERROR_OPENING_CONFIGURATION_FILE;
      } if (!is_num(token)) {
        cout << "Configuration file does not contain only numbers" << endl;
        return NON_NUMERIC_CHARACTER;
      } else if (!valid_index(token)){
        cout << "Configuration file contains an invalid index" << endl;
        return INVALID_INDEX;
      } else if (ext == "pb" && !contains(stoi(token), numbers, j)) {
        cout << "Impossible plugboard configuration" << endl;
        return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
      } else if (ext == "rot" && !valid_rotor_mapping(token)){
        cout << "Invalid rotor mapping" << endl;
        return INVALID_ROTOR_MAPPING;
      } else if (ext == "rot" && !valid_rotor_start_position(token)){
        cout << "No rotor starting position" << endl;
        return NO_ROTOR_STARTING_POSITION;
      } else if (ext == "rf" && !contains(stoi(token), numbers, j)){
        cout << "Invalid reflector mapping" << endl;
        return INVALID_REFLECTOR_MAPPING;
      } else if (ext == "rf" && !valid_reflector_parameters(token)){
        cout << "Incorrect number of reflector parameters" << endl;
        return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
      }
      numbers[j] = stoi(token);
      j++;
    }
    in_stream.close();
    if (ext == "pb" && !valid_plugboard_parameters(j)) {
      cout << "Incorrect number of plugboard parameters" << endl;
      return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
    }
  }
  return NO_ERROR;
}

bool can_open_file(ifstream &in_stream){
  if (in_stream.fail())
  {
    cout << "Configuration file cannot be opened." << endl;
    return false;
  }
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

bool valid_index(string token){
  return (stoi(token) >= 0) && (stoi(token) <= 25);
}

string get_extension(string config_filename){
  // find last dot in given string
  int ext_index = config_filename.rfind(".");
  // no extension found, return empty string
  if (ext_index == string::npos) {
    return "";
  }
  // otherwise return substring after the last dot
  return config_filename.substr(ext_index + 1, config_filename.length());
}

// size of numbers array needs to be explicit to get start and end of array
bool contains(int elem, int (&array)[26], int array_size){
  for (int i = 0; i < array_size; i++) {
    if (array[i] == elem) {
      return false;
    }
  }
  return true;
}

bool valid_plugboard_parameters(int size_of_config_array){
  return size_of_config_array % 2 == 0;
}

bool valid_rotor_mapping(string token){
  return true;
}

bool valid_rotor_start_position(string token){
  return true;
}

bool valid_reflector_parameters(string token){
  return true;
}

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "errors.h"
#include "main.h"

using namespace std;

int main(int argc, char** argv){
  if (!(argc >= 3)) {
    cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>* rotor-positions)?" << endl;
    return INSUFFICIENT_NUMBER_OF_PARAMETERS;
  }

  for (int i = 1; i < argc; i++){
    string config_filename = argv[i];
    string ext = get_extension(config_filename);
    string token;
    int j = 0;
    int numbers[26];

    ifstream in_stream(config_filename.c_str());
    if (!can_open_file(in_stream)){
      cerr << "Configuration file cannot be opened" << endl;
      return ERROR_OPENING_CONFIGURATION_FILE;
    }

    while(getline(in_stream, token, ' ')) {
      // remove whitespace
      remove_whitespace(token);
      // perform checks
      if (!is_num(token) && ext == "pb") {
        cerr << "Non-numeric character in plugboard file " << config_filename << endl;
        return NON_NUMERIC_CHARACTER;
      } else if (!is_num(token) && ext == "rot") {
        cerr << "Non-numeric character for mapping in rotor file " << config_filename << endl;
        return NON_NUMERIC_CHARACTER;
      } else if (!is_num(token) && ext == "rf") {
        cerr << "Non-numeric character in reflector file " << config_filename << endl;
        return NON_NUMERIC_CHARACTER;
      } else if (!valid_index(token)){
        cerr << "Configuration file contains an invalid index" << endl;
        return INVALID_INDEX;
      } else if (ext == "pb" && !contains(stoi(token), numbers, j)) {
        cerr << "Incorrect number of parameters in plugboard file " << config_filename << endl;
        return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
      } else if (ext == "rot" && !contains(stoi(token), numbers, j)){
        cerr << "Not all inputs mapped in rotor file: " << config_filename << endl;
        return INVALID_ROTOR_MAPPING;
      } else if (ext == "rot" && !valid_rotor_start_position(token)){
        cerr << "No rotor starting position" << endl;
        return NO_ROTOR_STARTING_POSITION;
      } else if (ext == "rf" && !contains(stoi(token), numbers, j)){
        cerr << "Insufficient number of mappings in reflector file: " << config_filename << endl;
        return INVALID_REFLECTOR_MAPPING;
      }
      numbers[j] = stoi(token);
      j++;
    }
    in_stream.close();
    if (ext == "pb" && !valid_plugboard_parameters(j)) {
      cerr << "Incorrect number of parameters in plugboard file " << config_filename << endl;
      return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
    } else if (ext == "rot" && !valid_rotor_mapping(j)){
      cerr << "Not all inputs mapped in rotor file: " << config_filename << endl;
      return INVALID_ROTOR_MAPPING;
    } else if (ext == "rf" && !valid_reflector_parameters(j) && j % 2 != 0){
      cerr << "Incorrect (odd) number of parameters in reflector file " << config_filename << endl;
      return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
    } else if (ext == "rf" && !valid_reflector_parameters(j)){
      cerr << "Insufficient number of mappings in reflector file: " << config_filename << endl;
      return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
    }

  }
  return NO_ERROR;
}

void remove_whitespace(string &token) {
  token.erase(remove_if(token.begin(), token.end(), ::isspace), token.end());
}

bool can_open_file(ifstream &in_stream){
  if (in_stream.fail())
  {
    cerr << "Configuration file cannot be opened." << endl;
    return false;
  }
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

bool valid_rotor_mapping(int size_of_config_array){
  return size_of_config_array == 26;
}

bool valid_rotor_start_position(string token){
  return true;
}

bool valid_reflector_parameters(int size_of_config_array){
  return size_of_config_array == 26;
}

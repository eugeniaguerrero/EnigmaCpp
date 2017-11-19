#include "main.h"

using namespace std;

int main(int argc, char** argv){

  // check if too few parameters were provided, or if a rotor without a position file (or vice versa)
  if (argc < 3 || argc == 4) {
    cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>* rotor-positions)?" << endl;
    return INSUFFICIENT_NUMBER_OF_PARAMETERS;
  }

  // check config files appear in correct place in command line
  for (int i = 1; i < argc; i++) {
    // get file extension
    string config_filename = argv[i];
    string ext = get_extension(config_filename);
    // check if in correct place
    if (i == 1 && ext != "pb") {
      cerr << "Configuration file cannot be opened" << endl;
      return ERROR_OPENING_CONFIGURATION_FILE;
    } else if (i == 2 && ext != "rf") {
      cerr << "Configuration file cannot be opened" << endl;
      return ERROR_OPENING_CONFIGURATION_FILE;
    } else if (i > 2 && i < argc-1 && ext != "rot") {
      cerr << "Configuration file cannot be opened" << endl;
      return ERROR_OPENING_CONFIGURATION_FILE;
    } else if (i > 2 && i == argc-1 && ext != "pos") {
      cerr << "Configuration file cannot be opened" << endl;
      return ERROR_OPENING_CONFIGURATION_FILE;
    }
  }

  // define components for enigma machine
  Plugboard plugboard;
  Reflector reflector;
  vector<Rotor> rotors;
  vector<int> rotor_positions;
  vector<vector<int>> rotor_notches;
  vector<vector<int>> rotor_mappings;

  // loop over configuration files
  for (int i = 1; i < argc; i++){
    // initialise convenient variables
    string config_filename = argv[i];
    string ext = get_extension(config_filename);
    string token;

    // open config file
    ifstream in_stream(config_filename.c_str());
    if (in_stream.fail()){
      cerr << "Configuration file cannot be opened" << endl;
      return ERROR_OPENING_CONFIGURATION_FILE;
    }

    // read from file token by token and store in mappings
    vector<int> mappings = {};
    while(getline(in_stream, token, ' ')) {

      // remove whitespace
      remove_whitespace(token);
      if (token == "") {
        continue;
      }

      // check if token is not a number
      if (!is_num(token)) {
        if (ext == "pb") {
          cerr << "Non-numeric character in plugboard file " << config_filename << endl;
        } else if (ext == "rot") {
          cerr << "Non-numeric character for mapping in rotor file " << config_filename << endl;
        } else if (ext == "rf") {
          cerr << "Non-numeric character in reflector file " << config_filename << endl;
        } else if (ext == "pos") {
          cerr << "Non-numeric character in rotor positions file " << config_filename << endl;
        }
        return NON_NUMERIC_CHARACTER;
      }

      // convert token to number
      int index = stoi(token);

      // check if it's a valid index
      if (index < 0 || index > 25){
        cerr << "Configuration file contains an invalid index" << endl;
        return INVALID_INDEX;
      }

      // perform plugboard checks
      if (ext == "pb") {
        if (mappings.size() >= 26) {
          cerr << "Incorrect number of parameters in plugboard file " << config_filename << endl;
          return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
        } else if (contains(index, mappings)) {
          cerr << "Incorrect number of parameters in plugboard file " << config_filename << endl;
          return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
        }
      }

      // perform reflector checks
      if (ext == "rf") {
        if (mappings.size() >= 26) {
          cerr << "Incorrect (odd) number of parameters in reflector file " << config_filename << endl;
          return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
        } else if (contains(index, mappings)){
          cerr << "Insufficient number of mappings in reflector file H: " << config_filename << endl;
          return INVALID_REFLECTOR_MAPPING;
        }
      }

      // perform rotor checks
      if (ext == "rot") {
        // still reading in mappings, otherwise, reading in notches
        if (mappings.size() < 26) {
          if (contains(index, mappings)) {
            print_rotor_duplication_message(index, mappings);
            return INVALID_ROTOR_MAPPING;
          }
        } else {
          vector<int> notches(mappings.begin() + 26, mappings.end());
          if (contains(index, notches)) {
            cerr << "Not all inputs mapped in rotor file: " << config_filename << endl;
            return INVALID_ROTOR_MAPPING;
          }
        }
      }

      // perform position checks
      if (ext == "pos") {
        if (mappings.size() == rotor_mappings.size()) {
          cerr << "Configuration file contains an invalid index" << endl;
          return INVALID_INDEX;
        }
      }

      // add index to mappings
      mappings.push_back(index);
    }

    // close file -- finished reading
    in_stream.close();

    // perform plugboard checks
    if (ext == "pb" && mappings.size() % 2 != 0){
      cerr << "Incorrect number of parameters in plugboard file " << config_filename << endl;
      return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
    }

    // perform reflector checks
    if (ext == "rf" && mappings.size() != 26){
      cerr << "Insufficient number of mappings in reflector file: " << config_filename << endl;
      return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
    } else if (ext == "rf" && mappings.size() < 26 && mappings.size() % 2 != 0){
      cerr << "Incorrect (odd) number of parameters in reflector file: " << config_filename << endl;
      return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
    }

    // perform rotor checks
    if (ext == "rot" && !valid_rotor_mapping(mappings)){
      cerr << "Not all inputs mapped in rotor file: " << config_filename << endl;
      return INVALID_ROTOR_MAPPING;
    }

    // perform position checks
    if (ext == "pos" && mappings.size() != rotor_mappings.size()) {
      cerr << "No rotor starting position" << endl;
      return NO_ROTOR_STARTING_POSITION;
    }

    // define each component
    if (ext == "pb") {
      // cout << "In main: passing ";
      // print_vector(mappings);
      // cout <<  " to plugboard" << endl;
      plugboard = Plugboard(mappings);
      // cout << "In main: created plugboard with mapping ";
      // print_vector(plugboard.get_mappings());
      // cout << endl;

    } else if (ext == "rf") {
      reflector = Reflector(mappings);
    } else if (ext == "rot") {
      // define current rotor's mappings
      vector<int> current_rotor_mapping(mappings.begin(), mappings.begin() + 26);
      // add to list of mappings for rotors
      rotor_mappings.push_back(current_rotor_mapping);
      // define current rotor's notches
      vector<int> current_rotor_notches(mappings.begin() + 26, mappings.end());
      // add to list of notches for rotors
      rotor_notches.push_back(current_rotor_notches);
    } else if (ext == "pos") {
      rotor_positions = mappings;
    }
  }

  // now we've read every configuration file, we can define the rotors
  for (size_t i = 0; i < rotor_positions.size(); i++) {
    Rotor current_rotor = Rotor(rotor_positions[i], rotor_notches[i], rotor_mappings[i]);
    rotors.push_back(current_rotor);
  }

  // define EnigmaMachine here (since its components are available)
  EnigmaMachine enigmaMachine = EnigmaMachine(plugboard, rotors, reflector);

  // read in characters from standard input
  char current_char;
  cin >> ws;
  while (!cin.eof())
  {
    cin >> current_char;
    if (current_char >= 'A' && current_char <= 'Z') {
      cout << (char) (enigmaMachine.encode(current_char - 'A') + 'A');
    } else {
      cerr << current_char << " is not a valid input character (input characters must be uppercase letters A-Z)!" << endl;
      return INVALID_INPUT_CHARACTER;
    }
    cin >> ws;
  }
  return NO_ERROR;
}

void remove_whitespace(string &token) {
  token.erase(remove_if(token.begin(), token.end(), ::isspace), token.end());
}

bool is_num(string token){
  for (size_t i = 0; i < token.length(); i++) {
    if (!isdigit(token[i])){
      return false;
    }
  }
  return true;
}

string get_extension(string config_filename){
  // find last dot in given string
  size_t ext_index = config_filename.rfind(".");
  // no extension found, return empty string
  if (ext_index == string::npos) {
    return "";
  }
  // otherwise return substring after the last dot
  return config_filename.substr(ext_index + 1, config_filename.length());
}


bool valid_rotor_mapping(vector<int> mappings){
  if (mappings.size() < 26) {
    return false;
  } else if (mappings.size() > 52) {
    return false;
  } else {
    vector<int> numbers(mappings.begin(), mappings.begin() + 26);
    vector<int> notches(mappings.begin() + 26, mappings.end());
    return !contains_duplicates(numbers) && !contains_duplicates(notches);
  }
}

bool contains_duplicates(vector<int> mappings) {
  vector<int> seen;
  for (size_t i = 0; i < mappings.size(); i++) {
    if (contains(mappings[i], seen)) {
      return true;
    } else {
      seen.push_back(mappings[i]);
    }
  }
  return false;
}

void print_rotor_duplication_message(int index, vector<int> mappings){
  for (size_t i = 0; i < mappings.size(); i++){
    if (contains(index, mappings)){
      // int attempting_to_map_to;
      // int previously_mapped_to;
      //
    }
      // cerr << "Invalid mapping of input " << attempting_to_map_to;
      // cerr << " to output " << token;
      // cerr << "(output " << token << "is already mapped to from input";
      // cerr << previously_mapped_to << ")" << endl;
  }
}

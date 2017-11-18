#include "main.h"

using namespace std;

int main(int argc, char** argv){

  if (!(argc >= 3)) {
    cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>* rotor-positions)?" << endl;
    return INSUFFICIENT_NUMBER_OF_PARAMETERS;
  }

  // check config files appear in correct place in command line
  for (int i = 1; i < argc; i++){
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
    } else if (i > 2 && i == argc-1 && ext != "pos") {
      cerr << "Configuration file cannot be opened" << endl;
      return ERROR_OPENING_CONFIGURATION_FILE;
    } else if (i > 2 && i < argc-1 && ext != "rot") {
      cerr << "Configuration file cannot be opened" << endl;
      return ERROR_OPENING_CONFIGURATION_FILE;
    }
  }

  // loop over command line arguments
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
    // read from file token by token
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

      // perform checks
      if (ext == "pb" && mappings.size() >= 26) {
        cerr << "Incorrect number of parameters in plugboard file " << config_filename << endl;
        return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
      } if (ext == "rf" && mappings.size() >= 26) {
        cerr << "Incorrect (odd) number of parameters in reflector file " << config_filename << endl;
        return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
      } else if (!valid_index(index)){
        cerr << "Configuration file contains an invalid index" << endl;
        return INVALID_INDEX;
      } else if (ext == "pb" && contains(index, mappings)) {
        cerr << "Incorrect number of parameters in plugboard file " << config_filename << endl;
        return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
      } else if (ext == "rot" && contains(index, mappings) && mappings.size() <= 26){
        cerr << "Not all inputs mapped in rotor file: " << config_filename << endl;
        return INVALID_ROTOR_MAPPING;
      } else if (ext == "rot" && !valid_rotor_start_position(index)){
        cerr << "No rotor starting position" << endl;
        return NO_ROTOR_STARTING_POSITION;
      } else if (ext == "rf" && contains(index, mappings)){
        cerr << "Insufficient number of mappings in reflector file: " << config_filename << endl;
        return INVALID_REFLECTOR_MAPPING;
      }
      // add index to mappings
      mappings.push_back(index);
    }

    in_stream.close();
    if (ext == "pb" && !valid_plugboard_parameters(mappings.size())) {
      cerr << "Incorrect number of parameters in plugboard file " << config_filename << endl;
      return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
    } else if (ext == "rot" && !valid_rotor_mapping(mappings)){
      cerr << "Not all inputs mapped in rotor file: " << config_filename << endl;
      return INVALID_ROTOR_MAPPING;
    } else if (ext == "rf" && (mappings.size() % 2 != 0)){
      cerr << "Incorrect (odd) number of parameters in reflector file " << config_filename << endl;
      return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
    } else if (ext == "rf" && !valid_reflector_parameters(mappings.size())){
      cerr << "Insufficient number of mappings in reflector file: " << config_filename << endl;
      return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
    }

    // define each component
    if (ext == "pb"){
      Plugboard plugboard = Plugboard(mappings);
    }

    if (ext == "pos"){
      vector<int> positions = mappings;
    }


    // instantiate number of rotors (deducting enigma, reflector, plugboard, position files)

      // Rotor rotor = Rotor(position, notches, mappings);

    if (ext == "rf"){
      Reflector reflector = Reflector(mappings);
    }
  }

  // define EnigmaMachine here (since its components are available)
  EnigmaMachine enigmaMachine(argc, argv);

  // read in characters from standard input
  char current_char;
  cin >> ws;
  while (!cin.eof())
  {
    cin >> current_char;
    cout << (char) enigmaMachine.encode(current_char);
    cin >> ws;
  }

  return NO_ERROR;
}

void remove_whitespace(string &token) {
  token.erase(remove_if(token.begin(), token.end(), ::isspace), token.end());
}

bool is_num(string token){
  for (int i = 0; i < token.length(); i++) {
    if (!isdigit(token[i])){
      return false;
    }
  }
  return true;
}

bool valid_index(int index){
  return (index >= 0) && (index <= 25);
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


bool valid_plugboard_parameters(int size_of_config_array){
  return size_of_config_array % 2 == 0;
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

bool valid_rotor_start_position(int index){
  return true;
}

// both have to be unique and cannot overflow
bool valid_reflector_parameters(int size_of_config_array){
  return size_of_config_array == 26;
}

bool contains_duplicates(vector<int> mappings) {
  vector<int> seen;
  for (size_t i = 0; i < mappings.size(); i++) {
    if (contains(mappings[i], seen)) {
      return false;
    } else {
      seen.push_back(mappings[i]);
    }
  }
  return true;
}

void print_vector(vector<int> mappings) {
  cout << "[ ";
  for (size_t i = 0; i < mappings.size(); i++) {
    cout << mappings[i] << " ";
  }
  cout << "]" << endl;
}

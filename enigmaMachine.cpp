#include "enigmaMachine.h"

using namespace std;

int EnigmaMachine::encode(int input) {

  // pass through plugboard
  // cout << "Given: " << input << endl;
  input = plugboard.encode(input);
  // cout << "After plugboard: " << input << endl;

  // pass through rotors right to left
  // cout << "Given: " << input << endl;
  for (int i = rotors.size() - 1; i >= 0; i--) {
    Rotor rotor = rotors[i];
    // cout << "Before rotor " << i << ": " << input << endl;
    // cout << "Rotor " << i << " has position " << rotor.get_position() << " and mappings ";
    // print_vector(rotor.get_mappings());
    input = mod(rotor.encode(mod(input + rotor.get_position(), 26)) - rotor.get_position(), 26);
    // cout << "After rotor " << i << ": " << input << endl;
  }

  // pass through reflector
  // cout << "Given: " << input << endl;
  input = reflector.encode(input);
  // cout << "After reflector: " << input << endl;

  // pass through rotors left to right
  // cout << "Given: " << input << endl;
  for (size_t i = 0; i < rotors.size(); i++) {
    Rotor rotor = rotors[i];
    // cout << "Before rotor " << i << ": " << input << endl;
    // cout << "Rotor " << i << " has position " << rotor.get_position() << " and mappings ";
    // print_vector(rotor.get_mappings());
    input = mod(rotor.decode(mod(input - rotor.get_position(), 26)) + rotor.get_position(), 26);
    // cout << "After rotor " << i << ": " << input << endl;
  }

  // pass through plugboard
  // cout << "Given: " << input << endl;
  input = plugboard.encode(input);
  // cout << "After plugboard: " << input << endl;
  
  // turn relevant rotors
  // cout << "Given: " << input << endl;
  turn_rotors();

  // return encoded input
  // cout << "Returning: " << input << endl;
  return input;
}

void EnigmaMachine::turn_rotors() {
  turn_rotors_helper(rotors.size() - 1); // turn the right-most rotor
}

void EnigmaMachine::turn_rotors_helper(int i) {
  if ((i >= 0) && rotors[i].turn()) {
    turn_rotors_helper(i - 1);  // turn rotor to left if rotor reaches notch
  }
}

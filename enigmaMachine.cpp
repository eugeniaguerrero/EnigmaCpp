#include "enigmaMachine.h"

using namespace std;

int EnigmaMachine::encode(int input) {
  // turn relevant rotors
  turn_rotors();
  // cout << "Given input: " << input << endl;
  // pass through plugboard
  // cout << "Plugboard using mappings ";
  // print_vector(plugboard.get_mappings());
  input = plugboard.encode(input);
  // cout << "After plugboard: " << input << endl;

  // pass through rotors right to left
  for (int i = rotors.size() - 1; i >= 0; i--) {
    Rotor rotor = rotors[i];
    // cout << "After " << i << " rotor: " << input << endl;
    input = mod(rotor.encode(mod(input + rotor.get_position(), 26)) - rotor.get_position(), 26);
  }

  // pass through reflector
  input = reflector.encode(input);
  // cout << "After reflector: " << input << endl;

  // pass through rotors left to right
  for (size_t i = 0; i < rotors.size(); i++) {
    Rotor rotor = rotors[i];
    input = mod(rotor.encode(mod(input + rotor.get_position(), 26)) - rotor.get_position(), 26);
  }

  // pass through plugboard
  input = plugboard.encode(input);
  // cout << "After plugboard: " << input << endl;

  // return encoded input
  // cout << "Returning input: " << input << endl;
  return input;
}

void EnigmaMachine::turn_rotors() {
  turn_rotors_helper(rotors.size() - 1); // turn rotors right to left
}

void EnigmaMachine::turn_rotors_helper(int i) {
  if ((i >= 0) && rotors[i].turn()) {
    turn_rotors_helper(i - 1);
  }
}

// mathematical version of modulus function
int EnigmaMachine::mod(int k, int n) {
    return ((k %= n) < 0) ? k + n : k;
}

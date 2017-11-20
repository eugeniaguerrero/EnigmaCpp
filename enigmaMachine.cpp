#include "enigmaMachine.h"

using namespace std;

int EnigmaMachine::encode(int input) {
  // turn relevant rotors
  turn_rotors();

  // pass through plugboard
  input = plugboard.encode(input);

  // pass through rotors right to left
  for (int i = rotors.size() - 1; i >= 0; i--) {
    Rotor rotor = rotors[i];
    input = mod(rotor.encode(mod(input + rotor.get_position(), 26)) - rotor.get_position(), 26);
  }

  // pass through reflector
  input = reflector.encode(input);

  // pass through rotors left to right
  for (size_t i = 0; i < rotors.size(); i++) {
    Rotor rotor = rotors[i];
    input = mod(rotor.decode(mod(input + rotor.get_position(), 26)) - rotor.get_position(), 26);
  }

  // pass through plugboard
  input = plugboard.encode(input);

  // return encoded input
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

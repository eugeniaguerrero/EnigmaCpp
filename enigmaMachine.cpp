#include "enigmaMachine.h"

using namespace std;

EnigmaMachine::EnigmaMachine(Plugboard _plugboard, vector<Rotor> _rotors, Reflector _reflector) {
  plugboard = _plugboard;
  rotors = _rotors;
  reflector = _reflector;
}

int EnigmaMachine::encode(int input) {
  // pass through plugboard
  input = plugboard.encode(input);

  // pass through rotors right to left
  for (int i = rotors.size() - 1; i >= 0; i--){
    Rotor rotor = rotors[i];
    input = rotor.encode(input + rotor.get_position()) - rotor.get_position();
  }

  // pass through reflector
  input = reflector.encode(input);

  // pass through rotors left to right
  for (int i = 0; i < rotors.size(); i++){
    Rotor rotor = rotors[i];
    input = rotor.encode(input - rotor.get_position()) + rotor.get_position();
  }

  // pass through plugboard
  input = plugboard.encode(input);

  // turn relevant rotors
  turn_rotors();

  return input;
}

void EnigmaMachine::turn_rotors() {
  turn_rotors_helper(0);
}

void EnigmaMachine::turn_rotors_helper(int i) {
  if ((i <= rotors.size() - 1) && rotors[rotors.size() - 1 - i].turn()) {
    turn_rotors_helper(i - 1);
  }
}

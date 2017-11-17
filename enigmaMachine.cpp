#include "enigmaMachine.h"

using namespace std;

EnigmaMachine::EnigmaMachine(Plugboard _plugboard, vector<Rotor> _rotors, Reflector _reflector) {
  plugboard = _plugboard;
  rotors = _rotors;
  reflector = _reflector;
}

int EnigmaMachine::encode(int input) {
  return input;
}

#include "enigmaMachine.h"

using namespace std;

int EnigmaMachine::encode(int input) {
  cout << "Given input: " << input << endl;

  // pass through plugboard
  cout << "Plugboard using mappings ";
  print_vector(plugboard.get_mappings());
  cout << endl;
  input = plugboard.encode(input);
  cout << "After plugboard: " << input << endl;

  // pass through rotors right to left
  for (int i = rotors.size() - 1; i >= 0; i--){
    Rotor rotor = rotors[i];
    input = rotor.encode(input + rotor.get_position()) - rotor.get_position();
    cout << "After " << i << " rotor: " << input << endl;
  }

  // pass through reflector
  input = reflector.encode(input);
  cout << "After reflector: " << input << endl;

  // pass through rotors left to right
  for (size_t i = 0; i < rotors.size(); i++){
    Rotor rotor = rotors[i];
    input = rotor.encode(input - rotor.get_position()) + rotor.get_position();
    cout << "After " << i << " rotor: " << input << endl;
  }

  // pass through plugboard
  input = plugboard.encode(input);
  cout << "After plugboard: " << input << endl;

  // turn relevant rotors
  turn_rotors();

  // return encoded input
  cout << "Returning input: " << input << endl;
  return input;
}

void EnigmaMachine::turn_rotors() {
  turn_rotors_helper(0);
}

void EnigmaMachine::turn_rotors_helper(size_t i) {
  if ((i <= rotors.size() - 1) && rotors[rotors.size() - 1 - i].turn()) {
    turn_rotors_helper(i + 1);
  }
}

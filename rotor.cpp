#include "rotor.h"

// define the constructor Rotor in the Rotor class
Rotor::Rotor(int _position, vector<int> _notches, vector<int> _mappings) {
  // intialise the attributes
  position = _position;
  notches = _notches;
  mappings = _mappings;
}

int Rotor::get_position(){
  return position;
}

bool Rotor::turn(){
  return contains(++position % 26, notches);
}

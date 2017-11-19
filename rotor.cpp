#include "rotor.h"

Rotor::Rotor(int _position, vector<int> _notches, vector<int> _mappings) {
  position = _position;
  notches = _notches;
  Encoder::mappings = _mappings;
}

int Rotor::get_position(){
  return position;
}

bool Rotor::turn(){
  return contains(++position % 26, notches);
}

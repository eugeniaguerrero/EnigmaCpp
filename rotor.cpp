#include "rotor.h"

Rotor::Rotor(int _position, vector<int> _notches, vector<int> _mappings) {
  position = _position;
  notches = _notches;
  Encoder::mappings = _mappings;
}

int Rotor::get_position(){
  return position;
}

vector<int> Rotor::get_mappings(){
  return Encoder::mappings;
}

bool Rotor::turn(){
  position = (position + 1) % 26;
  return contains(position, notches);
}

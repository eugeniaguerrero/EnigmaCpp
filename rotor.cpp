#include "rotor.h"

Rotor::Rotor(int _position, vector<int> _notches, vector<int> _mappings) {
  position = _position;
  notches = _notches;
  Encoder::mappings = _mappings;
}

int Rotor::encode(int index) {
  return mappings[index];
}

int Rotor::decode(int output) {
  return find_index(output, Encoder::mappings);
}

int Rotor::get_position(){
  return position;
}

vector<int> Rotor::get_mappings(){
  return Encoder::mappings;
}

bool Rotor::turn(){
  return contains(mod(++position, 26), notches);
}

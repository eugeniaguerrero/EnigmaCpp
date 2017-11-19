#include "plugboard.h"

using namespace std;

Plugboard::Plugboard(vector<int> _mappings) {
  Encoder::mappings = _mappings;
}
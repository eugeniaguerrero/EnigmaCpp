#include "reflector.h"

Reflector::Reflector(vector<int> _mappings) {
	Encoder::mappings = _mappings;
}

vector<int> Reflector::get_mappings() {
	return Encoder::mappings;
}

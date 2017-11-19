#include "encoder.h"

int Encoder::encode(int input) {
  for (size_t i = 0; i < mappings.size(); i++){
    if (mappings[i] == input && i % 2 == 0){
      return mappings[i + 1];
    } else if (mappings[i] == input && i % 2 != 0){
      return mappings[i - 1];
    }
  }
  return input;
}

vector<int> Encoder::get_mappings() {
  return mappings;
}

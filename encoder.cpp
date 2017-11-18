#include "encoder.h"

int Encoder::encode(int input) {
  for (size_t i = 0; i < mappings.size(); i++){
    if (mappings[i] == input && i % 2 == 0){
      return input = mappings[i + 1];
    } else if (mappings[i] == input && i % 2 != 0){
      return input = mappings[i - 1];
    }
  }
  return input;
}

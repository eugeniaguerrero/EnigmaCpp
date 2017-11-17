#include "utils.h"

// size of numbers array needs to be explicit to get start and end of array
bool contains(int elem, vector<int> mappings){
  for (int i = 0; i < mappings.size(); i++) {
    if (mappings[i] == elem) {
      return true;
    }
  }
  return false;
}

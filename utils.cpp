#include "utils.h"

// size of numbers array needs to be explicit to get start and end of array
bool contains(int elem, vector<int> mappings){
  for (size_t i = 0; i < mappings.size(); i++) {
    if (mappings[i] == elem) {
      return true;
    }
  }
  return false;
}

void print_vector(vector<int> mappings) {
  cout << "[ ";
  for (size_t i = 0; i < mappings.size(); i++) {
    cout << mappings[i] << " ";
  }
  cout << "]" << endl;
}

// mathematical version of modulus function
int mod(int k, int n) {
    return ((k %= n) < 0) ? k + n : k;
}

int find_index(int value, vector<int> values) {
  for (size_t i = 0; i < values.size(); i++) {
    if (value == values[i]) {
      return i;
    }
  }
  return -1;
}
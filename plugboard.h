#ifndef PLUGBOARD_H
#define PLUGBOARD_H

#include <iostream>
#include <vector>
#include "encoder.h"
#include "utils.h"

using namespace std;

class Plugboard: public Encoder {
  
  private:
    vector<int> mappings;

  public:
    // allows for accessing the encode and decode methods inside the plugboard class
    // both functions return the input if not contained in the configuration mappings array
    // else they return the mapping of that number
    Plugboard() {};
    Plugboard(vector<int> _mappings);

};

#endif

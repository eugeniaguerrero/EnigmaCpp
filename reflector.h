#ifndef REFLECTOR_H
#define REFLECTOR_H

#include <iostream>
#include <vector>
#include "encoder.h"

using namespace std;

class Reflector: public Encoder {
  private:
    vector<int> mappings;
  public:
    Reflector() {};
    Reflector(vector<int> _mappings);

};

#endif

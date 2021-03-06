#ifndef REFLECTOR_H
#define REFLECTOR_H

#include <vector>
#include "encoder.h"

using namespace std;

class Reflector: public Encoder {

  protected:
    vector<int> mappings;

  public:
    Reflector() {};
    Reflector(vector<int> _mappings);
    vector<int> get_mappings();

};

#endif

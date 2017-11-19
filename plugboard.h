#ifndef PLUGBOARD_H
#define PLUGBOARD_H

#include <vector>
#include "encoder.h"
#include "utils.h"

using namespace std;

class Plugboard: public Encoder {

  public:
    Plugboard() { };
    Plugboard(vector<int> _mappings);

};

#endif

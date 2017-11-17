#ifndef ROTOR_H
#define ROTOR_H

#include "encoder.h"
#include <vector>
using namespace std;

class Rotor: public Encoder {

  private:
    int position;
    vector<int> notches;
    vector<int> mappings;

  public:
    Rotor(int _position, vector<int> _notches, vector<int> _mappings);
    vector<int> get_notches(int notches);

};

#endif

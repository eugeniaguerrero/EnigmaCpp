#ifndef ROTOR_H
#define ROTOR_H

#include <vector>
#include "encoder.h"
#include "utils.h"

using namespace std;

class Rotor: public Encoder {

  private:
    int position;  // number of turns anti-clockwise from the absolute rotor
    vector<int> notches;

  public:
    Rotor(int _position, vector<int> _notches, vector<int> _mappings);
    virtual int encode(int) override;
    vector<int> get_mappings();
    int get_position();
    int decode(int);
    bool turn();  // increments the position and checks whether it is contained in the mappings of the rotor

};

#endif

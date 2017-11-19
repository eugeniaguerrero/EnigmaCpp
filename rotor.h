#ifndef ROTOR_H
#define ROTOR_H

#include <vector>
#include "encoder.h"
#include "utils.h"

using namespace std;

class Rotor: public Encoder {

  private:
    int position;
    vector<int> notches;
    
  protected:
    vector<int> mappings;

  public:
    Rotor(int _position, vector<int> _notches, vector<int> _mappings);
    vector<int> get_notches(int notches);
    int get_position();
    bool turn();  // increments the position and checks whether it is contained in the mappings of the rotor

};

#endif

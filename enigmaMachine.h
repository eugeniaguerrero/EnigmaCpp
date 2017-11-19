#ifndef ENIGMA_MACHINE_H
#define ENIGMA_MACHINE_H

#include <vector>
#include <iostream>
#include "encoder.h"
#include "plugboard.h"
#include "rotor.h"
#include "reflector.h"
#include "utils.h"

using namespace std;

class EnigmaMachine: public Encoder {

  private:
    Plugboard plugboard;
    vector<Rotor> rotors;
    Reflector reflector;
    void turn_rotors();
    void turn_rotors_helper(int i);
    int mod(int k, int n);

  public:
    EnigmaMachine(Plugboard &pb, vector<Rotor> &rots, Reflector &rf): plugboard(pb), rotors(rots), reflector(rf) {}
    virtual int encode(int) override;

};

#endif

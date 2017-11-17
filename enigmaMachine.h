#ifndef ENIGMA_MACHINE_H
#define ENIGMA_MACHINE_H

#include <vector>
#include "encoder.h"
#include "plugboard.h"
#include "rotor.h"
#include "reflector.h"

using namespace std;

class EnigmaMachine: public Encoder {

  private:
    Plugboard plugboard;
    vector<Rotor> rotors;
    Reflector reflector;

  public:
    EnigmaMachine(Plugboard, vector<Rotor>, Reflector);
    virtual int encode(int) override;

};

#endif

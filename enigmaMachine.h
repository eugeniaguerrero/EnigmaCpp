#ifndef ENIGMA_MACHINE_H
#define ENIGMA_MACHINE_H

#include <vector>

#include "plugboard.h"
#include "rotor.h"
#include "reflector.h"

class EnigmaMachine {

  private:
    Plugboard plugboard;
    std::vector<Rotor> rotors;
    Reflector reflector;

  public:
    EnigmaMachine(Plugboard, std::vector<Rotor>, Reflector);
    int encode(int);
    int decode(int);

};

#endif

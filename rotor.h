#ifndef ROTOR_H
#define ROTOR_H

#include "encoder.h"

class Rotor: public Encoder {

  private:
    int encode(int input);
    int decode(int input);

};

#endif

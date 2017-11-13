#ifndef ROTOR_H
#define ROTOR_H

#include "encoder.h"

class Rotor: public Encoder {

  public:
    int encode(int input);
    int decode(int input);

};

#endif

#ifndef REFLECTOR_H
#define REFLECTOR_H

#include "encoder.h"

class Reflector: public Encoder {

  public:
    int encode(int input);
    int decode(int input);

};

#endif

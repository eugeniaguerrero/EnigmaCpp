#ifndef PLUGBOARD_H
#define PLUGBOARD_H

#include "encoder.h"

class Plugboard: public Encoder {

  private:
    int encode(int input);
    int decode(int input);

};

#endif

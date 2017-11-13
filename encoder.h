#ifndef ENCODER_H
#define ENCODER_H

class Encoder {

  virtual int encode(int input) = 0;
  virtual int decode(int input) = 0;

};

#endif

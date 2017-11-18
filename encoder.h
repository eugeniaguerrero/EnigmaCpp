#ifndef ENCODER_H
#define ENCODER_H

#include <vector>
using namespace std;

class Encoder {

  protected: // can never be accessed outside of its child classes
    vector<int> mappings;
    Encoder() {};

  public:
    virtual int encode(int input);

};

#endif

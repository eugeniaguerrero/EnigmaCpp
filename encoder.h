#ifndef ENCODER_H
#define ENCODER_H

#include <vector>
using namespace std;

class Encoder {

  private:
    vector<int> mappings;

  // can never be accessed outside of its child classes
  protected:
    Encoder() {};

  public:
    virtual int encode(int input);

};

#endif

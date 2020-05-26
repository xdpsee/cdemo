#ifndef __CDEMO_EQUALIZER_H
#define __CDEMO_EQUALIZER_H

#include <cstdlib>

typedef struct Gain {

    int band;

    float value;

}Gain;

class Equalizer {

public:
    virtual void enable(bool enable) = 0;

    virtual bool update(int band, float gain) = 0;

    virtual bool update(Gain gains[], size_t num) = 0;

};

#endif
//
// Created by zhenhui on 2020/5/25.
// Copyright (c) 2020 zhenhui. All rights reserved.
//

#ifndef CDEMO_EQ10BANDSFX_H
#define CDEMO_EQ10BANDSFX_H


#include "bassfx.h"
#include "setting.h"
#include "equalizer.h"

class Equalizer10bandsFX : public Equalizer {

public:
    Equalizer10bandsFX(HSTREAM stream);

    virtual ~Equalizer10bandsFX();

    void enable(bool enable) override;

    bool update(int band, float gain) override;

    bool update(Gain gains[], size_t num) override;

private:
    HSTREAM _stream;
    HFX _handles[NUM_BANDS] = {0};
    const float _fCenters[NUM_BANDS] = {32, 64, 125, 250, 500, 1000, 2000, 4000, 8000, 16000};
    float _fGains[NUM_BANDS] = {0};
    bool _enabled;

    void setup();

    void tearDown();

    void updateAll();
};

#endif //CDEMO_EQ10BANDSFX_H


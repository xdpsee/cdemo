//
// Created by zhenhui on 2020/5/25.
// Copyright (c) 2020 zhenhui. All rights reserved.
//

#ifndef __EQ10BANDSFX_H
#define __EQ10BANDSFX_H


#include "bass.h"
#include "bass_fx.h"
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
    void setup();

    void tearDown();

    void updateAll();

private:
    HSTREAM _stream;
    HFX _handles[NUM_BANDS] = {0};
    BASS_DX8_PARAMEQ _params[NUM_BANDS];
    std::atomic<bool> _enabled;
};

#endif



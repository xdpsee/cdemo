//
// Created by zhenhui on 2020/5/26.
// Copyright (c) 2020 zhenhui. All rights reserved.
//

#ifndef CDEMO_REVERBFX_H
#define CDEMO_REVERBFX_H


#include "reverb.h"
#include "bass.h"

class ReverbFX : public Reverb {

public:
    ReverbFX(HSTREAM stream);

    virtual ~ReverbFX();

public:
    void enable(bool enable) override;

    void updateInGain(float inGain) override;

    void updateReverbMix(float reverbMix) override;

    void updateReverbTime(float reverbTime) override;

    void updateHighFreqRTRatio(float highFreqRTRatio) override;

private:
    void setup();

    void tearDown();

private:
    HSTREAM _stream;
    HFX _handle;
    bool _enabled;
    BASS_DX8_REVERB _reverb;
};

#endif //CDEMO_REVERBFX_H

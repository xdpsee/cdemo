//
// Created by zhenhui on 2020/5/25.
// Copyright (c) 2020 zhenhui. All rights reserved.
//

#ifndef CDEMO_EQ10BANDS_H
#define CDEMO_EQ10BANDS_H


#include "bassfx.h"
#include "setting.h"

class Equalizer10bands {

public:
    Equalizer10bands(HSTREAM stream);

    virtual ~Equalizer10bands();

    bool update(EQSetting* setting);

private:
    HSTREAM _stream;
    HFX _handles[NUM_BANDS] = {0};
    bool _enabled;

    void init();

    void clear();
};

#endif //CDEMO_EQ10BANDS_H


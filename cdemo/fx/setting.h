//
// Created by zhenhui on 2020/5/25.
// Copyright (c) 2020 zhenhui. All rights reserved.
//

#ifndef CDEMO_SETTING_H
#define CDEMO_SETTING_H

#include <cstdio>

#define NUM_BANDS 10

class EQSetting {
public:
    EQSetting() {
    }

    inline void setEnabled(bool enable) {
        _enabled = enable;
    }

    inline bool enabled() {
        return _enabled;
    }

    inline int bands() {
        return _bands;
    }

    const float *gains() const {
        return _gains;
    }

    void setGain(int band, float gain) {
        if (band >= 0 && band < NUM_BANDS) {
            _gains[band] = gain;
        }
    }

private:
    bool _enabled;
    int _bands;
    float _gains[NUM_BANDS] = {0};
};

#endif //CDEMO_SETTING_H

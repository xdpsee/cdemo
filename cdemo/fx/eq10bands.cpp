//
// Created by zhenhui on 2020/5/25.
// Copyright (c) 2020 zhenhui. All rights reserved.
//

#include <iostream>
#include "eq10bands.h"
#include "utility.h"

Equalizer10bands::Equalizer10bands(HSTREAM stream) : _stream(stream) {

}

Equalizer10bands::~Equalizer10bands() {
    clear();
}

bool Equalizer10bands::update(EQSetting *setting) {

    if (!setting) {
        LOG("eq setting shouldn't be null");
        return false;
    }

    if (setting->enabled()) {
        init();

        BASS_DX8_PARAMEQ param;
        param.fBandwidth = 16;

        float fCenters[NUM_BANDS] = {32, 64, 125, 250, 500, 1000, 2000, 4000, 8000, 16000};

        BASS_ChannelLock(_stream, TRUE);
        for (int i = 0; i < NUM_BANDS; ++i) {
            param.fCenter = fCenters[i];
            param.fGain = setting->gains()[i];
            BASS_FXSetParameters(_handles[i], &param);
        }
        BASS_ChannelLock(_stream, FALSE);
    } else {
        clear();
    }

    return true;
}

void Equalizer10bands::init() {
    _handles[0] = BASS_ChannelSetFX(_stream, BASS_FX_DX8_PARAMEQ, 0);
    _handles[1] = BASS_ChannelSetFX(_stream, BASS_FX_DX8_PARAMEQ, 0);
    _handles[2] = BASS_ChannelSetFX(_stream, BASS_FX_DX8_PARAMEQ, 0);
    _handles[3] = BASS_ChannelSetFX(_stream, BASS_FX_DX8_PARAMEQ, 0);
    _handles[4] = BASS_ChannelSetFX(_stream, BASS_FX_DX8_PARAMEQ, 0);
    _handles[5] = BASS_ChannelSetFX(_stream, BASS_FX_DX8_PARAMEQ, 0);
    _handles[6] = BASS_ChannelSetFX(_stream, BASS_FX_DX8_PARAMEQ, 0);
    _handles[7] = BASS_ChannelSetFX(_stream, BASS_FX_DX8_PARAMEQ, 0);
    _handles[8] = BASS_ChannelSetFX(_stream, BASS_FX_DX8_PARAMEQ, 0);
    _handles[9] = BASS_ChannelSetFX(_stream, BASS_FX_DX8_PARAMEQ, 0);
}

void Equalizer10bands::clear() {
    BASS_ChannelLock(_stream, TRUE);
    for (int i = 0; i < NUM_BANDS; ++i) {
        HFX h = _handles[i];
        if (h) {
            BASS_ChannelRemoveFX(_stream, _handles[i]);
            _handles[i] = 0;
        }
    }
    BASS_ChannelLock(_stream, FALSE);
}
//
// Created by zhenhui on 2020/5/25.
// Copyright (c) 2020 zhenhui. All rights reserved.
//

#include <iostream>
#include "eq10bands.h"

Equalizer10bands::Equalizer10bands(HSTREAM stream) : _stream(stream) {

}

Equalizer10bands::~Equalizer10bands() {
    tearDown();
}

void Equalizer10bands::setup() {
    if (!_enabled) {
        BASS_ChannelLock(_stream, TRUE);
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
        _enabled = true;
        BASS_ChannelLock(_stream, FALSE);
    }
}

void Equalizer10bands::tearDown() {
    BASS_ChannelLock(_stream, TRUE);
    for (int i = 0; i < NUM_BANDS; ++i) {
        HFX h = _handles[i];
        if (h) {
            BASS_ChannelRemoveFX(_stream, _handles[i]);
            _handles[i] = 0;
        }
    }
    _enabled = false;
    BASS_ChannelLock(_stream, FALSE);
}

void Equalizer10bands::enable(bool enable) {

    if (_enabled == enable) {
        return;
    }

    if (enable) {
        setup();
        updateAll();
    } else {
        tearDown();
    }
}

bool Equalizer10bands::update(int band, float gain) {

    if (band < 0 || band >= NUM_BANDS || !_enabled) {
        return false;
    }

    _fGains[band] = gain;
    if (_handles[band] != 0) {
        BASS_DX8_PARAMEQ param;
        param.fBandwidth = 16;
        param.fCenter = _fCenters[band];
        param.fGain = gain;
        return TRUE == BASS_FXSetParameters(_handles[band], &param);
    }

    return false;
}

bool Equalizer10bands::update(Gain gains[], size_t num) {

    for (int i = 0; i < num; ++i) {
        if (!update(gains[i].band, gains[i].value)) {
            return false;
        }
    }

    return true;
}

void Equalizer10bands::updateAll() {

    BASS_DX8_PARAMEQ param;
    param.fBandwidth = 16;
    for (int i = 0; i < NUM_BANDS; ++i) {
        param.fCenter = _fCenters[i];
        param.fGain = _fGains[i];
        if (_handles[i] != 0) {
            BASS_FXSetParameters(_handles[i], &param);
        }
    }
}

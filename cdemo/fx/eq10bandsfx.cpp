//
// Created by zhenhui on 2020/5/25.
// Copyright (c) 2020 zhenhui. All rights reserved.
//

#include <iostream>
#include "eq10bandsfx.h"

static const float fCenters[NUM_BANDS] = {32, 64, 125, 250, 500, 1000, 2000, 4000, 8000, 16000};

Equalizer10bandsFX::Equalizer10bandsFX(HSTREAM stream) : _stream(stream) {

    for (int i = 0; i < NUM_BANDS; ++i) {
        _params[i].fBandwidth = 36;
        _params[i].fCenter = fCenters[i];
        _params[i].fGain = 0;
    }
}

Equalizer10bandsFX::~Equalizer10bandsFX() {
    tearDown();
}

void Equalizer10bandsFX::setup() {
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

void Equalizer10bandsFX::tearDown() {
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

void Equalizer10bandsFX::enable(bool enable) {

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

bool Equalizer10bandsFX::update(int band, float gain) {

    if (band < 0 || band >= NUM_BANDS || !_enabled) {
        return false;
    }

    _params[band].fGain = gain;
    if (_handles[band] != 0) {
        return TRUE == BASS_FXSetParameters(_handles[band], &(_params[band]));
    }

    return false;
}

bool Equalizer10bandsFX::update(Gain gains[], size_t num) {

    for (int i = 0; i < num && _enabled; ++i) {
        if (!update(gains[i].band, gains[i].value)) {
            return false;
        }
    }

    return true;
}

void Equalizer10bandsFX::updateAll() {

    for (int i = 0; i < NUM_BANDS; ++i) {
        if (_handles[i] != 0) {
            BASS_FXSetParameters(_handles[i], &(_params[i]));
        }
    }

}

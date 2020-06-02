//
// Created by zhenhui on 2020/5/26.
// Copyright (c) 2020 zhenhui. All rights reserved.
//

#include "reverbfx.h"
#include "utility.h"

#define DEFAULT_IN_GAIN 0
#define DEFAULT_REVERB_MIX 0
#define DEFAULT_REVERB_TIME 1000
#define DEFAULT_HIGH_FREQ_RT_RATIO 0.001

ReverbFX::ReverbFX(HSTREAM stream)
        : _stream(stream),
          _handle(0),
          _enabled(false) {
    _reverb.fInGain = DEFAULT_IN_GAIN;
    _reverb.fReverbMix = DEFAULT_REVERB_MIX;
    _reverb.fReverbTime = DEFAULT_REVERB_TIME;
    _reverb.fHighFreqRTRatio = DEFAULT_HIGH_FREQ_RT_RATIO;
}

ReverbFX::~ReverbFX() {
    tearDown();
}

void ReverbFX::enable(bool enable) {
    if (_enabled == enable) {
        return;
    }

    if (enable) {
        setup();
        BASS_FXSetParameters(_handle, &_reverb);
    } else {
        tearDown();
    }
}

void ReverbFX::updateInGain(float inGain) {
    BASS_FXGetParameters(_handle, &_reverb);
    _reverb.fInGain = inGain;
    BASS_FXSetParameters(_handle, &_reverb);
}

void ReverbFX::updateReverbMix(float reverbMix) {
    BASS_FXGetParameters(_handle, &_reverb);
    _reverb.fReverbMix = reverbMix;
    BASS_FXSetParameters(_handle, &_reverb);
}

void ReverbFX::updateReverbTime(float reverbTime) {
    BASS_FXGetParameters(_handle, &_reverb);
    _reverb.fReverbTime = reverbTime;
    BASS_FXSetParameters(_handle, &_reverb);
}

void ReverbFX::updateHighFreqRTRatio(float highFreqRTRatio) {
    BASS_FXGetParameters(_handle, &_reverb);
    _reverb.fHighFreqRTRatio = highFreqRTRatio;
    BASS_FXSetParameters(_handle, &_reverb);
}

void ReverbFX::setup() {
    if (!_enabled || !_handle) {
        BASS_ChannelLock(_stream, TRUE);
        _handle = BASS_ChannelSetFX(_stream, BASS_FX_DX8_REVERB, 1);
        _enabled = true;
        BASS_ChannelLock(_stream, FALSE);
    }
}

void ReverbFX::tearDown() {
    BASS_ChannelLock(_stream, TRUE);
    HFX h = _handle;
    if (h) {
        BASS_ChannelRemoveFX(_stream, h);
        _handle = 0;
    }
    _enabled = false;
    BASS_ChannelLock(_stream, FALSE);
}


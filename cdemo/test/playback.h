//
// Created by zhenhui on 2020/5/21.
// Copyright (c) 2020 zhenhui. All rights reserved.
//

#ifndef CDEMO_PLAYBACK_H
#define CDEMO_PLAYBACK_H

#include "setting.h"
#include "collection.h"
#include "equalizer.h"
#include "reverb.h"

class Playback {

public:
    virtual bool open(MediaItem *media, bool start, bool fadeIn) = 0;

    virtual bool play(bool fadeIn) = 0;

    virtual bool pause() = 0;

    virtual void stop() = 0;

    virtual float volume() = 0;

    virtual bool setVolume(float volume) = 0;

    virtual double duration() = 0;

    virtual double position() = 0;

    virtual bool setPosition(double pos) = 0;

    virtual MediaCollection *queue() = 0;

    virtual Equalizer *equalizer() = 0;

    virtual Reverb* reverb() = 0;

};

#endif //CDEMO_PLAYBACK_H

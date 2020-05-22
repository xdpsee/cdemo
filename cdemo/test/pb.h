//
// Created by zhenhui on 2020/5/21.
// Copyright (c) 2020 zhenhui. All rights reserved.
//

#ifndef CDEMO_PB_H
#define CDEMO_PB_H


class Playback {

public:
    virtual bool open(const char* file, bool start, bool fadeIn) = 0;

    virtual bool play(bool fadeIn) = 0;

    virtual bool pause() = 0;

    virtual void stop() = 0;

    virtual float volume() = 0;

    virtual bool setVolume(float volume) = 0;

    virtual double duration() = 0;

    virtual double position() = 0;

    virtual bool setPosition(double pos) = 0;

};

#endif //CDEMO_PB_H

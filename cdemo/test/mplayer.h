//
// Created by zhenhui on 2020/5/21.
// Copyright (c) 2020 zhenhui. All rights reserved.
//

#ifndef CDEMO_MPLAYER_H
#define CDEMO_MPLAYER_H


#include <vector>
#include "playback.h"
#include "stream.h"
#include "streamob.h"
#include "collection.h"
#include "media.h"


class MusicPlayer : Playback {

public:
    MusicPlayer(StreamObserver *observer);

    virtual ~MusicPlayer();

public:
    /**
     * @param file file path or url
     * @param start start
     * @return true or false
     */
    bool open(MediaItem *media, bool start, bool fadeIn) override;

    /**
     * play
     * @return true or false
     */
    bool play(bool fadeIn) override;

    /**
     * pause
     * @return true or false
     */
    bool pause() override;

    /**
     * @deprecated
     * stop
     */
    void stop() override;

    /**
     * current volume
     * @return fail if less than 0, otherwise 0.0~1.0
     */
    float volume() override;

    /**
     * set volume
     * @param volume
     * @return true or false
     */
    bool setVolume(float volume) override;

    /**
     * duration in seconds
     * @return seconds
     */
    double duration() override;

    /**
     * current playback position in seconds
     * @return seconds
     */
    double position() override;

    /**
     * seek to position
     * @param pos
     * @return true or false
     */
    bool setPosition(double pos) override;

    MediaCollection *queue() override;

    Equalizer *equalizer() override;

    Reverb *reverb() override;

private:
    Stream *_stream;
    MediaCollection *_collection;
    StreamObserver *_observer;
};

#endif //CDEMO_MPLAYER_H

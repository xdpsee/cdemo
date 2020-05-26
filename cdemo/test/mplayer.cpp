//
// Created by zhenhui on 2020/5/21.
// Copyright (c) 2020 zhenhui. All rights reserved.
//

#include <iostream>
#include "mplayer.h"
#include "utility.h"

MusicPlayer::MusicPlayer(StreamObserver *observer) : _stream(0), _observer(observer) {
    _collection = new MediaCollection();
    if (_observer == NULL) {
        _observer = new DefaultStreamObserver(this);
    }
}

MusicPlayer::~MusicPlayer() {

    // stop playback

    delete _observer;
    delete _collection;
    _collection = NULL;
    _observer = NULL;
}

bool MusicPlayer::open(MediaItem *media, bool start, bool fadeIn) {

    if (_stream) {
        _stream->close(!_stream->eof());
    }

    _stream = new Stream(_observer);
    if (_stream->open(media->path())) {
        if (start) {
            return _stream->play(fadeIn);
        }

        return true;
    }

    return false;
}

bool MusicPlayer::play(bool fadeIn) {
    return _stream && _stream->play(fadeIn);
}

bool MusicPlayer::pause() {
    return _stream && _stream->pause();
}

void MusicPlayer::stop() {
    if (_stream) {
        _stream->close(false);
    }
}

float MusicPlayer::volume() {

    float volume = BASS_GetVolume();
    if (volume < 0) {
        LOG_ERROR("get volume");
    }

    return volume;
}

bool MusicPlayer::setVolume(float volume) {

    if (!BASS_SetVolume(volume)) {
        LOG_ERROR("set volume");
        return false;
    }

    return true;
}

double MusicPlayer::duration() {
    if (_stream) {
        return _stream->duration();
    }

    return -1;
}

double MusicPlayer::position() {
    if (_stream) {
        return _stream->position();
    }

    return -1;
}

bool MusicPlayer::setPosition(double pos) {
    return _stream && _stream->setPosition(pos);
}

MediaCollection *MusicPlayer::queue() {
    return _collection;
}

Equalizer *MusicPlayer::equalizer() {
    if (_stream) {
        return _stream->equalizer();
    }

    return NULL;
}

Reverb *MusicPlayer::reverb() {
    if (_stream) {
        return _stream->reverb();
    }

    return NULL;
}








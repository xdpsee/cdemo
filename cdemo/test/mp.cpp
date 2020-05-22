//
// Created by zhenhui on 2020/5/21.
// Copyright (c) 2020 zhenhui. All rights reserved.
//

#include "mp.h"
#include "utils.h"

bool MusicPlayer::open(const char *file, bool start, bool fadeIn) {

    if (_stream) {
        _stream->close(!_stream->eof());
    }

    _stream = new Stream();
    if (_stream->open(file)) {
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



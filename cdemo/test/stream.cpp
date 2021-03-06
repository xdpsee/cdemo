#include <iostream>
#include <thread>
#include "stream.h"
#include "streamob.h"
#include "utility.h"

#define FADING_DURATION 2000

void Stream::deviceFailSyncProc(HSYNC handle, DWORD channel, DWORD data, void *opaque) {

    Stream *stream = (Stream *) opaque;

    std::cout << "[tid = " << std::this_thread::get_id() << "] " << "device failed, stream = " << channel << std::endl;

}

void Stream::streamEOFSyncProc(HSYNC handle, DWORD channel, DWORD data, void *opaque) {

    Stream *stream = (Stream *) opaque;

    std::cout << "[tid = " << std::this_thread::get_id() << "] " << "stream eof, stream = " << channel << std::endl;

    stream->_eof = true;
    stream->notifyStreamEof();
}

void Stream::streamFadeoutSyncProc(HSYNC handle, DWORD channel, DWORD data, void *opaque) {

    Stream *stream = (Stream *) opaque;
    std::cout << "[tid = " << std::this_thread::get_id() << "] " << "stream fade-out finish, stream = " << channel
              << std::endl;

    stream->doClose();
}

void Stream::streamFadeInSyncProc(HSYNC handle, DWORD channel, DWORD data, void *opaque) {
    Stream *stream = (Stream *) opaque;
    std::cout << "[tid = " << std::this_thread::get_id() << "] " << "stream fade-in finish, stream = " << channel
              << std::endl;
}

void Stream::streamAboutFinishSyncProc(HSYNC handle, DWORD channel, DWORD data, void *opaque) {
    std::cout << "[tid = " << std::this_thread::get_id() << "] " << "stream about to finish, stream = " << channel
              << std::endl;
    BASS_ChannelSlideAttribute(channel, BASS_ATTRIB_VOL, -1, FADING_DURATION);
}

void Stream::streamFreeSyncProc(HSYNC handle, DWORD channel, DWORD data, void *opaque) {
    std::cout << "[tid = " << std::this_thread::get_id() << "] " << "stream free, stream = " << channel << std::endl;
}

Stream::Stream(StreamObserver *observer)
        : _observer(observer), _stream(0), _eof(FALSE) {
}

Stream::~Stream() {
}

bool Stream::open(const char *file) {

    _stream = BASS_StreamCreateFile(FALSE, file, 0, 0, BASS_STREAM_PRESCAN | BASS_STREAM_AUTOFREE);

    if (!_stream) {
        notifyStreamError();
        return false;
    }

    if (_stream) {
        std::cout << "[tid = " << std::this_thread::get_id() << "] " << "stream open, stream = " << _stream
                  << std::endl;
        setupSync();
        loadFX();
    }

    return _stream != 0;
}

void Stream::close(bool fadeout) {

    if (_stream) {
        bool needFadeout;
        DWORD ret = BASS_ChannelIsActive(_stream);
        if (BASS_ACTIVE_PLAYING == ret && fadeout) {
            if (BASS_ChannelSlideAttribute(_stream, BASS_ATTRIB_VOL, -1, FADING_DURATION)) {
                HSYNC sync = BASS_ChannelSetSync(_stream, BASS_SYNC_SLIDE | BASS_SYNC_ONETIME, 0, streamFadeoutSyncProc, this);
                needFadeout = sync != 0;
            } else {
                needFadeout = false;
            }
        } else {
            needFadeout = false;
        }

        if (!needFadeout) {
            doClose();
        }
    }
}

bool Stream::play(bool fadeIn) {
    BOOL ret = BASS_ChannelPlay(_stream, FALSE);
    if (!ret) {
        int err = BASS_ErrorGetCode();
        PrintError("stream play", err);
        if (BASS_ERROR_START == err) {
            ret = BASS_Start();
        }
    }

    if (ret && fadeIn) {
        doFadeIn();
    }

    return TRUE == ret;
}

bool Stream::pause() {
    BOOL ret = BASS_ChannelPause(_stream);
    if (!ret) {
        int err = BASS_ErrorGetCode();
        PrintError("stream pause", err);
        return BASS_ERROR_ALREADY == err;
    }

    return true;
}

double Stream::duration() {

    QWORD len = BASS_ChannelGetLength(_stream, BASS_POS_BYTE); // the length in bytes
    double time = BASS_ChannelBytes2Seconds(_stream, len); // the length in seconds

    return time;
}

double Stream::position() {

    QWORD len = BASS_ChannelGetPosition(_stream, BASS_POS_BYTE); // the length in bytes
    double time = BASS_ChannelBytes2Seconds(_stream, len); // the length in seconds
    return time;
}

bool Stream::setPosition(double pos) {

    QWORD q = BASS_ChannelSeconds2Bytes(_stream, pos);
    if (q < 0) {
        LOG_ERROR("stream set position, seconds to bytes");
        return false;
    }

    BOOL ret = BASS_ChannelSetPosition(_stream, q, BASS_POS_BYTE);
    if (!ret) {
        LOG_ERROR("stream set position, set");
    }
    return TRUE == ret;
}


bool Stream::eof() {
    return _eof;
}

bool Stream::playing() {

    return _stream && BASS_ChannelIsActive(_stream) == BASS_ACTIVE_PLAYING;

}

bool Stream::crossfading() {

    return _stream && BASS_ChannelIsSliding(_stream, BASS_ATTRIB_VOL);

}

void Stream::setupSync() {
    BASS_ChannelSetSync(_stream, BASS_SYNC_DEV_FAIL | BASS_SYNC_ONETIME, 0, deviceFailSyncProc, this);
    BASS_ChannelSetSync(_stream, BASS_SYNC_END | BASS_SYNC_ONETIME, 0, streamEOFSyncProc, this);
    BASS_ChannelSetSync(_stream, BASS_SYNC_FREE | BASS_SYNC_MIXTIME | BASS_SYNC_ONETIME, 0, streamFreeSyncProc, this);

    QWORD bytes = BASS_ChannelGetLength(_stream, BASS_POS_BYTE);
    QWORD fadeLen = BASS_ChannelSeconds2Bytes(_stream, FADING_DURATION / 1000.0);
    QWORD param = bytes - fadeLen;
    BASS_ChannelSetSync(_stream, BASS_SYNC_POS | BASS_SYNC_ONETIME, param, streamAboutFinishSyncProc, this);
}

void Stream::loadFX() {
    _equalizer = new Equalizer10bandsFX(_stream);
    _reverb = new ReverbFX(_stream);
    // TODO: other fx
}

Equalizer *Stream::equalizer() {

    if (!_eof && _stream && _equalizer) {
        return _equalizer;
    }

    return NULL;
}

Reverb *Stream::reverb() {

    if (!_eof && _stream && _reverb) {
        return _reverb;
    }

    return NULL;
}

void Stream::notifyStreamError() {

    LOG_ERROR("stream open failed");

    if (_observer) {
        _observer->onStreamError();
    }
}

void Stream::notifyStreamEof() {

    if (_observer) {
        _observer->onStreamCompleted();
    }
}

void Stream::doFadeIn() {
    BASS_ChannelSetAttribute(_stream, BASS_ATTRIB_VOL, 0);
    BASS_ChannelSlideAttribute(_stream, BASS_ATTRIB_VOL, 1, FADING_DURATION);
    BASS_ChannelSetSync(_stream, BASS_SYNC_SLIDE | BASS_SYNC_ONETIME, 0, streamFadeInSyncProc, this);
}

void Stream::doClose() {
    BOOL stopped = BASS_ChannelStop(_stream);
    if (!stopped) {
        LOG_ERROR("stream stop");
    }

    delete _equalizer;
    delete _reverb;

    std::cout << "[tid = " << std::this_thread::get_id() << "] " << "stream closed, stream = " << _stream
              << std::endl;

    _equalizer = NULL;
    _reverb = NULL;
    _stream = 0;
    _observer = NULL;

    delete this;
}
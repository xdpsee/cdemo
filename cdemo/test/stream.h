//
// Created by zhenhui on 2020/5/21.
// Copyright (c) 2020 zhenhui. All rights reserved.
//

#ifndef CDEMO_STREAM_H
#define CDEMO_STREAM_H

#include "bass.h"

class Stream {

public:
    Stream();
    ~Stream();

    bool open(const char* file);

    void close(bool fadeout);

    bool play(bool fadeIn);

    bool pause();

    double duration();

    double position();

    bool setPosition(double pos);

    bool eof();

    bool crossfading();

private:
    static void deviceFailSyncProc(HSYNC handle, DWORD channel, DWORD data, void* opaque);

    static void streamEOFSyncProc(HSYNC handle, DWORD channel, DWORD data, void* opaque);

    static void streamFadeoutSyncProc(HSYNC handle, DWORD channel, DWORD data, void *opaque);

    static void streamFadeInSyncProc(HSYNC handle, DWORD channel, DWORD data, void *opaque);

    void doClose();
private:
    HSTREAM _stream;
    volatile BOOL _eof;

};


#endif //CDEMO_STREAM_H

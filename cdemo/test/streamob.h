//
// Created by zhenhui on 2020/5/25.
// Copyright (c) 2020 zhenhui. All rights reserved.
//

#ifndef CDEMO_STREAMOB_H
#define CDEMO_STREAMOB_H


#include "playback.h"

class StreamObserver {

public:
    virtual void onStreamError() = 0;
    virtual void onStreamCompleted() = 0;

};

class DefaultStreamObserver : public StreamObserver {

public:
    DefaultStreamObserver(Playback* playback);
    virtual ~DefaultStreamObserver();


    // StreamObserver implementation
    void onStreamError() override;

    void onStreamCompleted() override;

private:
    Playback* _playback;
};

#endif //CDEMO_STREAMOB_H

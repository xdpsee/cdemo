//
// Created by zhenhui on 2020/5/25.
// Copyright (c) 2020 zhenhui. All rights reserved.
//

#include <iostream>
#include <thread>
#include "streamob.h"

DefaultStreamObserver::DefaultStreamObserver(Playback *playback)
        : _playback(playback) {

}

DefaultStreamObserver::~DefaultStreamObserver() {

}

void DefaultStreamObserver::onStreamCompleted() {

    std::cout << "[tid = " << std::this_thread::get_id() << "] " << "StreamObserver::onStreamCompleted" << std::endl;

    MediaCollection *mediaCollection = _playback->queue();
    MediaItem *mediaItem = mediaCollection->next();
    if (mediaItem) {
        _playback->open(mediaItem, true, true);
    }
}

void DefaultStreamObserver::onStreamError() {
    std::cout << "[tid = " << std::this_thread::get_id() << "] " << "StreamObserver::onStreamError" << std::endl;

    MediaCollection *mediaCollection = _playback->queue();
    MediaItem *mediaItem = mediaCollection->next();
    if (mediaItem) {
        _playback->open(mediaItem, true, true);
    }

}




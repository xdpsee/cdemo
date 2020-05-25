//
// Created by zhenhui on 2020/5/25.
// Copyright (c) 2020 zhenhui. All rights reserved.
//

#include "collection.h"

MediaCollection::MediaCollection()
        : _current(-1) {

}

MediaCollection::~MediaCollection() {
    const size_t count = _items.size();
    for (size_t i = 0; i < count; ++i) {
        MediaItem* item = _items.at(i);
        delete item;
    }
    _items.clear();
    _current = -1;
}

MediaItem* MediaCollection::next() {
    const size_t count = _items.size();
    if (count == 0) {
        return NULL;
    }

    _current += 1;
    if (_current >= count) {
        _current = 0;
    }

    return _items.at(_current);
}

void::MediaCollection::addMedia(MediaItem *mediaItem) {
    _items.push_back(mediaItem);
}


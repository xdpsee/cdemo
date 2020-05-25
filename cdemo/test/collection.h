//
// Created by zhenhui on 2020/5/25.
// Copyright (c) 2020 zhenhui. All rights reserved.
//

#ifndef CDEMO_COLLECTION_H
#define CDEMO_COLLECTION_H

#include <vector>
#include "media.h"

class MediaCollection {

public:
    MediaCollection();
    virtual ~MediaCollection();

public:
    MediaItem* next();

    void addMedia(MediaItem* mediaItem);

private:
    std::vector<MediaItem*> _items;
    int _current;
};


#endif //CDEMO_COLLECTION_H

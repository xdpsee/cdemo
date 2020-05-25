//
// Created by zhenhui on 2020/5/25.
// Copyright (c) 2020 zhenhui. All rights reserved.
//

#include <string.h>
#include <cstdlib>
#include "media.h"

MediaItem::MediaItem(const char *path) : _path(path) {
    if (path != NULL) {
        _path = strdup(path);
    }
}

MediaItem::~MediaItem() {
    if (_path != NULL) {
        free((void*)_path);
        _path = NULL;
    }
}

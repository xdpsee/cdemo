//
// Created by zhenhui on 2020/5/25.
// Copyright (c) 2020 zhenhui. All rights reserved.
//

#ifndef CDEMO_MEDIA_H
#define CDEMO_MEDIA_H


class MediaItem {

public:
    MediaItem(const char *path);

    virtual ~MediaItem();

    const char* path() { return _path; }


private:
    const char *_path;
};

#endif //CDEMO_MEDIA_H

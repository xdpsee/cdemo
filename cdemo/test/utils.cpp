//
// Created by zhenhui on 2020/5/21.
// Copyright (c) 2020 zhenhui. All rights reserved.
//

#include <iostream>
#include "utils.h"
#include "bass.h"

const char *GetErrorDescription(int error) {

    switch (error)
    {
        case BASS_OK:
            return "all is OK";
        case BASS_ERROR_MEM:
            return "memory error";
        case BASS_ERROR_FILEOPEN:
            return "can't open the file";
        case BASS_ERROR_DRIVER:
            return "can't find a free/valid driver";
        case BASS_ERROR_BUFLOST:
            return "the sample buffer was lost";
        case BASS_ERROR_HANDLE:
            return "invalid handle";
        case BASS_ERROR_FORMAT:
            return "unsupported sample format";
        case BASS_ERROR_POSITION:
            return "invalid position";
        case BASS_ERROR_INIT:
            return "BASS_Init has not been successfully called";
        case BASS_ERROR_START:
            return "BASS_Start has not been successfully called";
        case BASS_ERROR_ALREADY:
            return "already initialized/paused/whatever";
        case BASS_ERROR_NOCHAN:
            return "can't get a free channel";
        case BASS_ERROR_ILLTYPE:
            return "an illegal type was specified";
        case BASS_ERROR_ILLPARAM:
            return "an illegal parameter was specified";
        case BASS_ERROR_NO3D:
            return "no 3D support";
        case BASS_ERROR_NOEAX:
            return "no EAX support";
        case BASS_ERROR_DEVICE:
            return "illegal device number";
        case BASS_ERROR_NOPLAY:
            return "not playing";
        case BASS_ERROR_FREQ:
            return "illegal sample rate";
        case BASS_ERROR_NOTFILE:
            return "the stream is not a file stream";
        case BASS_ERROR_NOHW:
            return "no hardware voices available";
        case BASS_ERROR_EMPTY:
            return "the MOD music has no sequence data";
        case BASS_ERROR_NONET:
            return "no internet connection could be opened";
        case BASS_ERROR_CREATE:
            return "couldn't create the file";
        case BASS_ERROR_NOFX:
            return "effects are not available";
        case BASS_ERROR_NOTAVAIL:
            return "requested data is not available";
        case BASS_ERROR_DECODE:
            return "the channel is/isn't a 'decoding channel'";
        case BASS_ERROR_DX:
            return "a sufficient DirectX version is not installed";
        case BASS_ERROR_TIMEOUT:
            return "connection timeout";
        case BASS_ERROR_FILEFORM:
            return "unsupported file format";
        case BASS_ERROR_SPEAKER:
            return "unavailable speaker";
        case BASS_ERROR_VERSION:
            return "invalid BASS version (used by add-ons)";
        case BASS_ERROR_CODEC:
            return "codec is not available/supported";
        case BASS_ERROR_ENDED:
            return "the channel/file has ended";
        case BASS_ERROR_BUSY:
            return "the device is busy";
        case BASS_ERROR_UNKNOWN:
        default:
            return "some other mystery problem";
    }

}

void PrintError(const char* prefix, int error) {
    const char* desc = GetErrorDescription(BASS_ErrorGetCode());
    std::cerr << prefix << ": " << error << std::endl;
}
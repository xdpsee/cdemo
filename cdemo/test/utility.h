//
// Created by zhenhui on 2020/5/21.
// Copyright (c) 2020 zhenhui. All rights reserved.
//

#ifndef CDEMO_UTILITY_H
#define CDEMO_UTILITY_H

const char* GetErrorDescription(int code);

void PrintError(const char* prefix, int error);

#define LOG_ERROR(prefix) PrintError(prefix, BASS_ErrorGetCode())

#define LOG(msg) std::cout << (msg) << std::endl

#endif //CDEMO_UTILITY_H

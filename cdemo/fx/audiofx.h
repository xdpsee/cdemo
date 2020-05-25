#ifndef __AUDIO_FX_H
#define __AUDIO_FX_H

#include "setting.h"

class AudioFXConfig {

public:
    AudioFXConfig();
    ~AudioFXConfig();

    EQSetting* eq();

private:
    EQSetting *_eqSetting;
};

#endif

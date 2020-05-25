#include "audiofx.h"

AudioFXConfig::AudioFXConfig() {
    _eqSetting = new EQSetting();
}

AudioFXConfig::~AudioFXConfig() {
    delete _eqSetting;
}

EQSetting* AudioFXConfig::eq() {
    return _eqSetting;
}




#ifndef __CDEMO_REVERB_H
#define __CDEMO_REVERB_H

class Reverb {
public:
    virtual void enable(bool enable) = 0;

    /**
     * @param inGain 输入增益, -96 ~ 0, 默认 0
     */
    virtual void updateInGain(float inGain) = 0;

    /**
     * @param reverbMix
     */
    virtual void updateReverbMix(float reverbMix) = 0;

    /**
     * @param reverbTime
     */
    virtual void updateReverbTime(float reverbTime) = 0;

    /**
     * @param highFreqRTRatio
     */
    virtual void updateHighFreqRTRatio(float highFreqRTRatio) = 0;
};

#endif

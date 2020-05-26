#include <iostream>
#include "bass.h"
#include "stream.h"
#include "utility.h"
#include "mplayer.h"
#include "audiofx.h"

static void PrintPluginInfo(HPLUGIN plugin) {

    if (plugin) {
        const BASS_PLUGININFO *info = BASS_PluginGetInfo(plugin); // get the plugin info
        int a;
        for (a = 0; a < info->formatc; a++) { // display the array of formats...
            printf("type=%x name=%s exts=%s\n",
                    info->formats[a].ctype, info->formats[a].name, info->formats[a].exts);
        }
    } else {
        printf("plugin load error : %s\n", GetErrorDescription(BASS_ErrorGetCode()));
    }
}

static void InitPlugins() {
    HPLUGIN ape = BASS_PluginLoad("libbass_ape.dylib", 0);
    PrintPluginInfo(ape);
    HPLUGIN fx = BASS_PluginLoad("libbass_fx.dylib", 0);
    PrintPluginInfo(fx);
}

int main(int argc, const char *argv[]) {

    srand((unsigned int) time(NULL));

    std::cout << "system version: " << BASS_GetVersion() << std::endl;

    if (!BASS_Init(-1, 44100, 0, NULL, NULL)) {
        std::cout << BASS_ErrorGetCode() << std::endl;
        return -1;
    }

    InitPlugins();

    AudioFXConfig audioFxConfig;

    MusicPlayer *player = new MusicPlayer(NULL);
    MediaCollection *mediaCollection = player->queue();
    mediaCollection->addMedia(new MediaItem("/Users/zhenhui/audio_test/za.flac"));
    mediaCollection->addMedia(new MediaItem("/Users/zhenhui/audio_test/pfzl.ape"));
    mediaCollection->addMedia(new MediaItem("/Users/zhenhui/audio_test/bbb.mp4"));
    mediaCollection->addMedia(new MediaItem("/Users/zhenhui/audio_test/张芸京-怎么哭.flac"));
    mediaCollection->addMedia(new MediaItem("/Users/zhenhui/audio_test/杰文.mp3"));
    mediaCollection->addMedia(new MediaItem("/Users/zhenhui/audio_test/Walking in the Cold.m4a"));
    mediaCollection->addMedia(new MediaItem("/Users/zhenhui/audio_test/黄致列-苦海Live.ape"));

    if (!player->open(mediaCollection->next(), true, true)) {
        std::cout << "open media item failed!" << std::endl;
        return -1;
    }

    std::cout << "media duration = " << player->duration() << std::endl;

    char op;
    while (std::cin >> op) {
        switch (op) {
            case 'n': {
                MediaItem *mediaItem = mediaCollection->next();
                if (mediaItem) {
                    player->open(mediaItem, true, true);
                }
            }
                break;
            case 'q': {
                player->stop();
                goto _exit;
            }
                break;
            case 'e': {
                Equalizer *equalizer = player->equalizer();
                if (equalizer) {
                    equalizer->enable(true);
                    equalizer->update(5, -12.0f);
                }
            }
                break;
            case 'r': {
                Equalizer *equalizer = player->equalizer();
                if (equalizer) {
                    equalizer->enable(false);
                }
            }
                break;
            case 't': {
                Reverb *reverb = player->reverb();
                if (reverb) {
                    reverb->enable(true);
                    reverb->updateReverbTime(2400);
                    reverb->updateInGain(5.0f);
                }
            }
                break;
            case 'y': {
                Reverb *reverb = player->reverb();
                if (reverb) {
                    reverb->enable(false);
                }
            }
                break;
            case 'p': {
                if (player->playing()) {
                    player->pause();
                } else {
                    player->play(true);
                }
            }
                break;
            default:
                std::cout << "press 'n' to next, 'q' to exit" << std::endl;
                break;
        }
    }

    _exit:
    delete player;

    BASS_Free();
    BASS_PluginFree(0);

    return 0;
}




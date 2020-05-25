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

int main(int argc, const char *argv[]) {

    srand((unsigned int)time(NULL));

    std::cout << "system version: " << BASS_GetVersion() << std::endl;

    if (!BASS_Init(-1, 44100, 0, NULL, NULL)) {
        std::cout << BASS_ErrorGetCode() << std::endl;
        return -1;
    }

    HPLUGIN h1 = BASS_PluginLoad("libbass_ape.dylib", 0);
    PrintPluginInfo(h1);
    HPLUGIN h2 = BASS_PluginLoad("libtags.dylib", 0);
    PrintPluginInfo(h2);

    AudioFXConfig audioFxConfig;

    MusicPlayer *player = new MusicPlayer(NULL);
    MediaCollection *mediaCollection = player->collection();
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
                MediaItem* mediaItem = mediaCollection->next();
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
                audioFxConfig.eq()->setEnabled(true);
                audioFxConfig.eq()->setGain(0, ((float)rand()/(float)(RAND_MAX)) * 12);
                audioFxConfig.eq()->setGain(1, ((float)rand()/(float)(RAND_MAX)) * 12);
                audioFxConfig.eq()->setGain(2, ((float)rand()/(float)(RAND_MAX)) * 12);
                audioFxConfig.eq()->setGain(3, ((float)rand()/(float)(RAND_MAX)) * 12);
                audioFxConfig.eq()->setGain(4, ((float)rand()/(float)(RAND_MAX)) * 12);
                audioFxConfig.eq()->setGain(5, ((float)rand()/(float)(RAND_MAX)) * 12);
                audioFxConfig.eq()->setGain(6, ((float)rand()/(float)(RAND_MAX)) * 12);
                audioFxConfig.eq()->setGain(7, ((float)rand()/(float)(RAND_MAX)) * 12);
                audioFxConfig.eq()->setGain(8, ((float)rand()/(float)(RAND_MAX)) * 12);
                audioFxConfig.eq()->setGain(9, ((float)rand()/(float)(RAND_MAX)) * 12);
                player->equalize(audioFxConfig.eq());
            }
                break;
            case 'r':{
                audioFxConfig.eq()->setEnabled(false);
                player->equalize(audioFxConfig.eq());
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

    return 0;
}


#include <iostream>
#include <unistd.h>
#include "bass.h"
#include "stream.h"
#include "utils.h"
#include "mp.h"

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

    std::cout << "system version: " << BASS_GetVersion() << std::endl;

    if (!BASS_Init(-1, 44100, 0, NULL, NULL)) {
        std::cout << BASS_ErrorGetCode() << std::endl;
        return -1;
    }

    HPLUGIN h1 = BASS_PluginLoad("libbass_ape.dylib", 0);
    PrintPluginInfo(h1);
    HPLUGIN h2 = BASS_PluginLoad("libtags.dylib", 0);
    PrintPluginInfo(h2);

    MusicPlayer* player = new MusicPlayer();

    if (!player->open("/Users/zhenhui/audio_test/张芸京-怎么哭.flac", true, true)) {
        std::cout << "open file 1 failed!" << std::endl;
        return -1;
    }

    std::cout << "media duration = " << player->duration() << std::endl;

    bool test = true;
    while (true) {
        usleep(100000);
        //std::cout << "current position: " << player->position() << std::endl;
        if (player->position() > 100 && test) {
            test = false;
            if (!player->open("/Users/zhenhui/audio_test/杰文.mp3", true, true)) {
                std::cout << "open file 2 failed!" << std::endl;
            }
        }
    }

    return 0;
}


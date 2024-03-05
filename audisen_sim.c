/**
 * @authors Brun Zelman Fontaine Paul CIR3 Caen
 */

#include <stdio.h>
#include "amp.h"
#include "ams.h"
#include "frame.h"

void test_frame(){
    s_tick tick;
    tick.accent = 1;
    for (int i = 0; i < 4; ++i) {
        tick.note[i] = (i+1)*10;
    }

    s_song song;
    strcpy(song.title, "titre");
    song.tpm = 70;
    song.nTicks = 16;

    char initFrame[INIT_FRAME_MAX_SIZE] = "";
    createInitFrame(song, initFrame);
    printf("%s\n", initFrame);

    char frame[TICK_FRAME_SIZE] = "";
    createTickFrame(tick, frame);
    printf("%s", frame);
}

void test_readAMS(){
    s_song s = readAMS("bohemian_rhapsody.ams");
    int i = 0;
}

void test_createAMS(){
    createAMS("bohemian_rhapsody.txt", "test.ams");
}

int main(){
    test_createAMS();
    return 0;
}
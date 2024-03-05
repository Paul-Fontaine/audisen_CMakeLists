/**
 * @authors Brun Zelman Fontaine Paul CIR3 Caen
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "frame.h"
#include "define.h"

// tested with https://www.scadacore.com/tools/programming-calculators/online-checksum-calculator/
// it works !
void checksum_str(char* frame, char* checksumStr){
    int checksum = 0;
    for(int i=1; i<strlen(frame); i++){
        checksum ^= frame[i];
    }
    sprintf(checksumStr, "%02x", checksum); //02 pour forcer 2 un zéro devant si 1 seul caractere
}

// tested, it works
void createInitFrame(s_song mySong, char* frame){
    //init frame : #Bohemian Rhapsody,144,16*<checksum><CR><LF>
    char myFrame[INIT_FRAME_MAX_SIZE];
    myFrame[0] = '#';
    strcat(myFrame, mySong.title);
    strcat(myFrame,",");

    //conversion du tpm en chaine de caracteres
    char tpm_str[4];
    sprintf(tpm_str, "%d", mySong.tpm);
    strcat(myFrame,tpm_str);

    strcat(myFrame,",");

    //pareil pour nTicks
    char nTicks_str[4];
    sprintf(nTicks_str, "%d", mySong.nTicks);
    strcat(myFrame,nTicks_str);

    // checksum
    char checksumStr[3] = "";
    checksum_str(myFrame, checksumStr);
    strcat(myFrame,"*");
    strcat(myFrame, checksumStr);

    strcat(myFrame,"\r\n");

    strcpy(frame, myFrame);
}

// tested, it works !
void createTickFrame(s_tick myTick, char* frame){
    char myFrame[TICK_FRAME_SIZE] = "";
    myFrame[0] = '#';

    // mode
    strcat(myFrame, "1,");

    // accent
    if (myTick.accent){
        strcat(myFrame, "1");
    } else {
        strcat(myFrame, "0");
    }

    // notes
    char note_str[4]; // ',' + 2 digits
    for (int i = 0; i < 4; ++i) {
        sprintf(note_str, ",%02d", myTick.note[i]);
        strcat(myFrame, note_str);
    }

    // checksum
    char checksumStr[3] = "";
    checksum_str(myFrame, checksumStr);
    strcat(myFrame, "*");
    strcat(myFrame, checksumStr);

    strcat(myFrame, "\r\n");

    strcpy(frame, myFrame);
}

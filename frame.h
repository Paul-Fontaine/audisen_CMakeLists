/**
 * @authors Brun Zelman Fontaine Paul CIR3 Caen
 */

#ifndef AUDISEN2024_FRAME_H
#define AUDISEN2024_FRAME_H

#include "define.h"

#define TICK_FRAME_SIZE 22
#define INIT_FRAME_MAX_SIZE (1+MAX_SIZE_TITLE+12)

#define MODE 1
#define ACC 3
#define N1 5
#define N2 8
#define N3 11
#define N4 14

#define CR 13
#define LF 10

void checksum_str(char* frame, char* checksumStr);

void createInitFrame(s_song mySong, char* frame);
void createTickFrame(s_tick myTick, char* frame);

#endif //AUDISEN2024_FRAME_H
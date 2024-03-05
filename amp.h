/**
 * @authors Brun Zelman Fontaine Paul CIR3 Caen
 */

#ifndef AUDISEN2024_AMP_H
#define AUDISEN2024_AMP_H

#include "define.h"

void lower(char* s);

void replaceWithUnderscores(char* s);

void removeCharAtIndex(char* s, int i);

void removeMultiplesUnderscores(char* s);

void reformat(char* s);

FILE* initAMP(char* filename);

void readAMP(FILE* pf, char * song_filename);

void closeAMP(FILE* pf);

#endif //AUDISEN2024_AMP_H
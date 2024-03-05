/**
 * @authors Brun Zelman Fontaine Paul CIR3 Caen
 */

#ifndef INCLUDE_H
#define INCLUDE_H

//#define _WIN32

#ifndef _WIN32
// LINUX INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

#ifdef _WIN32
// WINDOWS INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

#define MAX_SIZE_TITLE 40
#define MAX_SIZE_PLAYLIST_NAME 100
#define MAX_SIZE_LINE 190
#define MAX_NUMBER_TICKS 999
#define MAX_SONGNAME_SIZE 100

typedef
struct tick{
	int accent;//accentuation du tick (0=Non, 1:Oui)
	int note[4];// Tableau de 4 notes (0 à 60)
}s_tick;

typedef
struct song{
	int tpm;// tick par minutes
	int nTicks;// Nombre de ticks dans le morceau
	char title[MAX_SIZE_TITLE];// Titre du morceau
	struct tick tickTab[MAX_NUMBER_TICKS];// Tableau de ticks
}s_song;
#endif





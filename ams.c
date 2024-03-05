/**
 * @authors Brun Zelman Fontaine Paul CIR3 Caen
 */

#include "define.h"
#include "ams.h"

/**
 * tested, it works !
 * ressource utilisée pour séparer une ligne avec '|' : https://www.codingame.com/playgrounds/14213/how-to-play-with-strings-in-c/string-split
 * @param char* line
 * @return s_tick
 */
s_tick tickFromLine(char* line){
    s_tick tick_;
    for (int i = 0; i < 4; ++i) {
        tick_.note[i] = -1;
    }
    int j = 0;

    char* token = strtok(line, "|"); // ignore la première colonne aka l'index
    token = strtok(NULL, "|");
    for (int i = 0; token != NULL; ++i) {
        switch (token[0]) {
            case '^':
                tick_.accent = 1;
                tick_.note[j] = i+1;
                j++;
                break;
            case 'x':
                tick_.accent = 0;
                tick_.note[j] = i+1;
                j++;
                break;
        }
        token = strtok(NULL, "|");
    }
    return tick_;
}

s_song readAMS(char* fileName){
	FILE* pf = fopen(fileName, "r");
	s_song mySong;

	if(pf == NULL){
        printf("file not oppened ! from readAMS()");
		mySong.title[0] = '\0';
		mySong.tpm = 0;
		mySong.nTicks = 0;

	}else{
		fgets(mySong.title, MAX_SIZE_TITLE, pf); // 1ere ligne : titre
        char tpm[5] ="";
		fgets(tpm, 5, pf); // 2eme ligne : tpm
        mySong.tpm = atoi(tpm);

        char buffer[MAX_SIZE_LINE] = "";
        fgets(buffer,MAX_SIZE_LINE,pf); // la ligne 3 est vide
        fgets(buffer,MAX_SIZE_LINE,pf); // la ligne 4 contient les entêtes des colonnes

        int nb_ticks = 0;
		while(fgets(buffer, MAX_SIZE_LINE, pf) != EOF){
            mySong.tickTab[nb_ticks] = tickFromLine(buffer);
			nb_ticks++;
		}
		mySong.nTicks = nb_ticks;
	}

	return mySong;
}



void createAMS(char* txtFileName, char* amsFileName){

    FILE* wpf = fopen(amsFileName, "w");

    s_song mySong = readAMS(txtFileName);

    fprintf(wpf, "%s\n", mySong.title);
    fprintf(wpf, "%d\n", mySong.tpm);
    fprintf(wpf, "\n");

    fprintf(wpf, "    ");
    for(int i = 1; i < 61; i++){
        fprintf(wpf, "%02d ", i);
    }

    //R=8
    //B=4
    //N=2
    //C=1

    for (int i = 0; token != NULL; ++i) {
        token = strtok(NULL, ",");
        switch (token[0]) {
            case '^':
                tick_.accent = 1;
                tick_.note[j] = i;
                break;
            case 'x':
                tick_.accent = 0;
                tick_.note[j] = i;
                break;
        }
    }

    for(int i = 1; i < mySong.nTicks+1; i++){
        fprintf(wpf, "%03d|", i);
        for(int j = 0; j < 4; j++){
            if(mySong.tickTab[i].note[j] == 0){
                fprintf(wpf, "  |");
            }else{
                if(mySong.tickTab[i].accent == 1){
                    fprintf(wpf, "^ |");
                }else{
                    fprintf(wpf, "x |");
                }
            }
        }
        fprintf(wpf, "\n");
    }

    char notes[60][4] = {
            "C1", "C#1", "D1", "D#1", "E1", "F1", "F#1", "G1", "G#1", "A1", "A#1", "B1",
            "C2", "C#2", "D2", "D#2", "E2", "F2", "F#2", "G2", "G#2", "A2", "A#2", "B2",
            "C3", "C#3", "D3", "D#3", "E3", "F3", "F#3", "G3", "G#3", "A3", "A#3", "B3",
            "C4", "C#4", "D4", "D#4", "E4", "F4", "F#4", "G4", "G#4", "A4", "A#4", "B4",
            "C5", "C#5", "D5", "D#5", "E5", "F5", "F#5", "G5", "G#5", "A5", "A#5", "B5"
    };


    fclose(wpf);
}
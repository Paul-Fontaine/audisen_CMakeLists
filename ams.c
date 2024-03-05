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
    int j = 0;

    char* token = strtok(line, "|"); // ignore la première colonne aka l'index
    for (int i = 0; token != NULL; ++i) {
        token = strtok(NULL, "|");
        switch (token[0]) {
            case '^':
                tick_.accent = 1;
                tick_.note[j] = i;
                j++;
                break;
            case 'x':
                tick_.accent = 0;
                tick_.note[j] = i;
                j++;
                break;
        }
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
        char tpm[4] ="";
		fgets(tpm, 4, pf); // 2eme ligne : tpm
        mySong.tpm = atoi(tpm);

        char buffer[MAX_SIZE_LINE] = "";
        fgets(buffer,0,pf); // les lignes 3 et 4 ne comptent pas
        fgets(buffer,0,pf);

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

}
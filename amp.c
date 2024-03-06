/**
 * @authors Brun Zelman Fontaine Paul CIR3 Caen
 */

#include "define.h"
#include "amp.h"
#include <string.h>
#include <ctype.h>

void lower(char* s){
    for (int i = 0; i < strlen(s); ++i) {
        if ('A' <= s[i] && s[i] <= 'Z'){
            s[i] = tolower(s[i]);
        }
    }
}

void replaceWithUnderscores(char* s){
    for (int i = 0; i < strlen(s); ++i){
        if (isalnum(s[i]) == 0){
            s[i] = '_';
        }
    }
}

// source : https://stackoverflow.com/questions/5457608/how-to-remove-the-character-at-a-given-index-from-a-string-in-c
// https://koor.fr/C/cstring/memmove.wp
void removeCharAtIndex(char* s, int i){
    memmove(&s[i], &s[i + 1], strlen(s) - i);
}

void removeTrailingUnderscores(char *s) {
    int l = strlen(s);
    while (l > 0 && s[l - 1] == '_') {
        s[--l] = '\0';
    }
}

void removeMultiplesUnderscores(char* s){
    int l = strlen(s);
    for (int i = 0; i < l; ++i){
        if (s[i] == '_'){
            while (s[i+1] == '_'){
                removeCharAtIndex(s, i+1);
            }
        }
    }
}

// tested, it works !
void reformat(char* s){
    //todo: replace "ç" by "c" and "à" by "a" ...
    lower(s);
    replaceWithUnderscores(s);
    removeMultiplesUnderscores(s);
    removeTrailingUnderscores(s);
    strcat(s, ".ams");
}

/**
 * tente d'ouvrir le fichier ams
 * ressource utilisée pour le rappel sur fopen() : https://koor.fr/C/cstdio/fopen.wp
 * * @param filename
 * @return a file pointer
 */
FILE* initAMP(char* filename){
    FILE * pf = fopen(filename, "r");

    if (pf == NULL){
        printf("error ! cannot open the file '%s'\n", filename);
    }

    return pf;
}

/**
 *
 * ressource utilisée : https://koor.fr/C/cstdio/fgets.wp
 * @param pf
 * @param song_filename le nom du morceau formaté avec les caractères spéciaux remplacés par '_'
 */
void readAMP(FILE* pf, char * song_filename){
    fgets(song_filename, MAX_SONGNAME_SIZE, pf); // lit une ligne pour récupérer le nom de la musique
    reformat(song_filename);
}

/**
 * tente de fermer le flux de caractères
 * ressource utilisée : https://koor.fr/C/cstdio/fclose.wp
 * @param pf
 */
void closeAMP(FILE* pf){
    if (pf != NULL) {
        int closeCode = fclose(pf);
        if (closeCode == EOF) {
            printf("error during the file closure !");
            exit(1);
        }
    }
}

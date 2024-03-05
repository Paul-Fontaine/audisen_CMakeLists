'''
@author AUDISEN 2024
Comment utiliser ce script python :

 - avoir dans le meme dossier un fichier contenant des trames au format frm
 - en ligne de commande : python play.py file.frm
 - avec pycharm :
    * ouvrir l'onglet terminal en bas puis entrer la commande ci dessus
    * ou : changer le nom du defaut_file dans la fonction main() puis utiliser le bouton vert >

 installation : installer la lib simpleaudio
 - en ligne de commande : pip install -U simpleaudio
 - avec pycharm :
    * CTRL ALT S (settings)
    * chercher python interpreter.
        - Dans ce menu : chercher le + au dessus de Packages
        - entrer simpleaudio, installer.

Notes sur le format frm
    plusieurs melodies peuvent se suivre.
    chaque melodie doit comporter une frame titre
    suivie du nombre de tick correspondant
    aucun saut de ligne entre les melodies
    pas de ligne vide en fin de fichier

'''

import sys
import numpy as np
import simpleaudio as sa

notes = {
'0':0.0,
'C1':65.407,
'C#1':69.296,
'D1':73.417,
'D#1':77.782,
'E1':82.407,
'F1':87.308,
'F#1':92.499,
'G1':97.999,
'G#1':103.827,
'A1':110,
'A#1':116.541,
'B1':123.471,
'C2':130.813,
'C#2':138.592,
'D2':146.833,
'D#2':155.564,
'E2':164.814,
'F2':174.615,
'F#2':184.998,
'G2':195.998,
'G#2':207.653,
'A2':220,
'A#2':233.082,
'B2':246.942,
'C3':261.626,
'C#3':277.183,
'D3':293.665,
'D#3':311.127,
'E3':329.628,
'F3':349.229,
'F#3':369.995,
'G3':391.996,
'G#3':415.305,
'A3':440,
'A#3':466.164,
'B3':493.884,
'C4':523.252,
'C#4':554.366,
'D4':587.33,
'D#4':622.254,
'E4':659.256,
'F4':698.457,
'F#4':739.989,
'G4':783.991,
'G#4':830.61,
'A4':880,
'A#4':932.328,
'B4':987.767,
'C5':1046.503,
'C#5':1108.731,
'D5':1174.66,
'D#5':1244.508,
'E5':1318.511,
'F5':1396.913,
'F#5':1479.978,
'G5':1567.982,
'G#5':1661.219,
'A5':1760,
'A#5':1864.656,
'B5':1975.534
}

def noteArray(t, freqs, accentFlag):
    '''
    concatenate 4 signals into one
    @:param t : time (nunmpy array)
    @:param freqs : frequencies
    @:return numpy array : sum of all 4 sinusoid function with corresponding frequencies
    '''
    norm = 1
    note = np.sin(freqs[0] * t * 2 * np.pi)
    for i in range (1,4):
        if freqs[i] > 0 :
            norm+=1.0
        note+= np.sin(freqs[i] * t * 2 * np.pi)
    return note/norm * (0.5+0.5*accentFlag)


def main():
    '''
    usage : python play.py file.frm
    plays the frm file containing frames.

    '''
    default_file='bohemian_rhapsody.frm'
    args = sys.argv[1:]
    if (len(args) == 1): # ouverture du fichier passé en argument
        print('opening file : ' + args[0])
        framefile = open(args[0], 'r')
    elif (len(args) > 1):
        print('to many args : \n usage :  usage : python play.py file.frm ')
        return
    else: #ouverture du fichier fourni par defaut
        print('opening defaut file')
        framefile = open(default_file, 'r')

    lines = framefile.readlines()

    count = 0
    titleframeline = 0
    print('read ' + str(len (lines))+ ' lines')
    melody = [] # melody list contains all the notes
    while (count < len (lines)):
        count += 1
        print('\nline : ' + str(count), end=" ")
        x = lines[titleframeline][1:].split(",")
        if (len(x)!=3):
            print('unable to read frm title, abort\n')
            return
        title = x[0]
        tempo = float(x[1])
        nbticks = int(x[2].split('*')[0])

        print('playing ' + title + ' at tempo ' + str(tempo) + ' for ' + str(nbticks) + ' ticks')

        # get timesteps for each sample, T is note duration in seconds


        sample_rate = 44100
        T = 60./tempo
        t = np.linspace(0, T, int(T * sample_rate), False)
        frequencies = list(notes.values())


        # Strips the newline character

        for line in lines[titleframeline+1:titleframeline+nbticks+1]:
            count += 1
            print ('\nline : ' + str(count), end = " ")
            x = line[1:16].split(",")
            for i in x :
                print (i, end=" ")
            accentFlag = 0 #int(x[1])
            melody.append(noteArray(t, (frequencies[int(x[2])],frequencies[int(x[3])],frequencies[int(x[4])],frequencies[int(x[5])]),accentFlag))
        print(' ')
        titleframeline = count
    # concatenate notes
    print('total notes to play : ' + str(len(melody)))
    audio = np.hstack(melody)

    # normalize to 16-bit range
    audio *= 32767 / np.max(np.abs(audio))
    # convert to 16-bit data
    audio = audio.astype(np.int16)

    # start playback
    play_obj = sa.play_buffer(audio, 1, 2, sample_rate)

    # wait for playback to finish before exiting
    play_obj.wait_done()

if __name__ == '__main__':
    main()
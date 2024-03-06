/**
 * @authors Brun Zelman Fontaine Paul CIR3 Caen
 */

#include "define.h"
#include "frame.h"
#include "ftd2xx.h"
#include "usb.h"

//DWORD BytesWritten;

FT_HANDLE initUSB(){
    FT_HANDLE ftHandle;
    FT_STATUS ftStatus;

    ftStatus = FT_Open(0, &ftHandle); // open

    ftStatus = FT_SetBaudRate(ftHandle, 9600); // set baud rate

    ftStatus |= FT_SetDataCharacteristics(ftHandle, FT_BITS_8, FT_STOP_BITS_1, FT_PARITY_NONE); // 8 bits de données, 1 bit de stop et pas de parité (on a déjà la checksum)

    ftStatus |= FT_SetFlowControl(ftHandle, FT_FLOW_NONE, 0, 0); // pas de contrôle de flux

    ftStatus |= FT_SetTimeouts(ftHandle, 5000, 1000); // pas recevoir trop de données

    return ftHandle;

}
void closeUSB(FT_HANDLE ftHandle){
    FT_Close(ftHandle);
}


void writeUSB(char* frame, FT_HANDLE ftHandle){
    FT_Write(ftHandle, frame, strlen(frame), &BytesWritten);
}

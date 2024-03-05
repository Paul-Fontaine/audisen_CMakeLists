/**
 * @authors Brun Zelman Fontaine Paul CIR3 Caen
 */

#ifndef AUDISEN_USB_H
#define AUDISEN_USB_H

#include "ftd2xx.h"

FT_HANDLE initUSB();
void closeUSB(FT_HANDLE ftHandle);
void writeUSB(char* frame, FT_HANDLE ftHandle);

#endif //AUDISEN_USB_H

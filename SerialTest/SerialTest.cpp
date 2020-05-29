// SerialTest.cpp : Defines the entry point for the console application.
//

#include <time.h>
#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

#include "Serial.h"

//using namespace std;

#ifndef __TURBOC__
#include <iostream>
#include <windows.h>
#include "stdafx.h"

#define kbhit()       _kbhit()
#define getch()       _getch()
// Used to simulate readbyte() and writebyte) functions
Serial *serialP;
#endif

int main(int argc, char *argv[]) {

    int speed;
    char ch = 0;
    int val;

    if (argc != 3) {
        printf("Serial port sample program for DOS and Windows 10\n");
        printf("Syntax  %s  comPort speed \n", argv[0]);
        printf("  comPort  - com1, com2, etc\n");
        printf("  speed    - 9600, etc.\n");
        printf("e.g %s com1 9600\n", argv[0]);
        return(10);
    }

    // verify the speed
    speed = atoi(argv[2]);
    if ((speed != 110) && (speed != 300) && (speed != 600) && (speed != 9600) && (speed != 19200)) {
        printf("Error: speed must be: 110, 300, 600, 9600 or 19200\n");
        exit(98);
    }

    printf("<esc> to quit\n");
    // Syntax must be good
#ifdef __TURBOC__
    setBaudRate(argv[1], speed);
#else
    tstring commPortName(argv[1]);
    // open the named com port aka com1, save a pointer to the data structure to inbyte and outbyte
    Serial serial(commPortName, speed);
    serialP = &serial;
#endif

    // loop forever
    while (ch != 27) {

        // Check for something from the keyboard
        if (kbhit()) {
            // yes, get it
            ch = getch();

            // send it out
            _outbyte(ch);
        }

        //  check for something from the input stream
        val = _inbyte(1);
        if (val != -2) {
            printf("%c", val & 0x00ff);
        }
    }

 // remove the interrupt handler
#ifdef __TURBOC__
     removeIntHandler();
#endif

     return 0;
}
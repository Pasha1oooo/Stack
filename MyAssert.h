#ifndef MyAssert_H
#define MyAssert_H

#include "Colors.h"

#define IncorrectCapacity() " ERROR: IncorrectCapacity: capacity <= 0 "

//inversive Assert
#define MyAssert(ARG){                                  \
    if(ARG){                                             \
        FILE * fin = fopen("logs.txt", "a");\
        fprintf(fin, "%s  " IncorrectCapacity() " : FILE: %s  FUNCTION: %s  LINE: %d\n",           \
            __TIME__, __FILE__, __FUNCTION__,__LINE__);     \
        fclose(fin);\
        printf(WordRED(IncorrectCapacity()) " IncorrectCapacity Capacity < 0\n");\
    abort();}\
    }\

#endif

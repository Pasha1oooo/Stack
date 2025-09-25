#ifndef MyAssert_H
#define MyAssert_H

#include "COLORS.h"
//inversive Assert
#define MyAssert(ARG){                                  \
    if(ARG){                                             \
        FILE * fin = fopen("logs.txt", "a");\
        fprintf(fin, "%s  ERROR IncorrectCapacity Capacity < 0 : FILE: %s  FUNCTION: %s  LINE: %d\n",           \
            __TIME__, __FILE__, __FUNCTION__,__LINE__);     \
        fclose(fin);\
        printf(WordRED("ERROR: IncorrectCapacity in init") " IncorrectCapacity Capacity < 0\n");\
    abort();}\
    }\

#endif

#ifndef spu_header
#define spu_header

#include <stdlib.h>

typedef enum WorkResult{
    failed = 0,
    success = 1
}WorkResult;

typedef enum Stack_command{
    HLT = 0,
    POP = 2,
    ADD = 3,
    SUB = 4,
    MUL = 5,
    DIV = 6,
    SQRT = 7,
    OUT = 8,
    INIT =  10,
    PUSH = 11,
    POPR = 12,
    PUSHR = 13,
    JMP = 50,
    JB = 51,
    JA = 52,
    JBE = 53,
    JAE = 54,
    JE = 55,
    JNE = 56,
    PUSHM = 60,
    POPM = 61,
    CALL = 90,
    RET = 1
}Stack_command;


#endif

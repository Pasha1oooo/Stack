#ifndef spu_header
#define spu_header

#include <stdlib.h>
typedef enum state{
    failed = 0,
    success = 1
}state;

typedef enum Stack_command{
    INIT =  -1,
    PUSH = 1,
    POP = 2,
    ADD = 3,
    SUB = 4,
    MUL = 5,
    DIV = 6,
    SQRT = 7,
    OUT = 8,
    HLT = 0,
    POPR = 33,
    PUSHR = 42,
    JMP = 50
}Stack_command;


#endif

#include<stdio.h>
#include <stdlib.h>

static FILE * fin = fopen("logs.txt", "a");
#define IncorrectCapacity " ERROR: IncorrectCapacity: capacity <= 0 "
#define BadAdress " ERROR: BadAdress: data = NULL "
#define DeadCanary " ERROR: DeadCanary: attack to Stack from right or left "
#define NUM_Canary 13

#define printlogs(StackErr_ID){\
    switch(StackErr_ID){\
    case(err_IncorrectCapacity):\
        fprintf(fin,"%s " IncorrectCapacity " FILE: %s  FUNCTION: %s  LINE: %d\n", __TIME__, __FILE__, __FUNCTION__,__LINE__);\
        printf(WordRED(IncorrectCapacity) " check logs \n");\
        fclose(fin);\
        break;\
    case(err_BadAdress):\
        fprintf(fin,"%s " BadAdress " FILE: %s  FUNCTION: %s  LINE: %d\n", __TIME__, __FILE__, __FUNCTION__,__LINE__);\
        printf(WordRED(BadAdress) " check logs \n");\
        fclose(fin);\
        break;\
    case(err_DeadCanary):\
        fprintf(fin,"%s " DeadCanary " FILE: %s  FUNCTION: %s  LINE: %d\n", __TIME__, __FILE__, __FUNCTION__,__LINE__);\
        printf(WordRED(DeadCanary) " check logs \n");\
        fclose(fin);\
        break;\
    case(no_err):\
    default:\
        break;\
    };}

typedef enum StackErr_ID{
    err_IncorrectCapacity = 1,
    err_BadAdress = 2,
    err_DeadCanary = 3,
    no_err = 0
}StackErr_ID;

typedef struct stack_t{
    int * data = NULL;
    int   size = 0;
    int   capacity = 0;
}stack_t;


void        StackInit(stack_t * stk, int capacity);
StackErr_ID        StackPush(stack_t * stk, int elem);            //////member, value?
void        StackDestroy(stack_t * stk);
StackErr_ID       StackSizeIncrese(stack_t * stk);
StackErr_ID        StackSizeReduce(stack_t * stk);
StackErr_ID StackVerify(stack_t * stk);
int         StackPop(stack_t * stk);

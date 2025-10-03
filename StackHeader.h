#include<stdio.h>
#include <stdlib.h>


#define IncorrectCapacity " ERROR: IncorrectCapacity: capacity <= 0 "
#define BadAdress " ERROR: BadAdress: data = NULL "
#define DeadCanary " ERROR: DeadCanary: attack to Stack from right or left "

#define CANARYLEFT(stack) *(stack->data)
#define CANARYRIGHT(stack) *(stack->data + stack->capacity - 1)
#define NUM_CANARY 0xDEADBABE

#define LOGS(StackErr_ID) PrintLogs(StackErr_ID, __LINE__, __FUNCTION__);

typedef enum StackErr_ID{
    err_IncorrectCapacity = 1,
    err_BadAdress = 2,
    err_DeadCanary = 3,
    err_GetFromEmptyStack = 4,
    no_err = 0
}StackErr_ID;

typedef struct stack_t{
    int * data = NULL;
    int   size = 0;
    int   capacity = 0;
}stack_t;


void            StackInit(stack_t * stk, int capacity);
StackErr_ID     StackPush(stack_t * stk, int elem);
void            StackDestroy(stack_t * stk);
StackErr_ID     ChangeStackSize(stack_t * stk, float x);
StackErr_ID     StackVerify(stack_t * stk);
StackErr_ID     StackPop(stack_t * stk, int * elem);
void            PrintLogs(StackErr_ID err, int line, const char * func);

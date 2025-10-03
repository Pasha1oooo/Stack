#include<stdio.h>
#include <stdlib.h>
#include<math.h>
#include "Colors.h"
#include "StackHeader.h"

//#include "/home/pasha/Hadders/Hedder.h"
// strings of errors

typedef enum state{
    failed = 0,
    success = 1
}state;

typedef enum Stack_command{
    INIT =  0,
    PUSH = 1,
    POP = 2,
    ADD = 3,
    SUB = 4,
    MUL = 5,
    DIV = 6,
    SQRT = 7,
    PRINT = 8,
    HLT = 9
}Stack_command;

state DoFunc(stack_t * stk, Stack_command command, int ARG);

int main(void){
    printf("Meow\n");
    stack_t stk = {};
    while(DoFunc(&stk,INIT,3) == success){}
    return 0;
}

state DoFunc(stack_t * stk, Stack_command command, int ARG) {
    switch(command){
    case INIT :
        StackDestroy(stk);
        StackInit(stk, ARG);
        return success;
    case PUSH :
        LOGS(StackPush(stk, ARG));
        return success;
    case POP :
        StackPop(stk);
        return success;
    case ADD :
        LOGS(StackPush(stk, StackPop(stk) + StackPop(stk)));
        return success;
    case SUB :
        StackPush(stk, StackPop(stk) - StackPop(stk));
        return success;
    case MUL :
        StackPush(stk, StackPop(stk) * StackPop(stk));
        return success;
    case DIV :
        StackPush(stk, StackPop(stk) / StackPop(stk));
        return success;
    case SQRT :
        StackPush(stk, (int)sqrt(StackPop(stk)));
        return success;
    case PRINT :
        for(int i = 0; i < stk->capacity; i++){
            if(i == 0 || i == stk->capacity - 1){
                printf(WordPURPLE(" [%d] %d ") "\n",  i,stk->data[i]);
                continue;
            }
            else if(i < stk->size){
                printf(WordGREEN(" [%d] %d ") "\n",  i,stk->data[i]);
                continue;
            }
            else if(i == stk->size){
                printf(WordYELLOW(" [%d] %d ") "\n",  i,stk->data[i]);
                continue;
            }
            else if(i > stk->size) {
                printf(WordRED(" [%d] %d ") "\n",  i,stk->data[i]);
                continue;
            }
        }
        return success;
    case HLT:
        StackDestroy(stk);
        return failed;
    default :
        return success;
    }
}


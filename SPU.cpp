#include<stdio.h>
#include <stdlib.h>
#include<math.h>
#include "Colors.h"
#include "StackHeader.h"


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
    OUT = 8,
    HLT = 9
}Stack_command;

state DoFunc(stack_t * stk, int funcs[], int * i);

int main(void){
    printf("Meow\n");
    stack_t stk = {};
    int funcs[1000];
    int i = 0;
    while(scanf("%d", &funcs[i]) != EOF){
        i++;
    }
    i = 0;
    while(DoFunc(&stk, funcs, &i) == success){
        i++;
    }
    return 0;
}
//init in main
state DoFunc(stack_t * stk, int funcs[], int * i){
    int a = 0, b = 0;
    switch((Stack_command)funcs[*i]){
    case INIT :
        StackDestroy(stk);
        StackInit(stk, funcs[*i+1]);
        (*i)++;
        return success;
    case PUSH :
        LOGS(StackPush(stk, funcs[*i+1]));
        (*i)++;
        return success;
    case POP :
        LOGS(StackPop(stk, &a));
        return success;
    case SQRT:
        LOGS(StackPop(stk, &a));
        LOGS(StackPush(stk, (int)sqrt(a)));
        return success;
    case OUT :
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
                printf(WordRED(" [%d] %d [EMPTY] ") "\n",  i,stk->data[i]);
                continue;
            }
        }
        return success;
    case HLT:
        StackDestroy(stk);
        return failed;
    default:
        break;
    }
    LOGS(StackPop(stk, &a));
    LOGS(StackPop(stk, &b));
    switch((Stack_command)funcs[*i]){
    case ADD :
        LOGS(StackPush(stk, a + b));
        return success;
    case SUB :
        LOGS(StackPush(stk, a - b));
        return success;
    case MUL :
        LOGS(StackPush(stk, a * b));
        return success;
    case DIV :
        LOGS(StackPush(stk, a / b));
        return success;
    default :
        return success;
    }
}


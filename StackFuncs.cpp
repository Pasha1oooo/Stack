#include<stdio.h>
#include <stdlib.h>
#include "StackHeader.h"
#include "Colors.h"


static FILE * fin = fopen("logs.txt", "a");

static float size_change_coefficient = 4;
static float size_change_coefficient_reverse = 0.25;


void StackInit(stack_t * stk, int capacity){
    stk->capacity = capacity + 2;
    stk->data = (int*)calloc((size_t)stk->capacity, sizeof(int));
    CANARYLEFT(stk)  = NUM_CANARY;
    CANARYRIGHT(stk) = NUM_CANARY;
    stk->size = 1;

    return;
}

StackErr_ID StackPush(stack_t * stk, int elem){
    StackErr_ID err = StackVerify(stk);
    if(err != no_err) return err;

    if(stk->capacity - 2 <= stk->size){
        ChangeStackSize(stk, size_change_coefficient);
    }

    *((stk->data) + (stk->size)) = elem;
    stk->size += 1;

    err = StackVerify(stk);
    return err;
}

StackErr_ID  StackPop(stack_t * stk, int * elem){
    if(stk->size <= 1) return err_GetFromEmptyStack;

    StackErr_ID err = StackVerify(stk);
    if(err != no_err) return err;

    if(stk->size <= stk->capacity / 4){
        ChangeStackSize(stk, size_change_coefficient_reverse);
    }

    *elem = *((stk->data) + (stk->size) - 1);
    stk->size -= 1;

    err = StackVerify(stk);
    return err;
}

void StackDestroy(stack_t * stk){
    free(stk->data);
    stk->data = NULL;
    stk->capacity = 0;
    stk->size = 0;
    stk = NULL;

    return;
}

StackErr_ID StackVerify(stack_t * stk){
    if (CANARYLEFT(stk) != NUM_CANARY || CANARYRIGHT(stk) != NUM_CANARY){
        return err_DeadCanary;
    }
    else if (stk->data == NULL){
        return err_BadAdress;
    }
    else if (stk->capacity < 0){
        return err_IncorrectCapacity;
    }
    return no_err;
}

StackErr_ID ChangeStackSize(stack_t * stk, float x){
    StackErr_ID err = StackVerify(stk);
    if(err != no_err) return err;

    stk->capacity = (int)((stk->capacity - 2) * x) + 2;
    stk->data = (int*)realloc(stk->data, (size_t)(stk->capacity)*(sizeof(int)));
    CANARYRIGHT(stk) = NUM_CANARY;

    err = StackVerify(stk);
    return err;
}

void PrintLogs(StackErr_ID err, int line, const char * func){
    switch(err){
    case(err_IncorrectCapacity):
        fprintf(fin,"%s " IncorrectCapacity " FILE: %s  FUNCTION: %s  LINE: %d\n", __TIME__, __FILE__, func, line);
        printf(WordRED(IncorrectCapacity) " check logs \n");
        fclose(fin);
        break;
    case(err_BadAdress):
        fprintf(fin,"%s " BadAdress " FILE: %s  FUNCTION: %s  LINE: %d\n", __TIME__, __FILE__, func, line);
        printf(WordRED(BadAdress) " check logs \n");
        fclose(fin);
        break;
    case(err_DeadCanary):
        fprintf(fin,"%s " DeadCanary " FILE: %s  FUNCTION: %s  LINE: %d\n", __TIME__, __FILE__, func, line);
        printf(WordRED(DeadCanary) " check logs \n");
        fclose(fin);
        break;
    case(err_GetFromEmptyStack):
    case(no_err):
    default:
        break;
    };
}

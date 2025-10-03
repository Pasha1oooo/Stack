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
    CanaryLeft(stk)  = NUM_Canary;
    CanaryRight(stk) = NUM_Canary;
    stk->size = 1;
    stk->err = no_err;

    return;
}

void StackPush(stack_t * stk, int elem){
    stk->err = StackVerify(stk);
    if(stk->err != no_err) return;

    if(stk->capacity - 2 <= stk->size) ChangeStackSize(stk, size_change_coefficient);

    *((stk->data) + (stk->size)) = elem;
    stk->size += 1;

    stk->err = StackVerify(stk);
    return;
}

int  StackPop(stack_t * stk){
    stk->err = StackVerify(stk);
    if(stk->size <= 1) stk->err = err_GetFromEmptyStack;
    if(stk->err != no_err) return 0; /////////////////////////////////////////////////////////////////

    if(stk->size <= stk->capacity / 4){
        ChangeStackSize(stk, size_change_coefficient_reverse);
    }

    int elem = *((stk->data) + (stk->size) - 1);
    stk->size -= 1;

    stk->err = StackVerify(stk);
    return elem;
}

void StackDestroy(stack_t * stk){
    stk->err = err_BadAdress;
    free(stk->data);
    stk->data = NULL;
    stk->capacity = 0;
    stk->size = 0;
    stk = NULL;

    return;
}

StackErr_ID StackVerify(stack_t * stk){
    if (CanaryLeft(stk) != NUM_Canary || CanaryRight(stk) != NUM_Canary){
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

void ChangeStackSize(stack_t * stk, float x){
    stk->err = StackVerify(stk);
    if(stk->err != no_err) return;

    stk->capacity = (int)((stk->capacity - 2) * x) + 2;
    stk->data = (int*)realloc(stk->data, (size_t)(stk->capacity)*(sizeof(int)));
    CanaryRight(stk) = NUM_Canary;

    stk->err = StackVerify(stk);
    return;
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

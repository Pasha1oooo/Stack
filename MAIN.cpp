#include<stdio.h>
#include <stdlib.h>
#include "COLORS.h"
#include "MyAssert.h"

#define printlogs(err_ID){\
    FILE * fin = fopen("logs.txt", "a");\
    switch(err_ID){\
    case(err_IncorrectCapacity):\
        fprintf(fin,"%s ERROR: IncorrectCapacity capacity <= 0  FILE: %s  FUNCTION: %s  LINE: %d\n", __TIME__, __FILE__, __FUNCTION__,__LINE__);\
        printf(WordRED("ERROR: IncorrectCapacity") " check logs \n");\
        fclose(fin);\
        break;\
    case(err_BadAdress):\
        fprintf(fin,"%s ERROR: BadAdress data = NULL  FILE: %s  FUNCTION: %s  LINE: %d\n", __TIME__, __FILE__, __FUNCTION__,__LINE__);\
        printf(WordRED("ERROR: BadAdress") " check logs \n");\
        fclose(fin);\
        break;\
    case(no_err):\
    default:\
        break;\
    };}

typedef struct stack_t{
    int * data = NULL;
    int   size = 0;
    int   capacity = 0;
}stack_t;

typedef enum err_ID{
    err_IncorrectCapacity = 1,
    err_BadAdress = 2,
    no_err = 0
}err_ID;

void StackInit(stack_t * stk, int capacity);
void StackPush(stack_t * stk, int elem);            //////member, value?
int  StackPop(stack_t * stk);
void StackDestroy(stack_t * stk);
err_ID StackVerify(stack_t * stk);



int main(void){
    printf("Meow\n");

    stack_t stk = {};
    StackInit(&stk, 10);
    StackPush(&stk, 11111);
    StackPush(&stk, 33333);
    int x = StackPop(&stk);

    printf("%d\n", x);

    StackDestroy(&stk);

    return 0;
}

void StackInit(stack_t * stk, int capacity){
    MyAssert(capacity < 0);

    stk->capacity = capacity;
    stk->data = (int*)calloc((size_t)capacity, sizeof(int));
    stk->size = 0;

    return;
}

void StackPush(stack_t * stk, int elem){
    err_ID err = StackVerify(stk);
    printlogs(err);
    if(err != no_err){
        return;
    }

    if(stk->capacity <= stk->size){
        stk->capacity *= 2;
        stk->data = (int*)realloc(stk->data, (size_t)(stk->capacity)*(sizeof(int)));
        printf("%d\n", (stk->capacity));
    }
    *((stk->data) + (stk->size)) = elem;
    stk->size += 1;

    return;
}

int  StackPop(stack_t * stk){
    err_ID err = StackVerify(stk);
    printlogs(err);
    if(err != no_err){
        return 0;
    }
    if(stk->size <= 0){
        return 0;
    }
    int elem = *((stk->data) + (stk->size) - 1);
    stk->size -= 1;
    return elem;
}

void StackDestroy(stack_t * stk){
    free(stk->data);
    stk->data = NULL;
    stk->capacity = 0;
    stk->size = 0;
    stk = NULL;

    return;
}

err_ID StackVerify(stack_t * stk){
    if (stk->data == NULL){
        return err_BadAdress;
    }
    if (stk->capacity < 0){
        return err_IncorrectCapacity;
    }
    return no_err;

}



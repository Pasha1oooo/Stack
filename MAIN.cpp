#include<stdio.h>
#include <stdlib.h>
#include "MyAssert.h"

typedef struct stack_t{
    int * data = NULL;
    int   size = 0;
    int   capacity = 0;
}stack_t;

void StackInit(stack_t * stk, int capacity);
void StackPush(stack_t * stk, int elem);            //////member?
int  StackPop(stack_t * stk);
void StackDestroy(stack_t * stk);

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
    MyAssert(stk == NULL);
    MyAssert(capacity <= 0);

    stk->capacity = capacity;
    stk->data = (int*)calloc((size_t)capacity, sizeof(int));
    stk->size = 0;

    return;
}

void StackPush(stack_t * stk, int elem){
    MyAssert(stk == NULL);
    MyAssert(stk->capacity <= 0);
    MyAssert(stk->size < 0);

    if(stk->capacity == stk->size){
        stk->data = (int*)realloc((stack_t *)stk->data, (size_t)stk->capacity * 2);
    }

    *((stk->data) + (stk->size)) = elem;
    //printf("%d\n", *((stk->data) + (stk->size)));
    stk->size += 1;

    return;
}

int  StackPop(stack_t * stk){
    //printf("%d\n", *((stk->data) + (stk->size) - 1));
    return *((stk->data) + (stk->size) - 1);
}

void StackDestroy(stack_t * stk){
    free(stk->data);
    stk->data = NULL;
    stk->capacity = 0;
    stk->size = 0;
    stk = NULL;

    return;
}

#include<stdio.h>
#include <stdlib.h>
#include "StackHedder.h"

#define CanaryLeft *(stk->data)
#define CanaryRight *(stk->data + stk->capacity - 1)

//errId
void StackInit(stack_t * stk, int capacity){
    //MyAssert(capacity < 0);

    stk->capacity = capacity + 2;
    stk->data = (int*)calloc((size_t)stk->capacity, sizeof(int));
    CanaryLeft= NUM_Canary;
    CanaryRight= NUM_Canary;
    stk->size = 1;

    return;
}

StackErr_ID StackPush(stack_t * stk, int elem){
    StackErr_ID err = StackVerify(stk);
    if(err != no_err){
        return err;
    }

    if(stk->capacity - 2 <= stk->size){
        StackSizeIncrese(stk);
    }
    *((stk->data) + (stk->size)) = elem;
    stk->size += 1;

    err = StackVerify(stk);
    return err;
}
//
StackErr_ID  StackPop(stack_t * stk, int elem){
    StackErr_ID err = StackVerify(stk);
    printlogs(err);
    if(err != no_err){
        return 0;
    }
    if(stk->size <= 1){
        printf("Empty\n");
        return 0;
    }
    if(stk->size <= stk->capacity / 4){
        StackSizeReduce(stk);
    }
    int elem = *((stk->data) + (stk->size) - 1);
    stk->size -= 1;
    err = StackVerify(stk);

    printlogs(err);
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

StackErr_ID StackVerify(stack_t * stk){
    if (CanaryLeft != NUM_Canary || CanaryRight != NUM_Canary){
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

StackErr_ID StackSizeIncrese(stack_t * stk){
    StackErr_ID err = StackVerify(stk);
    if(err != no_err){
        return err;
    }

    stk->capacity = ((stk->capacity - 2) * 2) + 2;
    stk->data = (int*)realloc(stk->data, (size_t)(stk->capacity)*(sizeof(int)));
    CanaryRight = NUM_Canary;

    err = StackVerify(stk);
    return err;
}

StackErr_ID StackSizeReduce(stack_t * stk){
    StackErr_ID err = StackVerify(stk);
    if(err != no_err){
        return err;
    }

    stk->capacity = (stk->capacity / 2) + 2;
    stk->data = (int*)realloc(stk->data, (size_t)(stk->capacity)*(sizeof(int)));
    CanaryRight = NUM_Canary;

    err = StackVerify(stk);
    return err;
}

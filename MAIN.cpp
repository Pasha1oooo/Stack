#include<stdio.h>
#include <stdlib.h>
#include "COLORS.h"
#include "MyAssert.h"
#include "/home/pasha/Hadders/Hedder.h"

#define IncorrectCapacity() " ERROR: IncorrectCapacity: capacity <= 0 "
#define BadAdress() " ERROR: BadAdress: data = NULL "
#define DeadCanary() " ERROR: DeadCanary: attack to Stack from right or left "
#define NUM_Canary 13
// strings of errors
#define printlogs(StackErr_ID){\
    FILE * fin = fopen("logs.txt", "a");\
    switch(StackErr_ID){\
    case(err_IncorrectCapacity):\
        fprintf(fin,"%s " IncorrectCapacity() " FILE: %s  FUNCTION: %s  LINE: %d\n", __TIME__, __FILE__, __FUNCTION__,__LINE__);\
        printf(WordRED(IncorrectCapacity()) " check logs \n");\
        fclose(fin);\
        break;\
    case(err_BadAdress):\
        fprintf(fin,"%s " BadAdress() " FILE: %s  FUNCTION: %s  LINE: %d\n", __TIME__, __FILE__, __FUNCTION__,__LINE__);\
        printf(WordRED(BadAdress()) " check logs \n");\
        fclose(fin);\
        break;\
    case(err_DeadCanary):\
        fprintf(fin,"%s " DeadCanary() " FILE: %s  FUNCTION: %s  LINE: %d\n", __TIME__, __FILE__, __FUNCTION__,__LINE__);\
        printf(WordRED(DeadCanary()) " check logs \n");\
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

typedef enum StackErr_ID{
    err_IncorrectCapacity = 1,
    err_BadAdress = 2,
    err_DeadCanary = 3,
    no_err = 0
}StackErr_ID;

typedef enum state{
    failed = 0,
    success = 1
}state;

StackErr_ID StackVerify(stack_t * stk);
int         StackPop(stack_t * stk);
state       DoFunc(stack_t * stk);
bool        ComparisonStr(const char * str1, const char * str2);
void        StackInit(stack_t * stk, int capacity);
void        StackPush(stack_t * stk, int elem);            //////member, value?
void        StackDestroy(stack_t * stk);
void        StackSizeIncrese(stack_t * stk);
void        StackSizeReduce(stack_t * stk);

int main(void){
    printf("Meow\n");

    stack_t stk = {};
    while(DoFunc(&stk) == success){}
    return 0;
}

void StackInit(stack_t * stk, int capacity){
    MyAssert(capacity < 0);

    stk->capacity = capacity + 2;
    stk->data = (int*)calloc((size_t)stk->capacity, sizeof(int));
    *(stk->data)= NUM_Canary;
    *((stk->data) + (stk->capacity) - 1)= NUM_Canary;
    stk->size = 1;

    return;
}

void StackPush(stack_t * stk, int elem){
    StackErr_ID err = StackVerify(stk);
    printlogs(err);
    if(err != no_err){
        return;
    }
    if(stk->capacity - 2 <= stk->size){
        StackSizeIncrese(stk);
    }
    *((stk->data) + (stk->size)) = elem;
    stk->size += 1;

    return;
}

int  StackPop(stack_t * stk){
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
    if (*(stk->data) != NUM_Canary || *(stk->data + stk->capacity - 1) != NUM_Canary){
        return err_DeadCanary;
    }
    if (stk->data == NULL){
        return err_BadAdress;
    }
    if (stk->capacity < 0){
        return err_IncorrectCapacity;
    }
    return no_err;
}


state DoFunc(stack_t * stk) {
    char  func[100];
    scanf("%s", &func);
    if(ComparisonStr(func, "INIT")) {
        StackDestroy(stk);
        int capacity = 0;
        scanf("%d", &capacity);
        StackInit(stk, capacity);
    }
    else if(ComparisonStr(func, "PUSH")) {
        int elem = 0;
        scanf("%d", &elem);
        StackPush(stk, elem);
    }
    else if(ComparisonStr(func, "POP")) {
        StackPop(stk);
    }
    else if(ComparisonStr(func, "ADD")) {
        StackPush(stk, StackPop(stk) + StackPop(stk));
    }
    else if(ComparisonStr(func, "SUB")) {
        StackPush(stk, StackPop(stk) - StackPop(stk));
    }
    else if(ComparisonStr(func, "MUL")) {
        StackPush(stk, StackPop(stk) * StackPop(stk));
    }
    else if(ComparisonStr(func, "DIV")) {
        StackPush(stk, StackPop(stk) / StackPop(stk));
    }
    else if(ComparisonStr(func, "SQRT")) {
        StackPush(stk, (int)sqrt(StackPop(stk)));
    }
    else if(ComparisonStr(func, "PRINT")) {
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
    }
    else if(ComparisonStr(func, "HLT")) {
        StackDestroy(stk);
        return failed;
    }
    return success;
}

bool ComparisonStr(const char * str1, const char * str2) {
    MyAssert(str1 == NULL);
    MyAssert(str2 == NULL);
    int j = 0;
    while((str1[j] != '\0') || (str2[j] != '\0')) {
        if (str1[j] != str2[j]) {
            return false;
        }
        j++;
    }
    return true;
}

void StackSizeIncrese(stack_t * stk){
    stk->capacity = ((stk->capacity - 2) * 2) + 2;
    stk->data = (int*)realloc(stk->data, (size_t)(stk->capacity)*(sizeof(int)));
    *(stk->data + stk->capacity - 1) = NUM_Canary;

    return;
}

void StackSizeReduce(stack_t * stk){
    stk->capacity = (stk->capacity / 2) + 2;
    stk->data = (int*)realloc(stk->data, (size_t)(stk->capacity)*(sizeof(int)));
    *(stk->data + stk->capacity - 1) = NUM_Canary;

    return;
}

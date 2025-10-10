#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Colors.h"
#include "StackHeader.h"
#include "spuHeader.h"
// strange work MUL and DIV == 0

typedef struct Code{
    int * code;
    int code_capacity;
    int ic;
}Code;

typedef struct processor{
    stack_t stk;
    Code code;
    int registers[16];
}processor;

state DoInstructions(processor * proc);
void LoadDataFromFile(processor * proc, FILE * fin);
void ProcessorInit(processor * proc);
void ProcessorDestroy(processor * proc);

int main(int argc, char * argv[]){
    printf("Meow\n");
    FILE * fin = fopen(argv[1],"r");
    processor proc = {};
    ProcessorInit(&proc);
    LoadDataFromFile(&proc, fin);

    int i = 0;
    while(DoInstructions(&proc) == success){
        i++;
    }
    //ProcessorDestroy(&proc);
    return 0;
}
//init in main
state DoInstructions(processor * proc){
    int a = 0, b = 0;
    //printf("%d    %d\n", proc->code.code[proc->code.ic], proc->code.ic);
    switch((Stack_command)proc->code.code[proc->code.ic]){
    case INIT :
        StackDestroy(&proc->stk);
        StackInit(&proc->stk, proc->code.code[proc->code.ic+1]);
        (proc->code.ic) += 2;
        return success;
    case PUSH :
        LOGS(StackPush(&proc->stk, proc->code.code[proc->code.ic+1]));
        (proc->code.ic) += 2;
        return success;
    case POP :
        LOGS(StackPop(&proc->stk, &a));
        (proc->code.ic) += 1;
        return success;
    case POPR :
        LOGS(StackPop(&proc->stk, &a));
        //printf("%d\n", proc->code.code[proc->code.ic+1]);
        (proc->registers)[proc->code.code[proc->code.ic+1]] = a;
        (proc->code.ic) += 2;
        return success;
    case PUSHR :
        LOGS(StackPush(&proc->stk, (proc->registers)[proc->code.code[proc->code.ic+1]]));
        (proc->code.ic) += 2;
        return success;
    case SQRT:
        LOGS(StackPop(&proc->stk, &a));
        LOGS(StackPush(&proc->stk, (int)sqrt(a)));
        (proc->code.ic) += 1;
        return success;
    case OUT :
        for(int i = 0; i < proc->stk.capacity; i++){
            if(i == 0 || i == proc->stk.capacity - 1){
                printf(WordPURPLE(" [%d] %d ") "\n",  i, proc->stk.data[i]);
                continue;
            }
            else if(i < proc->stk.size){
                printf(WordGREEN(" [%d] %d ") "\n",  i, proc->stk.data[i]);
                continue;
            }
            else if(i == proc->stk.size){
                printf(WordYELLOW(" [%d] %d ") "\n",  i, proc->stk.data[i]);
                continue;
            }
            else if(i > proc->stk.size) {
                printf(WordRED(" [%d] %d [EMPTY] ") "\n",  i, proc->stk.data[i]);
                continue;
            }
        }
        (proc->code.ic) += 1;
        return success;
    case HLT:
        StackDestroy(&proc->stk);
        return failed;
    case ADD :
        LOGS(StackPop(&proc->stk, &a));
        LOGS(StackPop(&proc->stk, &b));
        LOGS(StackPush(&proc->stk, a + b));
        (proc->code.ic) += 1;
        return success;
    case SUB :
        LOGS(StackPop(&proc->stk, &a));
        LOGS(StackPop(&proc->stk, &b));
        LOGS(StackPush(&proc->stk, b - a));
        (proc->code.ic) += 1;
        return success;
    case MUL :
        LOGS(StackPop(&proc->stk, &a));
        LOGS(StackPop(&proc->stk, &b));
        LOGS(StackPush(&proc->stk, a * b));
        (proc->code.ic) += 1;
        return success;
    case DIV :
        LOGS(StackPop(&proc->stk, &a));
        LOGS(StackPop(&proc->stk, &b));
        LOGS(StackPush(&proc->stk, (int)b / a));
        (proc->code.ic) += 1;
        return success;
    case JMP :
        (proc->code.ic) = proc->code.code[proc->code.ic + 1];
        return success;
    default :
        return success;
    }
}

void ProcessorInit(processor * proc){
    proc->code.ic = 1;
    proc->code.code_capacity = proc->code.code[0];
    return;
}

void ProcessorDestroy(processor * proc){
    StackDestroy(&proc->stk);
    proc->code.code = NULL;
    proc->code.code_capacity = 0;
    proc->code.ic = 0;
}

void LoadDataFromFile(processor * proc, FILE * fin){
    int i = 0;
    fscanf(fin, "%d", &proc->code.code[i]);
    i++;
    proc->code.code_capacity = proc->code.code[0];
    proc->code.code = (int*)calloc(proc->code.code_capacity * 2, sizeof(int));
    StackInit(&(proc->stk), proc->code.code_capacity * 2);

    while(fscanf(fin, "%d", &proc->code.code[i]) != EOF){
        //printf("%d \n",proc->code.code[i]);
        i++;
    }
    return;
}

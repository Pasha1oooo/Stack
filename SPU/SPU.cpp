#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../lib/Colors.h"
#include "../stack/Stack.h"
#include "../SPU/SPU.h"

#define MAX_RAM_LEN 5000
#define NUM_REGISTERS 16


typedef struct Code{
    int * code;
    size_t code_capacity;
    int ic;
}Code;

typedef struct processor{
    stack_t stk;
    Code code;
    int registers[NUM_REGISTERS];
    int * ram;
}processor;

WorkResult DoInstructions(processor * proc);
void LoadDataFromFile(processor * proc, FILE * fin);
void ProcessorInit(processor * proc);
void ProcessorDestroy(processor * proc);
void PrintStack(processor * proc);

int main(int argc, char * argv[]){
    printf("Meow10\n");
    if(argc < 2){
       printf("Not enough arguments (must be 1 arguments)\n");
       return 0;
    }

    FILE * fin = fopen(argv[1],"r");
    processor proc = {};
    ProcessorInit(&proc);
    LoadDataFromFile(&proc, fin);

    while(DoInstructions(&proc) == success){}

    ProcessorDestroy(&proc);
    return 0;
}
//init in main
WorkResult DoInstructions(processor * proc){
    int a = 0, b = 0;
    //printf("%d\n", proc->code.code[proc->code.ic]);
    switch((Stack_command)(proc->code.code[proc->code.ic])){
    case INIT :
        StackDestroy(&proc->stk);
        printf("Meow10FF %d\n", proc->code.code[proc->code.ic+1]);
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
        (proc->registers)[proc->code.code[proc->code.ic+1]] = a;
        (proc->code.ic) += 2;
        return success;
    case PUSHR :
        LOGS(StackPush(&proc->stk, (proc->registers)[proc->code.code[proc->code.ic+1]]));
        (proc->code.ic) += 2;
        return success;
    case PUSHM :
        LOGS(StackPop(&proc->stk, &a));
        (proc->ram)[proc->code.code[proc->code.ic+1]] = a;
        (proc->code.ic) += 2;
        return success;
    case POPM :
        LOGS(StackPush(&proc->stk, (proc->ram)[proc->code.code[proc->code.ic+1]]));
        (proc->code.ic) += 2;
        return success;
    case SQRT:
        LOGS(StackPop(&proc->stk, &a));
        LOGS(StackPush(&proc->stk, (int)sqrt(a)));
        (proc->code.ic) += 1;
        return success;
    case OUT :
        PrintStack(proc);
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
    case CALL :
        LOGS(StackPush(&proc->stk, proc->code.ic + 1));
        (proc->code.ic) = proc->code.code[proc->code.ic + 1] - 1;
        return success;
    case RET :
        LOGS(StackPop(&proc->stk, &a));
        (proc->code.ic) = a +1;
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
        (proc->code.ic) = proc->code.code[proc->code.ic + 1] - 1;
        return success;
    case JB :
        LOGS(StackPop(&proc->stk, &a));
        LOGS(StackPop(&proc->stk, &b));
        if(a > b){
            (proc->code.ic) = proc->code.code[proc->code.ic + 1] - 1;
        }
        else if (a <= b){
            (proc->code.ic) += 2;
        }
        return success;
    case JA :
        LOGS(StackPop(&proc->stk, &a));
        LOGS(StackPop(&proc->stk, &b));
        if(a < b){
            (proc->code.ic) = proc->code.code[proc->code.ic + 1] - 1;
        }
        else if (a >= b){
            (proc->code.ic) += 2;
        }
        return success;
    case JBE :
        LOGS(StackPop(&proc->stk, &a));
        LOGS(StackPop(&proc->stk, &b));
        if(a >= b){
            (proc->code.ic) = proc->code.code[proc->code.ic + 1] - 1;
        }
        else if (a < b){
            (proc->code.ic) += 2;
        }
        return success;
    case JAE :
        LOGS(StackPop(&proc->stk, &a));
        LOGS(StackPop(&proc->stk, &b));
        if(a <= b){
            (proc->code.ic) = proc->code.code[proc->code.ic + 1] - 1;
        }
        else if (a > b){
            (proc->code.ic) += 2;
        }
        return success;
    case JE :
        LOGS(StackPop(&proc->stk, &a));
        LOGS(StackPop(&proc->stk, &b));
        if(a == b){
            (proc->code.ic) = proc->code.code[proc->code.ic + 1] - 1;
        }
        else if (a != b){
            (proc->code.ic) += 2;
        }
        return success;
    case JNE :
        LOGS(StackPop(&proc->stk, &a));
        LOGS(StackPop(&proc->stk, &b));
        if(a != b){
            (proc->code.ic) = proc->code.code[proc->code.ic + 1] - 1;
        }
        else if (a == b){
            (proc->code.ic) += 2;
        }
        return success;
    default :
        return failed;
    }
}

void ProcessorInit(processor * proc){
    proc->code.ic = 0;
    proc->code.code_capacity = 0;
    proc->code.code = NULL;
    StackInit(&proc->stk, 0);
    proc->ram = (int*)calloc(MAX_RAM_LEN, sizeof(int));
    return;
}

void ProcessorDestroy(processor * proc){
    StackDestroy(&proc->stk);
    free(proc->ram);
    proc->code.code = NULL;
    proc->code.code_capacity = 0;
    proc->code.ic = 0;
}

void LoadDataFromFile(processor * proc, FILE * fin){
    fread(&proc->code.code_capacity, sizeof(int), 1,fin);
    proc->code.code = (int*)calloc(proc->code.code_capacity, sizeof(int));
    proc->code.code[0] = proc->code.code_capacity;
    fread(proc->code.code, sizeof(int), proc->code.code_capacity,fin);

    //printf("%d %d\n", proc->code.code_capacity, i);
    //printf("%d \n",proc->code.code[0]);
    //printf("%d \n",proc->code.code[1]);
    return;
}

void PrintStack(processor * proc){
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
}

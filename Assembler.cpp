#include<stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "lib/Colors.h"

//TODO define max len

typedef enum WorkResult{
    failed = 0,
    success = 1
}WorkResult;

// rename
typedef struct Byte{
    int * a;
    int len;
    int * labels;
}Byte;

void ByteInit(Byte * text);
void Translation(FILE * fin1,  Byte * text, const char * funcs[2][7]);
bool ComparisonStr(const char * str1, const char * str2);
void LoadToFile(FILE * fin2,  Byte * text);

int main(int argc, char * argv[]){
    printf("Meow\n");
    if(argc < 3){
       printf("Not enough arguments (must be 2 arguments)\n");
       return 0;
    }
    const char * funcs[2][7] = {{"POP", "ADD", "SUB", "MUL", "DIV", "SQRT", "OUT"},{"INIT", "PUSH", "POPR", "PUSHR"}};
    FILE * fin1 = fopen(argv[1], "r");
    FILE * fin2 = fopen(argv[2], "w");
    Byte text = {};
    ByteInit(&text);
    Translation(fin1, &text, funcs);
    fseek(fin1, 0, SEEK_SET);
    Translation(fin1, &text, funcs);
    LoadToFile(fin2, &text);
    return 0;
}

void Translation(FILE * fin1, Byte * text, const char * funcs[2][7]) {
    char func[1000];
    int i = 0;
    while(fscanf(fin1 ,"%s", &func) != EOF){
                                                    ///NO COPYPASTA in assembler
                       ///BETTER comment     //define
        for(int j = 0; j < 7; j++){                 ///magic number   //define
            if(ComparisonStr(func, funcs[0][j])){
                printf("%s\n", funcs[0][j]);
                text->a[i] = 2 + j;                ///magic number
            }
        }
        for(int j = 0; j < 4; j++){                 ///magic number   //define
            if(ComparisonStr(func, funcs[1][j])){
                printf("%s\n", funcs[1][j]);
                int elem = 0;
                fscanf(fin1, "%d", &elem);
                text->a[i] = 10 + j;
                i++;
                text->a[i] = elem;             ///magic number
            }
        }
        if(ComparisonStr(func, "HLT")) {
            printf("HLT\n");
            text->a[i] = 0;
        }
        else if(ComparisonStr(func, "JMP")) {
            text->a[i] = 50;
            fscanf(fin1 ,"%s", &func);
            i++;
            if(func[0] == ':') {
                if(text->labels[(int)(func[1] - '0')] == 0){
                    printf(WordRED("No JUMP") "\n");
                }
                else{
                    printf(WordGREEN("JUMP") "%d" "\n", text->labels[(int)(func[1] - '0')]);
                    text->a[i] = text->labels[(int)(func[1] - '0')];
                }
            }
            else{
                text->a[i] = atoi(func);
            }
        }
        else if(ComparisonStr(func, "JB")) {
            text->a[i] = 51;
            fscanf(fin1 ,"%s", &func);
            i++;
            if(func[0] == ':') {
                text->a[i] = text->labels[(int)(func[1] - '0')];
            }
            else{
                text->a[i] = atoi(func);
            }
        }
        else if(func[0] == ':') {
            text->labels[(int)(func[1] - '0')] = i + 1;
            printf("%d\n", text->labels[(int)(func[1] - '0')]);
            i--;
        }
        else if(func[0] == '#'){
            i--;
        }
        i++;
    }
    printf("%d\n", i);
    text->len = i;
}

void LoadToFile(FILE * fin2,  Byte * text){
    fprintf(fin2, "%d ", text->len);
    for(int j = 0;j < text->len; j++){
        fprintf(fin2, "%.64b ", text->a[j]);
    }
}

bool ComparisonStr(const char * str1, const char * str2) {
    assert(str1 != NULL);
    assert(str2 != NULL);
    int j = 0;
    while((str1[j] != '\0') || (str2[j] != '\0')) {
        if (str1[j] != str2[j]) {
            return false;
        }
        j++;
    }
    return true;
}

void ByteInit(Byte * text){
    text->a = (int*)calloc(1000, sizeof(int));
    text->labels = (int*)calloc(10, sizeof(int)); ////////TODO define
    text->len = 0;
}
// CALL
// PUSHR 0

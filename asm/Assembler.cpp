#include<stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../lib/Colors.h"
#include "Assembler.h"



int main(int argc, char * argv[]){
    printf("Meow\n");
    Funcs funcs = {{"HLT", "RET", "POP", "ADD", "SUB", "MUL", "DIV", "SQRT", "OUT"},
                   {"INIT", "PUSH", "POPR", "PUSHR"},
                   {"JMP" ,"JB",  "JA", "JBE", "JAE",  "JE", "JNE"}};

    if(argc < 3){
       printf("Not enough arguments (must be 2 arguments)\n");
       return 0;
    }

    FILE * fin1 = fopen(argv[1], "r");
    FILE * fin2 = fopen(argv[2], "w");
    ByteCode text = {};
    ByteCodeInit(&text);
    Translation(fin1, &text, funcs);
    fseek(fin1, 0, SEEK_SET);
    Translation(fin1, &text, funcs);
    LoadToFile(fin2, &text);
    return 0;
}

void Translation(FILE * fin1, ByteCode * text, Funcs funcs) {
    char func[1000];
    int i = 0;
    while(fscanf(fin1 ,"%s", &func) != EOF){

        for(int j = 0; j < 9; j++){
            if(ComparisonStr(func, funcs.funcs_without_args[j])){
                printf("%s\n", funcs.funcs_without_args[j]);
                text->text[i] = j;
            }
        }
        for(int j = 0; j < 4; j++){
            if(ComparisonStr(func, funcs.funcs_with_args[j])) {
                printf("%s\n", funcs.funcs_with_args[j]);
                int elem = 0;
                fscanf(fin1, "%d", &elem);
                text->text[i] = 10 + j;
                i++;
                text->text[i] = elem;
            }
        }
        for(int j = 0; j < 7; j++){
            if(ComparisonStr(func, funcs.jumps[j])) {
                printf("%s\n", funcs.jumps[j]);
                text->text[i] = 50 + j;
                fscanf(fin1 ,"%s", &func);
                i++;
                if(func[0] == ':') {
                    if(text->labels[(int)(func[1] - '0')] == 0){
                    }
                    else{
                        text->text[i] = text->labels[(int)(func[1] - '0')];
                    }
                }
                else{
                    text->text[i] = atoi(func);
                }
            }
        }
        if(ComparisonStr(func, "POPM")){
            printf("%s\n", func);
            int elem = 0;
            fscanf(fin1, "%d",&elem);

            text->text[i] = 60;
            i++;
            printf("%d\n", elem);
            text->text[i] = elem;
        }
        else if(ComparisonStr(func, "PUSHM")){
            printf("%s\n", func);
            int elem = 0;
            fscanf(fin1, "%d",&elem);
            text->text[i] = 61;
            i++;
            printf("%d\n", elem);
            text->text[i] = elem;
        }
        else if(ComparisonStr(func, "CALL")) {
            text->text[i] = 90;
            fscanf(fin1 ,"%s", &func);
            i++;
            if(func[0] == ':') {
                if(text->labels[(int)(func[1] - '0')] == 0){
                }
                else{
                    text->text[i] = text->labels[(int)(func[1] - '0')];
                }
            }
            else{
                text->text[i] = atoi(func);
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

void LoadToFile(FILE * fin2,  ByteCode * text){
    fwrite(&(text->len), sizeof(int), 1,fin2);
    for(int j = 0;j < text->len; j++){
        fwrite(&(text->text[j]), sizeof(int), 1,fin2);
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

void ByteCodeInit(ByteCode * text){
    text->text = (int*)calloc(MAX_TEXT_LEN, sizeof(int));
    text->labels = (int*)calloc(MAX_LABELS_LEN, sizeof(int));
    text->len = 0;
}

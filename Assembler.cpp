#include<stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef enum state{
    failed = 0,
    success = 1
}state;

void Translation(FILE * fin1, FILE * fin2);
bool ComparisonStr(const char * str1, const char * str2);

int main(int argc, char * argv[]){
    printf("Meow\n");
    FILE * fin1 = fopen(argv[1], "r");
    FILE * fin2 = fopen(argv[2], "w");
    Translation(fin1, fin2);
    return 0;
}

void Translation(FILE * fin1, FILE * fin2) {
    char func[1000];
    int buffer[1000];
    int labels[10];
    int i = 0;
    while(!(ComparisonStr(func, "HLT"))){
        fscanf(fin1 ,"%s", &func);
        if(ComparisonStr(func, "INIT")) {
            int capacity = 0;
            fscanf(fin1, "%d", &capacity);
            buffer[i] = -1;
            i++;
            buffer[i] = capacity;
        }
        else if(ComparisonStr(func, "PUSH")) {
            int elem = 0;
            fscanf(fin1, "%d", &elem);
            buffer[i] = 1;
            i++;
            buffer[i] = elem;
        }
        else if(ComparisonStr(func, "POP")) {
            buffer[i] = 2;
        }
        else if(ComparisonStr(func, "ADD")) {
            buffer[i] = 3;
        }
        else if(ComparisonStr(func, "SUB")) {
            buffer[i] = 4;
        }
        else if(ComparisonStr(func, "MUL")) {
            buffer[i] = 5;
        }
        else if(ComparisonStr(func, "DIV")) {
            buffer[i] = 6;
        }
        else if(ComparisonStr(func, "SQRT")) {
            buffer[i] = 7;
        }
        else if(ComparisonStr(func, "OUT")) {
            buffer[i] = 8;
        }
        else if(ComparisonStr(func, "POPR")) {
            int elem = 0;
            fscanf(fin1, "%d", &elem);
            buffer[i] = 33;
            i++;
            buffer[i] = elem;
        }
        else if(ComparisonStr(func, "PUSHR")) {
            int elem = 0;
            fscanf(fin1, "%d", &elem);
            buffer[i] = 42;
            i++;
            buffer[i] = elem;
        }
        else if(ComparisonStr(func, "HLT")) {
            buffer[i] = 0;
        }
        else if(ComparisonStr(func, "JMP")) {
            buffer[i] = 999;
            printf("%d\n", i);
            fscanf(fin1 ,"%s", &func);
            i++;
            if(ComparisonStr(func, ":")) {
                buffer[i] = labels[(int)(func[1] - '0')];
            }
            else{
                buffer[i] = atoi(func);
            }
        }
        else if(func[0] == ':') {
            printf("abc %d %d %d", (int)(func[1] - '0'), func[1], 1);
            labels[(int)(func[1] - '0')] = i;
            i--;
        }
        else if(func[0] == '#'){
            i--;
        }
        i++;
    }
    fprintf(fin2, "%d ", i);
    for(int j = 0;j < i; j++){
        fprintf(fin2, "%d ", buffer[j]);
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

//EMPTY

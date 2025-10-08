#include<stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef enum state{
    failed = 0,
    success = 1
}state;

state Translation(FILE * fin1, FILE * fin2);
bool ComparisonStr(const char * str1, const char * str2);

int main(int argc, char * argv[]){
    FILE * fin1 = fopen(argv[1], "r");
    FILE * fin2 = fopen(argv[2], "w");
    fprintf(fin2, "                     "); ///???????
    int i = 0;                                                      //
    while(Translation(fin1, fin2) == success){i++;}
    fseek(fin2, 0, SEEK_SET);                                       //
    fprintf(fin2, "%d", i);                                      //
    return 0;
}

state Translation(FILE * fin1, FILE * fin2) {
    char  func[100];
    fscanf(fin1 ,"%s", &func);
    if(ComparisonStr(func, "INIT")) {
        int capacity = 0;
        fscanf(fin1, "%d", &capacity);
        fprintf(fin2, "0 ");
        fprintf(fin2, "%d ", capacity);
        return success;
    }
    if(ComparisonStr(func, "PUSH")) {
        int elem = 0;
        fscanf(fin1, "%d", &elem);
        fprintf(fin2, "1 ");
        fprintf(fin2, "%d ", elem);
        return success;
    }
    else if(ComparisonStr(func, "POP")) {
        fprintf(fin2, "2 ");
        return success;
    }
    else if(ComparisonStr(func, "ADD")) {
        fprintf(fin2, "3 ");
        return success;
    }
    else if(ComparisonStr(func, "SUB")) {
        fprintf(fin2, "4 ");
        return success;
    }
    else if(ComparisonStr(func, "MUL")) {
        fprintf(fin2, "5 ");
        return success;
    }
    else if(ComparisonStr(func, "DIV")) {
        fprintf(fin2, "6 ");
        return success;
    }
    else if(ComparisonStr(func, "SQRT")) {
        fprintf(fin2, "7 ");
        return success;
    }
    else if(ComparisonStr(func, "OUT")) {
        fprintf(fin2, "8 ");
        return success;
    }
    else if(ComparisonStr(func, "POPR")) {
        int elem = 0;
        fscanf(fin1, "%d", &elem);
        fprintf(fin2, "10 ");
        fprintf(fin2, "%d ", elem);
        return success;
    }
    else if(ComparisonStr(func, "PUSHR")) {
        int elem = 0;
        fscanf(fin1, "%d", &elem);
        fprintf(fin2, "11 ");
        fprintf(fin2, "%d ", elem);
        return success;
    }
    else if(ComparisonStr(func, "HLT")) {
        fprintf(fin2, "9 ");
        return failed;
    }
    return failed;
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

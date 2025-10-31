#include <stdio.h>

#define MAX_TEXT_LEN 1000
#define MAX_LABELS_LEN 10


typedef enum WorkResult{
    failed = 0,
    success = 1
}WorkResult;

typedef struct ByteCode{
    int * text;
    int len;
    int * labels;
}ByteCode;

//designated initializers [HLT] = "HLT"
typedef struct Funcs{
    const char * funcs_without_args[9];
    const char * funcs_with_args[4];
    const char * jumps[7];
}Funcs;

void ByteCodeInit(ByteCode * text);
void Translation(FILE * fin1,  ByteCode * text, Funcs funcs);
bool ComparisonStr(const char * str1, const char * str2);
void LoadToFile(FILE * fin2,  ByteCode * text);
 // DanilaZhebryakov was here (move to global, remove array)

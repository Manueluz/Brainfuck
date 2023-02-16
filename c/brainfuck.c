#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum TOKENS {
    LEFT,
    RIGHT,
    INCREMENT, 
    DECREMENT,
    OUPUT,
    INPUT,
    BEGIN,
    END,
    NONE
};

typedef struct{
    int type;
    instruction* inner_program;
} instruction;

char* token_names[] = {
    "LEFT"  , "RIGHT", "INCREMENT", "DECREMENT",
    "OUTPUT", "INPUT", "BEGIN"    , "END"      , "NONE"
};

int* tokenize(char* source){
    int len = strlen(source);
    int* token_list =  malloc((len + 1) * sizeof(int));

    for(int i = 0; i < len; i++){
        switch (source[i]){
        case '<':
            token_list[i] = LEFT;
            break;
        case '>':
            token_list[i] = RIGHT;
            break;
        case '+':
            token_list[i] = INCREMENT;
            break;
        case '-':
            token_list[i] = DECREMENT;
            break;
        case '.':
            token_list[i] = OUPUT;
            break;
        case ',':
            token_list[i] = INPUT;
            break;
        case '[':
            token_list[i] = BEGIN;
            break;
        case ']':
            token_list[i] = END;
            break;
        default:
            token_list[i] = NONE;
            break;
        }
    }
    token_list[len] = -1;
    return token_list;
}

instruction* lex(int* tokens){
    int index = 0;
    int res = tokens[index];;

    while(res >= 0){
        printf("%s ", token_names[res]);
        index++;
        res = tokens[index];
    }

    printf("%d",index);
}

int main(){
    char* program_source = "[><.,]";

    int* tokens = tokenize(program_source);
    instruction* program = lex(tokens);

    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STACK_SIZE 1024
#define TAPE_SIZE 2048

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

typedef int token;
typedef int instruction;

char* token_names[] = {"LEFT","RIGHT","INCREMENT","DECREMENT","OUTPUT","INPUT","BEGIN", "END","NONE"};

int token_len(token* tokens){
    int index = 0, count = 0;
    while(tokens[index] >= 0){
        if(tokens[index] != NONE) 
            count++; 
        index++;
    }
    return count;
}

token* tokenize(char* source){
    int len = strlen(source);
    token* token_list =  malloc((len + 1) * sizeof(token));
    for(int i = 0; i < len; i++){
        switch (source[i]){
            case '<': token_list[i] = LEFT; break;
            case '>': token_list[i] = RIGHT; break;
            case '+': token_list[i] = INCREMENT; break;
            case '-': token_list[i] = DECREMENT; break;
            case '.': token_list[i] = OUPUT; break;
            case ',': token_list[i] = INPUT; break;
            case '[': token_list[i] = BEGIN; break;
            case ']': token_list[i] = END; break;
            default : token_list[i] = NONE; break;
        }
    }
    token_list[len] = -1;
    return token_list;
}

instruction* lex(token* tokens){
    int len = token_len(tokens);
    int i = 0, i_pointer = 0;
    instruction* instructions = malloc((len + 1) * sizeof(instruction));
    token tk;
    while(tokens[i] >= 0){
        if(tokens[i] != NONE){
            instructions[i_pointer] = tokens[i];
            i_pointer++;
        }
        i++;
    }
    instructions[len] = NONE;
    return instructions;
}

void execute(instruction* instructions){
    int i = 0;

    int stack[STACK_SIZE];
    int tape[TAPE_SIZE];
    
    int stack_pointer = 0;
    int tape_pointer = TAPE_SIZE / 2;

    while(instructions[i] != NONE){
        switch (instructions[i] ){
            case LEFT : tape_pointer--; i++; break; 
            case RIGHT: tape_pointer++; i++; break; 
            case INCREMENT: tape[tape_pointer]++; i++; break;
            case DECREMENT: tape[tape_pointer]--; i++; break;
            case OUPUT: printf("%c", tape[tape_pointer]); i++; break;
            case INPUT: scanf("%c", &tape[tape_pointer]); i++; break;
            case BEGIN: stack[stack_pointer] = i; stack_pointer++; i++; break;
            case END: stack_pointer--;  if (tape[tape_pointer] != 0) i = stack[stack_pointer]; else i++; break;
            default : i++; break;
        }
    }
}

int main(){
    
    char* program_source = "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.";
 
    printf("Tokenizing ...\n");
    token* tokens = tokenize(program_source);
    
    printf("Lexing....\n");
    instruction* program = lex(tokens);
    
    printf("Executing....\n");
    execute(program);
    return 0;
}
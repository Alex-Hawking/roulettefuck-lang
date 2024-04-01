/*
    RouletteFuck Interpreter
    ========================
    This is the official interpreter for RouletteFuck, an esoteric programming language 
    designed by Alex Hawking. In this interpreter, each command has a one in six chance
    of being executed, simulating the unpredictability of Russian roulette. This design 
    choice challenges  programmers to develop solutions that are not only efficient but 
    also resilient to the inherent randomness introduced by this execution model.

    Usage: 
    To execute a RouletteFuck program, compile this interpreter and run it with the path 
    to your program file as the argument. For example:

    ./roulettefuck_interpreter myprogram.rf

    Note: Due to the randomness of command execution, loop behaviors (`[` and `]`) may 
    work unpredictably. Programmers are advised to design their programs with this 
    variability in mind.

    Designed by Alex Hawking
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAPE_SIZE 30000

// Function prototypes
void execute_brainfuck(char* code);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 2;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *code = (char*)malloc(file_size + 1);
    fread(code, 1, file_size, file);
    code[file_size] = '\0'; 

    execute_brainfuck(code);

    free(code);
    fclose(file);

    return 0;
}

void execute_brainfuck(char* code) {
    unsigned char tape[TAPE_SIZE] = {0};
    unsigned char *ptr = tape;
    char *pc = code;
    int count = 0; 
    int execute_command_at = rand() % 6; 

    while (*pc) {
        if (count == execute_command_at) {
            switch (*pc) {
                case '>':
                    ptr++;
                    if (ptr - tape >= TAPE_SIZE) ptr = tape;
                    break;
                case '<':
                    if (ptr == tape) ptr = tape + TAPE_SIZE;
                    ptr--;
                    break;
                case '+':
                    (*ptr)++;
                    break;
                case '-':
                    (*ptr)--;
                    break;
                case '.':
                    putchar(*ptr);
                    break;
                case ',':
                    *ptr = getchar();
                    break;
                case '[':
                    if (!*ptr) {
                        int loop = 1;
                        while (loop > 0) {
                            pc++;
                            if (*pc == '[') loop++;
                            else if (*pc == ']') loop--;
                        }
                    }
                    break;
                case ']':
                    if (*ptr) {
                        int loop = 1;
                        while (loop > 0) {
                            pc--;
                            if (*pc == ']') loop++;
                            else if (*pc == '[') loop--;
                        }
                    }
                    break;
            }
        }

        count++; 
        pc++;
        if (count == 6) {
            count = 0;
            execute_command_at = rand() % 6;
        }
    }
}


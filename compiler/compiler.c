#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generate(const char *filepath) {
    FILE *file = fopen(filepath, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }


    char *newFilename = malloc(strlen(filepath) + 5); 
    if (!newFilename) {
        perror("Memory allocation failed");
        fclose(file);
        return;
    }
    strcpy(newFilename, filepath);
    char *dot = strrchr(newFilename, '.');
    if (dot) {
        strcpy(dot, ".rf");
    } else {
        strcat(newFilename, ".rf");
    }

    FILE *outfile = fopen(newFilename, "w");
    if (!outfile) {
        perror("Error creating output file");
        free(newFilename);
        fclose(file);
        return;
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '>' || ch == '<' || ch == '+' || ch == '-' || ch == '.' || ch == ',' || ch == '[' || ch == ']') {
            for (int i = 0; i < 6; i++) {
                fputc(ch, outfile);
            }
        }
    }

    // Clean up
    fclose(file);
    fclose(outfile);
    free(newFilename);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <file_path>\n", argv[0]);
        return 1;
    }
    generate(argv[1]);
    return 0;
}

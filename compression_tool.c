#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void compressFile(const char *inputFile, const char *outputFile) {
    FILE *in = fopen(inputFile, "r");
    FILE *out = fopen(outputFile, "w");

    if (in == NULL || out == NULL) {
        printf("File error.\n");
        return;
    }

    char current, previous;
    int count = 1;

    previous = fgetc(in);
    while ((current = fgetc(in)) != EOF) {
        if (current == previous) {
            count++;
        } else {
            fprintf(out, "%c%d", previous, count);
            previous = current;
            count = 1;
        }
    }
    fprintf(out, "%c%d", previous, count);

    fclose(in);
    fclose(out);
}

void decompressFile(const char *inputFile, const char *outputFile) {
    FILE *in = fopen(inputFile, "r");
    FILE *out = fopen(outputFile, "w");

    if (in == NULL || out == NULL) {
        printf("File error.\n");
        return;
    }

    char ch;
    int count;

    while ((ch = fgetc(in)) != EOF) {
        if (isalpha(ch) || isspace(ch) || ispunct(ch)) {
            fscanf(in, "%d", &count);
            for (int i = 0; i < count; i++) {
                fputc(ch, out);
            }
        }
    }

    fclose(in);
    fclose(out);
}

int main() {
    int choice;
    char inputFile[100], outputFile[100];

    printf("1. Compress File\n");
    printf("2. Decompress File\n");
    printf("Choice: ");
    scanf("%d", &choice);
    getchar();

    printf("Enter input file name: ");
    scanf("%s", inputFile);
    printf("Enter output file name: ");
    scanf("%s", outputFile);

    if (choice == 1) {
        compressFile(inputFile, outputFile);
    } else if (choice == 2) {
        decompressFile(inputFile, outputFile);
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}


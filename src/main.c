#include <stdio.h>
#include <stdlib.h>
#include "lib/lexer.h"

int main(int argc, char* argv[]) {
    // Check for the correct number of command-line arguments
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // Open the input file
    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening input file");
        return 1;
    }

    // Determine the file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    // Allocate memory for the input string
    char* input = (char*)malloc((file_size + 1) * sizeof(char));
    if (input == NULL) {
        perror("Error allocating memory for input");
        fclose(file);
        return 1;
    }

    // Read the contents of the file into the input string
    if (fread(input, 1, file_size, file) != (size_t)file_size) {
        perror("Error reading file");
        fclose(file);
        free(input);
        return 1;
    }

    // Null-terminate the input string
    input[file_size] = '\0';

    // Close the file
    fclose(file);

    // Tokenize the input
    Token* tokens = tokenize(input);

    // Print the tokens
    int i = 0;
    while (tokens[i].type != TOKEN_ENDLN) {
        printf("Token Type: %d, Lexeme: %s\n", tokens[i].type, tokens[i].lexeme);
        i++;
    }

    // Free allocated memory
    i = 0;
    while (tokens[i].type != TOKEN_ENDLN) {
        free(tokens[i].lexeme);
        i++;
    }
    free(tokens);
    free(input);

    return 0;
}

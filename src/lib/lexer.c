#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Token* create_token(TokenType type, const char* lexeme) {
    Token* token = (Token*)malloc(sizeof(Token));
    if (token == NULL) {
        perror("Failed to allocate memory for token");
        exit(EXIT_FAILURE);
    }
    token->type = type;
    token->lexeme = strdup(lexeme);
    return token;
}

Token* tokenize(const char* input) {
    Token* tokens = (Token*)malloc(strlen(input) * sizeof(Token));
    if (tokens == NULL) {
        perror("Failed to allocate memory for tokens");
        exit(EXIT_FAILURE);
    }

    int token_count = 0;
    const char* ptr = input;

    while (*ptr != '\0') {
        if (*ptr == ' ') {
            ptr++;  // Skip whitespace
        }
        else if (*ptr == '(') {
            tokens[token_count++] = *create_token(TOKEN_LPAREN, "(");
            ptr++;
        }
        else if (*ptr == ')') {
            tokens[token_count++] = *create_token(TOKEN_RPAREN, ")");
            ptr++;
        }
        else if (*ptr == ';') {
            tokens[token_count++] = *create_token(TOKEN_ENDLN, ";");
            ptr++;
        }
        else if (*ptr == '"') {
            ptr++;  // Skip opening double quote
            const char* start = ptr;
            while (*ptr != '"' && *ptr != '\0') {
                ptr++;
            }
            if (*ptr == '\0') {
                // Unterminated string
                tokens[token_count++] = *create_token(TOKEN_ERROR, "Unterminated string");
                break;
            }
            char* lexeme = (char*)malloc((ptr - start + 1) * sizeof(char));
            if (lexeme == NULL) {
                perror("Failed to allocate memory for string lexeme");
                exit(EXIT_FAILURE);
            }
            strncpy(lexeme, start, ptr - start);
            lexeme[ptr - start] = '\0';
            tokens[token_count++] = *create_token(TOKEN_STRING, lexeme);
            ptr++;  // Skip closing double quote
        }
        else if ((*ptr >= 'a' && *ptr <= 'z') || (*ptr >= 'A' && *ptr <= 'Z')) {
            const char* start = ptr;
            while ((*ptr >= 'a' && *ptr <= 'z') || (*ptr >= 'A' && *ptr <= 'Z')) {
                ptr++;
            }
            char* lexeme = (char*)malloc((ptr - start + 1) * sizeof(char));
            if (lexeme == NULL) {
                perror("Failed to allocate memory for identifier lexeme");
                exit(EXIT_FAILURE);
            }
            strncpy(lexeme, start, ptr - start);
            lexeme[ptr - start] = '\0';
            tokens[token_count++] = *create_token(TOKEN_IDENTIFIER, lexeme);
        }
        else {
            // Invalid character
            char invalid_char[2];
            invalid_char[0] = *ptr;
            invalid_char[1] = '\0';
            tokens[token_count++] = *create_token(TOKEN_ERROR, invalid_char);
            ptr++;
        }
    }

    // Add a null terminator at the end of the token array
    tokens[token_count].type = TOKEN_ENDLN;
    tokens[token_count].lexeme = NULL;

    return tokens;
}

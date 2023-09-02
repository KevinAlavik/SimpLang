#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOKEN_IDENTIFIER,
    TOKEN_LPAREN,
    TOKEN_STRING,
    TOKEN_RPAREN,
    TOKEN_ENDLN,
    TOKEN_ERROR
} TokenType;

typedef struct {
    TokenType type;
    char* lexeme;
} Token;

Token* tokenize(const char* input);

#endif // LEXER_H

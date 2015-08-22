// (c) 1992 Allen I. Holub
#include <stdio.h>
#include <ctype.h>
#include "lex.h"
#include "name.h"
#include "args.h"

void expression(char *tempvar); 
void term(char *tempvar);
void factor(char *tempvar);

void statements(void) {
    // statements -> expression SEMICOLON  |  expression SEMICOLON statements

    char *tempvar;

    while (!match(EOI)) {
        expression(tempvar = newname());
        freename(tempvar);

        if (match(SEMICOLON))
            advance();
        else
            fprintf(stderr, "%d: Inserting missing semicolon\n", yylineno);
    }
}

void expression(char *tempvar) {
    // expression  -> term expression' expression' -> PLUS term expression'
    //             |  epsilon

    char *tempvar2;

    term(tempvar);
    while (match(PLUS)) {
        advance();
        term(tempvar2 = newname());
        printf("    %s += %s\n", tempvar, tempvar2);
        freename(tempvar2);
    }
}

void term(char *tempvar) {
    char *tempvar2;

    factor(tempvar);
    while (match(TIMES)) {
        advance();
        factor(tempvar2 = newname());
        printf("    %s *= %s\n", tempvar, tempvar2);
        freename(tempvar2);
    }
}

void factor(char *tempvar) {
    if (match(NUM_OR_ID)) {
        printf("    %s = %s%.*s\n", tempvar, (isalpha(*yytext) ? "_" : ""),
                yyleng, yytext);
        advance();
    } else if (match(LPAREN)) {
        advance();
        expression(tempvar);
        if (match(RPAREN))
            advance();
        else
            fprintf(stderr, "%d: Mismatched parenthesis\n", yylineno);
    } else
        fprintf(stderr, "%d: Number or identifier expected\n", yylineno);
}

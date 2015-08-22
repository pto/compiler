/*@A (C) 1992 Allen I. Holub                                                */
#include <stdio.h>
#include "lex.h"
#include "name.h"
#include "retval.h"

void statements(void) {
    // statements -> expression SEMICOLON  |  expression SEMICOLON statements

    char *tempvar;

    while (!match(EOI))
    {
        tempvar = expression();

        if (match(SEMICOLON))
            advance();
        else
            fprintf(stderr, "%d: Inserting missing semicolon\n", yylineno);

        freename(tempvar);
    }
}

char *expression(void) {
    // expression -> term expression'
    // expression' -> PLUS term expression' |  epsilon

    char *tempvar, *tempvar2;

    tempvar = term();
    while (match(PLUS)) {
        advance();
        tempvar2 = term();
        printf("    %s += %s\n", tempvar, tempvar2);
        freename(tempvar2);
    }

    return tempvar;
}

char *term(void) {
    char  *tempvar, *tempvar2 ;

    tempvar = factor();
    while (match(TIMES)) {
        advance();
        tempvar2 = factor();
        printf("    %s *= %s\n", tempvar, tempvar2);
        freename(tempvar2);
    }

    return tempvar;
}

char *factor(void) {
    char *tempvar;

    if (match(NUM_OR_ID)) {
        tempvar = newname();
        printf("    %s = %.*s\n", tempvar, yyleng, yytext);
        advance();
    } else if(match(LPAREN)) {
        advance();
        tempvar = expression();
        if(match(RPAREN))
            advance();
        else
            fprintf(stderr, "%d: Mismatched parenthesis\n", yylineno);
    } else {
        tempvar = newname(); // because it will be freed
        fprintf(stderr, "%d: Number or identifier expected\n", yylineno);
    }

    return tempvar;
}

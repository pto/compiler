// (c) 1992 Allen I. Holub
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include "lex.h"

char *yytext = ""; //Lexeme(not '\0' terminated)
int yyleng = 0;    //Lexeme length
int yylineno = 0;  //Input line number

int lex(void) {
    static char input_buffer[BUFSIZ];
    char *current;

    current = yytext + yyleng; //Skip current lexeme

    while (true) {
        while (*current == '\0') { //at end of line
            // Get new line
            current = input_buffer;

            if (fgets(input_buffer, BUFSIZ, stdin) == NULL) {
                *current = '\0';
                return EOI;
            }
            ++yylineno;
            while (isspace(*current))
                ++current;
        }

        for (; *current; ++current) { //Get next token
            yytext = current;
            yyleng = 1;

            switch (*current) {
            case ';':
                return SEMICOLON;
            case '+':
                return PLUS;
            case '*':
                return TIMES;
            case '(':
                return LPAREN;
            case ')':
                return RPAREN;

            case '\n':
            case '\t':
            case ' ':
                break;

            default:
                if (!isalnum(*current))
                    fprintf(stderr, "Ignoring illegal input <%c>\n", *current);
                else {
                    while (isalnum(*current))
                        ++current;

                    yyleng = current - yytext;
                    return NUM_OR_ID;
                }
                break;
            }
        }
    }
}

static int Lookahead = -1; //Lookahead token

int match(int token) {
    if (Lookahead == -1)
        Lookahead = lex();

    return token == Lookahead;
}

void advance(void) {
    //Advance the lookahead to the next input symbol
    Lookahead = lex();
}

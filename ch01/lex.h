// (c) 1992 Allen I.Holub

enum {
    EOI, //end of input
    SEMICOLON,
    PLUS,
    TIMES,
    LPAREN,
    RPAREN,
    NUM_OR_ID
};

extern char *yytext;
extern int yyleng;
extern int yylineno;

int lex(void);
int match(int token);
void advance(void);

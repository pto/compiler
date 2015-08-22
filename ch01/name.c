// (c) 1992 Allen I.Holub
#include <stdio.h>
#include <stdlib.h>
#include "lex.h"
#include "trace.h"
#include "name.h"

char *Names[] = {"t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7"};
char **Namep = Names;

char *newname(void) {
    if (Namep >= &Names[sizeof(Names) / sizeof(*Names)]) {
        fprintf(stderr, "%d: Expression too complex\n", yylineno);
        exit(EXIT_FAILURE);
    }
    if (Trace)
        printf("newname(%s)\n", *Namep);
    return *Namep++;
}

void freename(char *s) {
    if (Namep > Names) {
        if (Trace)
            printf("freename(%s)\n", s);
        *--Namep = s;
    } else
        fprintf(stderr, "%d: (Internal error) Name stack underflow\n",
                yylineno);
}

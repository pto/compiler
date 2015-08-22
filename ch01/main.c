// (c) 1992 Allen I. Holub
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "retval.h"
#include "trace.h"

bool Trace = false;

int main(int argc, char *argv[]) {
    if (argc == 2 && strncmp(argv[1], "-v", 3) == 0)
        Trace = true;

    statements();
}

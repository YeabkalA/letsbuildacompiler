#include <stdio.h>
#include "cradle.h"

/* A global variable to hold the lookahead character */
char lookahead_character;

/* A global variable to use for print buffering */
char _print_buffer[256];
char *print_buffer = _print_buffer;

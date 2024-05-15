#include <stdio.h>
#include "error.h"

/* function declaration */
void controller();

/**
 * main function - activates the program.
 * @return 0
 */
int main() {
    /* Welcome message */
    printf("Welcome to SET program :)\n");

    /* continue to execute until EOF/other error is reached or a manual terminator is encountered. */
    while ( globalError.type !=EOF_ERROR &&
            globalError.type !=MEMORY_ALLOCATION_ERROR &&
            globalError.type != TERMINATE) {controller();}

    handle_error(); /* print error's message */
    return 0; /* return value of main function*/
}

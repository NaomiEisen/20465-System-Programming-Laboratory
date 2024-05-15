#include "error.h"

/* function declaration */
void controller(int argc, char* argv[]);

/* main function - activates the program */
int main(int argc, char* argv[]) {
    if (argc < 2 ) { /* no arguments were passed */
        /* print error message */
        set_error(ILLEGAL_COMMAND_ERROR);
        handle_error();
        return 0; /* return */
    }
    /* read files */
    controller(argc, argv);

    return 0; /* return value of main */
}
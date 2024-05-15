#include "error.h"

/* define global error variable */
Error global_error = {NO_ERROR};

/**
 * Sets error type
 * @param type - error's type
 */
void set_error(ErrorType type) {
    global_error.type = type;
}

/**
 * Prints the corresponding error message
 */
void handle_error() {
    if (global_error.type != NO_ERROR) {
        switch (global_error.type) {
            case CANNOT_OPEN_FILE_ERROR:
                printf("Error: cannot open file.\n");
                break;
            case ILLEGAL_COMMAND_ERROR:
                printf("No arguments have passed\n");
                break;
            case MEMORY_ALLOCATION_ERROR:
                printf("Error: Memory allocation failed.\n");
                break;
            case NO_ERROR:
                break;
            case OUT_OF_RANGE:
                printf("File contains an integer out of range.\n");
                break;
        }
    }
}

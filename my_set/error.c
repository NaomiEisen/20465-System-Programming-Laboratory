#include "error.h"
#include <stdio.h>

/* global error variable */
Error globalError = {NO_ERROR};

/**
 * Sets error type
 * @param type - error's type
 */
void set_error(ErrorType type) {
    globalError.type = type;
}

/**
 * Resets error type to NO_ERROR
 */
void clear_error() {
    globalError.type = NO_ERROR;
}

/**
 * Prints the corresponding error message
 */
void handle_error() {
    if (globalError.type != NO_ERROR) {
        switch (globalError.type) {
            case COMMAND_NAME_ERROR:
                printf("Error: Undefined command name.\n");
                break;
            case SET_NAME_ERROR:
                printf("Error: Undefined set name\n");
                break;
            case OUT_OF_RANGE_ERROR:
                printf("Error: Invalid set member - value out of range.\n");
                break;
            case NOT_INT_ERROR:
                printf("Error: Invalid set member - not an integer.\n");
                break;
            case NOT_TERMINATED_ERROR:
                printf("Error: List of set members is not terminated correctly.\n");
                break;
            case MISSING_PRARAM_ERROR:
                printf("Error: Missing parameter.\n");
                break;
            case EXTRA_TXT_ERROR:
                printf("Error: Extraneous text after end of command.\n");
                break;
            case MULTIPULE_COMMA_ERROR:
                printf("Error: Multiple consecutive commas.\n");
                break;
            case MISSING_COMMA_ERROR:
                printf("Error: Missing comma.\n");
                break;
            case ILLEGAL_COMMA_ERROR:
                printf("Error: Illegal comma.\n");
                break;
            case EOF_ERROR:
                printf("Error: Program is not terminated correctly.\n");
                break;
            case MEMORY_ALLOCATION_ERROR:
                printf("Error: Memory allocation failed.\n");
                break;
            case NO_ERROR:
                break;
            case OTHER_ERROR:
                printf("Unidentified error.\n");
                break;
            default: /* TERMINATE */
                printf("Terminating the program...\n");
        }
    }
}


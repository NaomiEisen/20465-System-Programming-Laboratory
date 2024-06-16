/* -------------------------------- Includes -------------------------------- */
#include "error.h"

/* -------------------------------- Functions -------------------------------- */
/**
 * Sets error type
 * @param error - pointer to the error
 * @param type - error's type
 */
void set_error(Error *error, ErrorType type) {
    /* validate error pointer */
    if (error != NULL) {
        error->type = type;
    }
}

/**
 * Prints the corresponding error message
 * @param error - pointer to the error
 */
void handle_error(Error *error) {
    if (error->type != NO_ERROR) {
        switch (error->type) {
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
/* --------------------------------------------------------------------------- */


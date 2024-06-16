#ifndef ERROR_H
#define ERROR_H
/* -------------------------------- Includes -------------------------------- */
#include <stdio.h>

/* ------------------------------- Structures ------------------------------- */
/* enum for error types */
typedef enum {
    NO_ERROR,
    CANNOT_OPEN_FILE_ERROR,
    ILLEGAL_COMMAND_ERROR,
    MEMORY_ALLOCATION_ERROR,
    OUT_OF_RANGE
} ErrorType;

/* error struct */
typedef struct {
    ErrorType type;
} Error;

/* --------------------------- Function Prototypes --------------------------- */
/**
 * Sets error type
 * @param error - pointer to the error
 * @param type - error's type
 */
void set_error(Error *error, ErrorType type);

/**
 * Prints the corresponding error message
 * @param error - pointer to the error
 */
void handle_error(Error *error);

/* --------------------------------------------------------------------------- */
#endif /* ERROR_H */

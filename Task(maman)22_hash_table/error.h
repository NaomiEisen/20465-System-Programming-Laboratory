#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>

/* enum for error types */
typedef enum {
    NO_ERROR,
    CANNOT_OPEN_FILE_ERROR,
    ILLEGAL_COMMAND_ERROR,
    MEMORY_ALLOCATION_ERROR,
    OUT_OF_RANGE
} ErrorType;

/* initialize error struct */
typedef struct {
    ErrorType type;
} Error;

/* global error variable */
extern Error global_error;

/* function declarations */
void set_error(ErrorType type);
void handle_error();

#endif /* ERROR_H */

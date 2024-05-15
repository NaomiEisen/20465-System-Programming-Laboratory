#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>

/* enum for error types */
typedef enum {
    NO_ERROR,
    COMMAND_NAME_ERROR,
    SET_NAME_ERROR,
    OUT_OF_RANGE_ERROR,
    NOT_INT_ERROR,
    NOT_TERMINATED_ERROR,
    MISSING_PRARAM_ERROR,
    EXTRA_TXT_ERROR,
    MULTIPULE_COMMA_ERROR,
    MISSING_COMMA_ERROR,
    ILLEGAL_COMMA_ERROR,
    EOF_ERROR,
    MEMORY_ALLOCATION_ERROR,
    OTHER_ERROR,
    TERMINATE
} ErrorType;

/* declare error struct */
typedef struct {
    ErrorType type;
} Error;

/* declare global error variable */
extern Error globalError;

/* function declarations */
void set_error(ErrorType type);
void clear_error();
void handle_error();

#endif /* ERROR_H */
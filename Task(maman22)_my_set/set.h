#ifndef SET_H
#define SET_H

/* includes */
#include <stdio.h>
#include <stdlib.h>

/* defines */
#define BYTE_SIZE 8
#define NUM_OF_BYTES 16
#define MAX_COMMAND_CHAR 14
#define MIN_VALUE 0
#define MAX_VALUE 127
#define PARAM_NUM 3 /* number of parameters for limited input function */

/* set struct */
typedef struct {
    /* variable with a size of 127 bits */
    char setValues[NUM_OF_BYTES];
} set;

/* setMapping struct */
typedef struct {
    const char *setName;
    set* setPtr;
} setMapping;

/* functions declarations */
size_t get_line(char **lineptr, FILE *stream);
size_t tokenize_string(char *input, char **tokenizedInput, size_t max_tokens);
void check_memory_allocation(const char *buffer);
void read_set(set* setPtr, char** elements);
void print_set(set *setPtr, const char *setName);
void union_set(set* setPtr1, set* setPtr2, set* setPtrResult);
void intersect_set(set* setPtr1, set* setPtr2, set* setPtrResult);
void sub_set(set* setPtr1, set* setPtr2, set* setPtrResult);
void symdiff_set(set* setPtr1, set* setPtr2, set* setPtrResult);
void stop();


#endif /* SET_H */
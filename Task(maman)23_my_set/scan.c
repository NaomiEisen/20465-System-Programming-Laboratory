#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"

/* functions declarations */
char *my_strsep (char** strPtr, const char* delim);
static char* my_realloc(char* ptr, size_t newSize);
char* trimed_str(char *str);
void check_memory_allocation(const char *buffer);

/**
 * Function that scans line dynamically.
 * @param lineptr - pointer to char array where the scanned input will be saved
 * @param stream - the file to scan
 * @return - the number of characters read
 */
size_t get_line(char **lineptr, FILE *stream) {
    size_t bufferSize = 128; /* initial buffer size */
    char getChar; /* scanned char */
    size_t pos = 0;
    char *buffer = (char *)malloc(bufferSize * sizeof(char));

    /* invalid arguments */
    if (lineptr == NULL || stream == NULL) {
        set_error(EOF_ERROR);
        return 0;
    }

    /* check memory allocation error */
    check_memory_allocation(buffer);
    if (globalError.type != NO_ERROR)
        return 0;

    /* proceed scanning input */
    while ((getChar = (char)(fgetc(stream))) != EOF) {

        if (pos >= bufferSize - 1) { /* reached max buffer size */
            bufferSize += 128; /* Increase buffer size*/
            buffer = my_realloc(buffer, bufferSize * sizeof(char));

            if (buffer == NULL) { /* Memory reallocation error*/
                set_error(MEMORY_ALLOCATION_ERROR);
                return 0;
            }
        }

        buffer[pos] = getChar;
        if (getChar == '\n') {
            buffer[pos] = '\0'; /* Null-terminate the string*/

            *lineptr = buffer; /* update parameters */
            return pos; /* Return the number of characters read*/
        }
        pos++;
    }

    /* end of file reached without newline */
    free(buffer);
    set_error(EOF_ERROR);
    return 0;
}

/**
 * Function to tokenize a string based on commas
 * @param input - the string to tokenize
 * @param tokenizedInput - the result ; tokenized input in the form of array of pointers
 * @param max_tokens - max of tokenizedInput allowed
 * @return
 */
size_t tokenize_string(char *input, char **tokenizedInput, size_t max_tokens) {
    char* token; /* separated token */
    char* copy; /* copy of the inputted string */
    char* copy_start; /* save the initial pointer for later freeing */
    char* word; /* word read */
    int numTokens = 0;

    /* create a trimmed copy of the input string for tokenization */
    copy = trimed_str(input);
    copy_start = copy;

    /* check if memory allocation failed */
    check_memory_allocation(copy);
    if (globalError.type != NO_ERROR)
            return 0;

    /* tokenize the input based on commas */
    token = my_strsep(&copy, ",");
    while (token != NULL) { /* check for errors */
        if (globalError.type != NO_ERROR)
            break;

        word = trimed_str(token); /* create a copy of the token for processing */
        /* check if memory allocation failed */
        check_memory_allocation(word);
        if (globalError.type != NO_ERROR) {
            free(copy_start); /* free current trimmed copy */
            return numTokens;
        }

        if (numTokens >= max_tokens) {
            set_error(EXTRA_TXT_ERROR);
            free(word); /* free current trimmed copy */
            break; /* exit the loop if max_tokens exceeded */
        }

        /* check if the word contains spaces without commas */
        if (strchr(word, ' ') != NULL) {
            set_error(MISSING_COMMA_ERROR);
            free(word); /* free current trimmed copy */
            break;
        }

        /* if the string is empty - check for errors */
        if (strcmp(word, "") == 0) {
            if (numTokens == 0) { /* comma at the start of the inputted  string */
                set_error(ILLEGAL_COMMA_ERROR);
                free(word); /* free current trimmed copy */
                break;
                }
            else if (copy != NULL) { /* consecutive commas */
                set_error(MULTIPULE_COMMA_ERROR);
                free(word); /* free current trimmed copy */
                break;
            }
            else /* comma at the end of the inputted string */
                set_error(EXTRA_TXT_ERROR);
                free(word); /* free current trimmed copy */
                break;
            }

        tokenizedInput[numTokens++] = word; /* add the word to the array of pointers */
        token = my_strsep(&copy, ","); /* Get the next token */
    }

    free(copy_start); /* free the memory allocated for the copy */

    return numTokens; /* return the number of tokenizedInput */
}

/**
 * Function that executes realloc method on inputted parameters
 * while managing errors.
 * @param ptr - pointer to the memory area to be reallocated
 * @param newSize - new size of the array in bytes
 * @return
 */
static char* my_realloc(char* ptr, size_t newSize) {
    char* newPtr = realloc(ptr, newSize);
    if (newPtr == NULL) {
        free(ptr);
        return NULL; /* Memory reallocation error*/
    }
    return newPtr;
}


/**
 * Function that returns a trimmed copy of the input string,
 * removing any leading and trailing spaces.
 * @param str - the string to copy
 * @return - a pointer to the str trimmed copy
 */
char* trimed_str(char *str) {
    size_t len = strlen(str);
    size_t trimmedLen;
    char* trimmedStr;
    char* start = str;
    char* end = str + len - 1;

    /* skip leading spaces */
    while (*start == ' ' || *start == '\t') {
        start++;
    }

    /* skip trailing spaces */
    while (end > start && *end == ' ') {
        end--;
    }

    /* calculate the length of the trimmed string */
    trimmedLen = end - start + 1;

    /* allocate memory for the trimmed string */
    trimmedStr = malloc(trimmedLen + 1);  /* +1 for null terminator */
    if (trimmedStr == NULL) { /* memory allocation error */
        set_error(MEMORY_ALLOCATION_ERROR);
        return NULL;
    }

    /* copy the trimmed string to the new buffer */
    strncpy(trimmedStr, start, trimmedLen);
    trimmedStr[trimmedLen] = '\0';  /* null-terminate the string */

    return trimmedStr;
}

/**
 * Finds the first token in the inputted string that is delimited by the delim.
 * This token is terminated by overwriting the delimiter with a null byte ('\0').
 * If the inputted string is NULL the function returns NULL.
 * @param strPtr - pointer to the string to tokenize
 * @param delim - delimiter string
 * @return - a pointer to the token
 */
char* my_strsep (char** strPtr, const char* delim)
{
    char *start = *strPtr; /* start of the token */
    char *end; /* end of the token */

    if (start == NULL || *start == '\0')   {
        return NULL; /* no more tokens */
    }

    end = strpbrk(start, delim); /* find the next delimiter */

    if (end != NULL) {
        *end = '\0'; /* Null-terminate the token */
        *strPtr = end + 1; /* update the string pointer for the next call */
    }
    else
        *strPtr = NULL; /* no more tokens after this one */
    return start; /* return the token */
}

/**
 * Function to check for memory allocation failure.
 * Sets error accordingly based on the buffer's allocation status.
 * @param buffer - The buffer to check for successful memory allocation.
 */
void check_memory_allocation(const char *buffer) {
    if (buffer == NULL)
        set_error(MEMORY_ALLOCATION_ERROR);
}


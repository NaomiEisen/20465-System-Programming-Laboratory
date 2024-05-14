#include <string.h>
#include "set.h"
#include "error.h"

/* functions declarations */
void handle_read_set(char* ptr, size_t maxNumWords);
void handle_print_set(char* input);
void handle_union_set(char* input);
void handle_intersect_set(char* input);
void handle_sub_set(char* input);
void handle_symdiff_set(char* input);
void handle_stop(char* input, size_t maxNumWords);
int three_param_methods(int* setIndex1, int* setIndex2, int* setIndexResult , char* input);
int validate_var(char** ptr, size_t size);
int is_integer_in_range(char* str);
void print_result(int setIndex1, int setIndex2 , int setIndexResult);
void my_free(char **ptr, size_t size);
int find_set(char* setName);

/* set global variables */
set SETA;
set SETB;
set SETC;
set SETD;
set SETE;
set SETF;

/* global mapping for sets */
setMapping setMappings[] = {
        {"SETA", &SETA},
        {"SETB", &SETB},
        {"SETC", &SETC},
        {"SETD", &SETD},
        {"SETE", &SETE},
        {"SETF", &SETF},
};

/* global mapping for commands */
char commandMapping[][MAX_COMMAND_CHAR]  = {
        "read_set",
        "print_set",
        "union_set",
        "intersect_set",
        "sub_set",
        "symdiff_set",
        "stop",
};


/**
 * Controller function - scans input and executes program commands accordingly
 */
void controller() {
    char command[MAX_COMMAND_CHAR]; /* inputted command name */
    char *input = NULL; /* pointer to inputted line */
    size_t inputSize;
    int commandIndex = 0; /* the corresponding command's index from commandMapping */
    int numOfCommands; /* number of commands in commandMapping */

    handle_error(); /* print previous error's message */

    /* clearing error type before scanning the line */
    clear_error();

    printf("-----------------------------------------------\n");
    printf("Enter your command\n");

    /* scan command name */
    if (scanf("%s", command) == EOF) {
        if (feof(stdin)) {  /* check EOF */
            set_error(EOF_ERROR);
            return;
        }
        else { /* other error */
            set_error(OTHER_ERROR);
            return;
        }
    }

    /* scan the rest of the line */
    inputSize = get_line(&input, stdin);

    printf("\nYou have entered: %s%s\n", command, input);

    /* find the corresponding command from commandMapping */
    numOfCommands = sizeof(commandMapping) / sizeof(commandMapping[0]);
    while ((commandIndex < numOfCommands) &&
           strcmp(command, commandMapping[commandIndex]) != 0) {commandIndex++;}

    /* if no command found - throw an error */
    if ( commandIndex == numOfCommands) {
        set_error(COMMAND_NAME_ERROR);
    }
    else {
        switch (commandIndex) {
            case 0: /* read_set */
                handle_read_set(input, inputSize);
                break;
            case 1: /* print_set */
                handle_print_set(input);
                break;
            case 2: /* union_se t*/
                handle_union_set(input);
                break;
            case 3: /* intersect_set */
                handle_intersect_set(input);
                break;
            case 4: /* sub_set*/
                handle_sub_set(input);
                break;
            case 5: /* symdiff_set */
                handle_symdiff_set(input);
                break;
            case 6: /* stop */
                handle_stop(input ,inputSize);
                break;
            default: /* not supposed to reach here */
                set_error(OTHER_ERROR);
        }
    }
    free(input);

}

/**
 *  Function that prepares the parameters for the 'read_set'
 *  function while managing errors.
 * @param ptr - pointer to the inputted string
 * @param maxNumWords - number of chars in the inputted string
 */
void handle_read_set(char* ptr, size_t maxNumWords) {
    size_t numTokens; /* number of words */
    int setIndex; /* the corresponding set's index from setMapping */

    /* array of pointers to inputted words */
    char **tokenizedInput = (char **)malloc(maxNumWords * sizeof(char *));

    /* memory allocation error */
    check_memory_allocation((char *) tokenizedInput);
    if (globalError.type != NO_ERROR)
        return;

    /* Tokenize the input string */
    numTokens = tokenize_string(ptr, tokenizedInput, maxNumWords);

    /* return if an error occurred */
    if (globalError.type != NO_ERROR){
        my_free(tokenizedInput, numTokens);
        return;
    }

    /* find the corresponding set in setMapping */
    setIndex = find_set(tokenizedInput[0]);

    /* proceed if no errors are detected */
    if (globalError.type == NO_ERROR) {
        /* validate inputted variables */
        validate_var(tokenizedInput + 1, numTokens - 1);

        if (globalError.type == NO_ERROR){
            /* send to function */
            read_set((setMappings[setIndex].setPtr),
                     tokenizedInput + 1);
            /* print the result */
            printf("The values in the set after executing the command >>\n");
            print_set(setMappings[setIndex].setPtr, setMappings[setIndex].setName);
            printf("\n");
        }
    }
    /* free used memory */
    my_free(tokenizedInput, numTokens);
}

/**
 * Function that prepares the parameters for the 'print_set'
 * function while managing errors.
 * @param input - pointer to the inputted string
 */
void handle_print_set(char* input) {
    size_t numTokens; /* number of words */
    int setIndex; /* the corresponding set's index from setMapping */

    /* array of pointers to inputted words */
    char **tokenizedInput = (char **)malloc(sizeof(char *));

    /* memory allocation error */
    check_memory_allocation((char *) tokenizedInput);
    if (globalError.type != NO_ERROR)
        return;

    /* Tokenize the input string */
    numTokens = tokenize_string(input, tokenizedInput, 1); /**FIX**/

    /* if error occurred, return */
    if (globalError.type != NO_ERROR){
        /* first check for others errors */
        if (globalError.type != EXTRA_TXT_ERROR){
            my_free(tokenizedInput, numTokens);
            return;
        }
    }

    /* find the corresponding set in setMapping */
    setIndex = find_set(tokenizedInput[0]);

    /* proceed if no errors are detected */
    if (globalError.type == NO_ERROR){
        print_set(setMappings[setIndex].setPtr, setMappings[setIndex].setName);
    }

    /* free used memory */
    my_free(tokenizedInput, numTokens);

}

/**
 * Function that prepares the parameters for the 'union_set'
 * function while managing errors.
 * @param input - pointer to the inputted string
 */
void handle_union_set(char* input) {
    /* the indexes corresponding to the sets in setMapping */
    int setIndex1, setIndex2, setIndexResult;

    /* proceed if no errors are detected */
    if (three_param_methods(&setIndex1, &setIndex2, &setIndexResult, input)) {
        /* send to union_set function */
        union_set(setMappings[setIndex1].setPtr, setMappings[setIndex2].setPtr,
                  setMappings[setIndexResult].setPtr);
        /* print the result */
        print_result(setIndex1, setIndex2,setIndexResult);
    }
}

/**
 * Function that prepares the parameters for the 'intersect_set'
 * function while managing errors.
 * @param input - pointer to the inputted string
 */
void handle_intersect_set(char* input) {
    /* the indexes corresponding to the sets in setMapping */
    int setIndex1, setIndex2, setIndexResult;

    /* proceed if no errors are detected */
    if (three_param_methods(&setIndex1, &setIndex2, &setIndexResult, input)) {
        /* send to intersect_set function */
        intersect_set(setMappings[setIndex1].setPtr, setMappings[setIndex2].setPtr,
                      setMappings[setIndexResult].setPtr);
        /* print the result */
        print_result(setIndex1, setIndex2,setIndexResult);
    }
}

/**
 * Function that prepares the parameters for the 'sub_set'
 * function while managing errors.
 * @param input - pointer to the inputted string
 */
void handle_sub_set(char* input) {
    /* the indexes corresponding to the sets in setMapping */
    int setIndex1, setIndex2, setIndexResult;

    /* proceed if no errors are detected */
    if (three_param_methods(&setIndex1, &setIndex2, &setIndexResult, input)) {
        /* send to sub_set function */
        sub_set(setMappings[setIndex1].setPtr, setMappings[setIndex2].setPtr,
                setMappings[setIndexResult].setPtr);
        /* print the result */
        print_result(setIndex1, setIndex2,setIndexResult);
    }
}

/**
 * Function that prepares the parameters for the 'symdiff_set'
 * function while managing errors.
 * @param input - pointer to the inputted string
 */
void handle_symdiff_set(char* input) {
    /* the indexes corresponding to the sets in setMapping */
    int setIndex1, setIndex2, setIndexResult;

    /* proceed if no errors are detected */
    if (three_param_methods(&setIndex1, &setIndex2, &setIndexResult, input)) {
        /* send to symdiff_set function */
        symdiff_set(setMappings[setIndex1].setPtr, setMappings[setIndex2].setPtr,
                    setMappings[setIndexResult].setPtr);
        /* print the result */
        print_result(setIndex1, setIndex2,setIndexResult);
    }
}

/**
 * Function that prepares the parameter for the 'stop'
 * function while managing errors.
 * @param input - pointer to the inputted string
 * @param maxNumWords - number of chars in the inputted string
 */
void handle_stop(char* input, size_t maxNumWords) {
    /* array of pointers to inputted words */
    char **tokenizedInput = (char **)malloc(maxNumWords * sizeof(char *));
    size_t numTokens; /* number of words */

    /* memory allocation error */
    check_memory_allocation((char *) tokenizedInput);
    if (globalError.type != NO_ERROR)
        return;

    /* tokenize the inputted string */
    numTokens = tokenize_string(input, tokenizedInput, 0);

    /* if error occurred, return */
    if (globalError.type != NO_ERROR) {
        my_free(tokenizedInput, numTokens);
        return;
    }

    /* proceed to function */
    stop();
    set_error(TERMINATE);

    /* Free memory  */
    my_free(tokenizedInput, maxNumWords);
}

/**
 * Utility function - separates tokens and prepares
 * parameters for a function with three parameters.
 * @param setIndex1 - the corresponding index in the setMapping for the first inputted set's name.
 * @param setIndex2 - the corresponding index in the setMapping for the second inputted set's name.
 * @param setIndexResult - the corresponding index in the setMapping for the third inputted set's name.
 * @param input - pointer to the inputted string
 * @return - 0 if an error occurred ; 1 else
 */
int three_param_methods(int* setIndex1, int* setIndex2, int* setIndexResult , char* input){
    /* array of pointers to inputted words */
    char **tokenizedInput = (char **)malloc(3 * sizeof(char *));
    size_t numTokens;

    /* memory allocation error */
    check_memory_allocation((char *) tokenizedInput);
    if (globalError.type != NO_ERROR)
        return 0;

    /* tokenize the inputted string */
    numTokens = tokenize_string(input, tokenizedInput, PARAM_NUM);

    /* if error occurred */
    if (globalError.type != NO_ERROR) {
        my_free(tokenizedInput, numTokens);
        return 0;
    }

    /* if num of params is smaller than 3 */
    if (numTokens < PARAM_NUM) {
        my_free(tokenizedInput, numTokens);
        set_error(MISSING_PRARAM_ERROR);
        return 0;
    }

    /* find the set in setMapping */
    *setIndex1 = find_set(tokenizedInput[0]);
    *setIndex2 = find_set(tokenizedInput[1]);
    *setIndexResult = find_set(tokenizedInput[2]);

    /* if error occurred, return */
    if (globalError.type != NO_ERROR) {
        my_free(tokenizedInput, numTokens);
        return 0;
    }
    /* no errors */
    my_free(tokenizedInput, numTokens);
    return 1;
}

/**
 * Utility function - validates the inputted numbers.
 * @param ptr - pointer to the tokenized input
 * @param size - number of tokens
 * @return - 0 if an error occurred ; 1 else
 */
int validate_var(char** ptr, size_t size) {
    size_t i; /* index for iterating through loops. */

    for (i = 0; i < size-1 ; i++) {
        /* check if the string represents an integer within the specified range. */
        if (!(is_integer_in_range(ptr[i])))
            return 0;
    }

    /* check if the list of integers is terminated correctly */
    if ((strcmp(ptr[i],"-1"))!= 0 ) {
        set_error(NOT_TERMINATED_ERROR);
        return 0;
    }

    /* no errors */
    return 1;
}

/**
 * Utility function - checks if inputted string is an instance of
 * an integer within the specified range.
 * @param str - the string
 * @return
 */
int is_integer_in_range(char* str) {
    char *endptr; /* pointer to the end of the string */
    long value = strtol(str, &endptr, 10);  /* convert string to long*/

    if (*endptr != '\0' || endptr == str) {
        set_error(NOT_INT_ERROR);
        return 0;  /* Not a valid integer*/
    }

    if (value < MIN_VALUE || value > MAX_VALUE) {
        set_error(OUT_OF_RANGE_ERROR);
        return 0;  /* Not in the specified range */
    }

    return 1;  /* integer in the range */
}

/**
 * Utility function - finds the corresponding set in setMapping
 * for the inputted set's name.
 * @param setName - the inputted set's name
 * @return the index of the corresponding set in setMapping
 */
int find_set(char* setName){
    int i = 0; /* index for iterating through loop */

    /* find the number of sets */
    int num_sets = sizeof(setMappings) / sizeof(setMappings[0]);

    /* iterating through setMappings until a match is found or until the end of the array */
    while (i < num_sets &&
           strcmp(setName, setMappings[i].setName) != 0)
    {i++;}

    /* no match was found */
    if (i == num_sets)
        set_error(SET_NAME_ERROR);

    /* return the index */
    return i;
}
/**
 * Utility function - prints the values in the inputted sets.
 * @param setIndex1 - index of the first set in the setMappings
 * @param setIndex2 - index of the second set in the setMappings
 * @param setIndexResult - index of the third set in the setMappings
 */
void print_result(int setIndex1, int setIndex2 , int setIndexResult) {
    printf("The values in the sets after executing the command:\n");
    print_set(setMappings[setIndex1].setPtr, setMappings[setIndex1].setName);
    print_set(setMappings[setIndex2].setPtr, setMappings[setIndex2].setName);
    print_set(setMappings[setIndexResult].setPtr, setMappings[setIndexResult].setName);
}

/**
 * Function that frees the memory of an array of pointers.
 * @param ptr - pointer to the 2D array
 * @param size - number of rows in the array.
 */
void my_free(char **ptr, size_t size) {
    size_t i; /* index for iterating through loop */

    /* free the memory that each index in the array points to */
    for (i = 0; i < size; i++)
        free(ptr[i]);

    /* free the array's memory */
    free(ptr);
}

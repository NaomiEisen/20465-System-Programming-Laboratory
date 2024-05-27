#include <string.h>
#include "set.h"

/* functions declarations */
void clearSet(set* setPtr);
void setBit(set* setPtr, int i);

/**
 * Function that sets the bit at the specified index to 1 in the given set.
 * @param setPtr - pointer to the set
 * @param i - the required index
 */
void setBit(set* setPtr, int i) {
    char mask;
    /* calculate the byte index and bit offset*/
    int byteIndex = i / BYTE_SIZE; /* find the byte index */
    int bitOffset = i % BYTE_SIZE; /* find the bit offset within the byte*/

    /* create a mask with only the bit at the offset position set to 1 */
    mask = (char)(1 << bitOffset); /* explicit cast to char */
    setPtr -> setValues[byteIndex] |= mask;
}

/**
 * Function that sets the elements of the set,
 * overriding any previous initialization.
 * @param setPtr - pointer to the set
 * @param elements - the required elements.
 */
void read_set(set* setPtr, char** elements) {
    int i = 0; /* index for iterating through loop */
    int intRead; /* the integer at index i in the elements array */
    int isMinusOne = 0; /* flag to track the terminator -1 */

    clearSet(setPtr); /* clear previous initialization */

    while (!isMinusOne) {
        if (strcmp(elements[i], "-1") == 0)
            isMinusOne = 1;  /* set flag for -1 */
        else {
            intRead = atoi(elements[i]);
            /* FOR ME!!! DELETE LATER!!!!!!!!!!!
            printf("Read integer: %d\n", intRead); */
            setBit(setPtr, intRead);
            i++;
            }
    }
}

/**
 * Function that prints the set.
 * @param setPtr - pointer to the set
 */
void print_set(set *setPtr, const char *setName) {
    int i, j; /* indexes for iterating through loops */
    int index; /* the index of the bit */
    int emptySet = 1; /* initialize emptySet to true */
    printf("%s: ", setName);

    for (i = 0; i < NUM_OF_BYTES; i++) {
        for (j = 0; j < BYTE_SIZE; j++) {
            if (setPtr->setValues[i] & (1 << j)) { /* Check if the j-th bit is 1 */
                emptySet = 0; /* set is not empty - change variable to false */
                index = i * BYTE_SIZE + j; /* calculate the overall index */
                printf("%d ", index);
            }
        }
    }

    if (emptySet) /* if the set is an empty set */
        printf("Empty set.");

    printf("\n");
}

/**
 * Function that performs the union operation on the first two inputted
 * sets and stores the result in the third inputted set.
 * @param setPtr1 - pointer to the first set
 * @param setPtr2 - pointer to the second set
 * @param setPtrResult - pointer to the set that will store the result
 */
void union_set(set* setPtr1, set* setPtr2, set* setPtrResult){
    int i; /* index for iterating through loop */
    for (i = 0; i < NUM_OF_BYTES; i++) {
        setPtrResult->setValues[i] = (char)(setPtr1->setValues[i] | setPtr2->setValues[i]);
    }

}

/**
 * Function that performs the intersect operation on the first two inputted
 * sets and stores the result in the third inputted set.
 * @param setPtr1 - pointer to the first set
 * @param setPtr2 - pointer to the second set
 * @param setPtrResult - pointer to the set that will store the result
 */
void intersect_set(set* setPtr1, set* setPtr2, set* setPtrResult){
    int i; /* index for iterating through loop */
    for (i = 0; i < NUM_OF_BYTES; i++) {
        setPtrResult->setValues[i] = (char)(setPtr1->setValues[i] & setPtr2->setValues[i]);
    }

}

/**
 * Function that performs the subtraction operation on the first two inputted
 * sets and stores the result in the third inputted set.
 * @param setPtr1 - pointer to the first set
 * @param setPtr2 - pointer to the second set
 * @param setPtrResult - pointer to the set that will store the result
 */
void sub_set(set* setPtr1, set* setPtr2, set* setPtrResult){
    int i; /* index for iterating through loop */
    for (i = 0; i < NUM_OF_BYTES; i++) {
        setPtrResult->setValues[i] = (char)(setPtr1->setValues[i] & (~setPtr2->setValues[i]));
    }
}

/**
 * Function that performs the symmetrical difference operation on the first two inputted
 * sets and stores the result in the third inputted set.
 * @param setPtr1 - pointer to the first set
 * @param setPtr2 - pointer to the second set
 * @param setPtrResult - pointer to the set that will store the result
 */
void symdiff_set(set* setPtr1, set* setPtr2, set* setPtrResult){
    int i; /* index for iterating through loop */
    for (i = 0; i < NUM_OF_BYTES; i++) {
        setPtrResult->setValues[i] = (char)((setPtr1->setValues[i] | setPtr2->setValues[i]) &
                ~(setPtr1->setValues[i] & setPtr2->setValues[i]));
    }
}

/**
 * Function that terminates the program
 */
void stop(){
    printf("Ok. bye :)\n");
}

/**
 * Function than resets the set's values
 * @param setPtr - pointer to the set
 */
void clearSet(set* setPtr) {
    int i; /* index for iterating through loop */
    for (i = 0; i < NUM_OF_BYTES; i++) {
        setPtr->setValues[i] = 0;
    }
}


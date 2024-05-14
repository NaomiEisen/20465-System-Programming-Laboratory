#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 29

/* define the structure for a node in the linked list */
typedef struct {
    int repetition;
    FILE* fp;
    struct Node* next;
} Node;

/* define the structure for the hash table */
typedef struct {
    struct Node* table[TABLE_SIZE];
} HashTable;

#endif //HASH_H

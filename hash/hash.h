#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 30


/* declare the structure for a node in the linked list */
typedef struct Node {
    int repetition;
    char* file_name;
    struct Node* next;
} Node;

/* declare the structure for the hash table */
typedef struct {
    Node* table[TABLE_SIZE];
} HashTable;

/* declare global HashTable variable */
extern HashTable global_hash_table;

/* functions declarations */
void insert(int key, char *file);
void free_hash_table();

#endif /* HASH_H */

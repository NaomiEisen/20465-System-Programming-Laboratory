#ifndef MAMAN23_HASH_TABLE_H
#define MAMAN23_HASH_TABLE_H
/* -------------------------------- Includes -------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include "error.h"
/* --------------------------------- Defines --------------------------------- */
#define TABLE_SIZE 29
/* ------------------------------- Structures -------------------------------- */

/* declare the structure for a node in the linked list */
typedef struct Node {
    int repetition;
    char* file_name;
    struct Node* next;
} Node;

/* declare the structure for the hash table */
typedef struct {
    Node* table[TABLE_SIZE];
    Error error;
} HashTable;

/* --------------------------- Function Prototypes --------------------------- */
/**
 * Initializes a hash table by setting all table entries to NULL and
 * initializing the error field to indicate no error.
 * @param hash_table - pointer to the hash table to be initialized
 */
void initialize_hash_table(HashTable* hash_table);

/**
 * Creates new node with the required data.
 * @param file - file name
 * @return  pointer to the created node
 */
Node* create_node(char* file);

/**
 * Inserts the scanned integer from the specified file to the given hash table.
 * @param hash_table - pointer to the hash_table
 * @param key - the scanned integer
 * @param file - file name
 */
void insert(HashTable *hash_table, char *file, int key);

/**
 * Checks if a node with the same file name and key exists in the given HashTable by examining the head of the linked
 * list at the specified key index. If it exists, updates its repetition count attribute and returns true.
 * Otherwise, returns false.
 * @param hash_table - the hash table
 * @param key - the scanned integer
 * @param file - file name
 * @return  1 (true) if the corresponding node is found; 0 (false) otherwise
 */
int matching_list_head(HashTable *hash_table, char *file, int key);

/**
 * Free the memory allocated for the specified hash table and its nodes
 */
void free_hash_table(HashTable *hash_table);
/* --------------------------------------------------------------------------- */

#endif /* MAMAN23_HASH_TABLE_H */

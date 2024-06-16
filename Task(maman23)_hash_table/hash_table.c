/* -------------------------------- Includes -------------------------------- */
#include <string.h>
#include "hash_table.h"
#include "error.h"
/* --------------------------------------------------------------------------- */

/* -------------------------------- Functions -------------------------------- */
/**
 * Initializes a hash table by setting all table entries to NULL and
 * initializing the error field to indicate no error.
 * @param hash_table - pointer to the hash table to be initialized
 */
void initialize_hash_table(HashTable* hash_table) {
    int i; /* index for iterating through loop */

    /* set all entries in the hash table to NULL */
    for (i = 0; i < TABLE_SIZE; i++) {
        hash_table->table[i] = NULL;
    }

    /* initialize the error field to indicate no error */
    hash_table->error.type = NO_ERROR;
}

/**
 * Creates new node with the required data.
 * @param file - file name
 * @return  pointer to the created node
 */
Node* create_node(char* file) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    /* if memory allocation succeeded, set nodes attributes */
    if (newNode) {
        newNode->file_name = file;
        newNode->repetition = 1; /* first instance of this key in the specified file */
        newNode->next = NULL;
        return newNode; /* return pointer to the new node */

    } else {  /* if memory allocation failed */
        free(newNode);
        return NULL;
    }
}

/**
 * Inserts the scanned integer from the specified file to the given hash table.
 * @param hash_table - pointer to the hash_table
 * @param key - the scanned integer
 * @param file - file name
 */
void insert(HashTable *hash_table, char *file, int key) {
    Node* newNode; /* declaration of new node */

    /* check if node with the same file name and key exists */
    /* if so, change the rep count of this node and return */
    if (matching_list_head(hash_table, file, key))
        return;

    /* create new node */
    newNode = create_node(file);
    if (!newNode) { /* memory allocation failure */
        set_error(&hash_table->error, MEMORY_ALLOCATION_ERROR);
        return;
    }

    /* insert at the beginning of the linked list */
    newNode->next = hash_table->table[key];
    hash_table->table[key] = newNode;
}


/**
 * Checks if a node with the same file name and key exists in the given HashTable by examining the
 * head of the linked list at the specified key index. If it exists, updates its repetition count
 * attribute and returns true. Otherwise, returns false.
 * @param hash_table - the hash table
 * @param key - the scanned integer
 * @param file - file name
 * @return  1 (true) if the corresponding node is found; 0 (false) otherwise
 */
int matching_list_head(HashTable *hash_table, char *file, int key) {
    if (hash_table != NULL) {
        Node *n = hash_table->table[key];
        if (n) { /* if node exists */
            if (strcmp(n->file_name, file) == 0) { /* matching file name found */
                n->repetition++; /* update repetition count */
                return 1; /* return true */
            }
        }
    }
    /* if no match exists return false */
    return 0;
}

/**
 * Free the memory allocated for the specified hash table and its nodes
 */
void free_hash_table(HashTable *hash_table) {
    int i; /* index for iterating through loop */

    /* free nodes in each bucket */
    for ( i = 0; i < TABLE_SIZE; i++) {
        /* get head of list at index i of table */
        Node* current = hash_table->table[i];

        while (current != NULL) { /* free all the nodes in this list */
            Node* temp = current;
            current = current->next;
            free(temp);
        }
        /* set bucket to NULL after freeing nodes */
        hash_table->table[i] = NULL;
    }
}
/* --------------------------------------------------------------------------- */

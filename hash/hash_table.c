#include <string.h>
#include "hash.h"
#include "error.h"

HashTable global_hash_table;  /* define global_hash_table */

/* functions declarations */
Node* create_node(char* file);
int matching_list_head(int key, char* file);

/**
 * Creates new node with the required data.
 * @param file - file name
 * @return  pointer to the created node
 */
Node* create_node(char* file) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode) { /* if memory allocation succeeded, set nodes attributes */
        newNode->file_name = file;
        newNode->repetition = 1; /* first instance of this key in the specified file */
        newNode->next = NULL;
    }
    return newNode; /* return pointer to the new node */
}

/**
 * Inserts the scanned integer from the specified file to the hash table.
 * @param key - the scanned integer
 * @param file - file name
 */
void insert(int key, char *file) {
    Node* newNode; /* declaration of new node */

    /* check if node with the same file name and key exists */
    /* if so, change the rep count of this node and return */
    if (matching_list_head(key, file))
        return;

    /* create new node */
    newNode = create_node(file);
    if (!newNode) { /* memory allocation failure */
        set_error(MEMORY_ALLOCATION_ERROR);
        return;
    }

    /* insert at the beginning of the linked list */
    newNode->next = global_hash_table.table[key];
    global_hash_table.table[key] = newNode;
}


/**
 * Checks if a node with the same file name and key exists by examining the head of the linked list
 * at the specified key index. If it exists, updates its repetition count attribute and returns true.
 * Otherwise, returns false.
 * @param key - the scanned integer
 * @param file - file name
 * @return  1 (true) if the corresponding node is found; 0 (false) otherwise
 */
int matching_list_head(int key, char* file) {
    Node* n = global_hash_table.table[key];
    if (n) { /* if node exists */
        if (strcmp(n->file_name, file) == 0) { /* matching file name found */
            n->repetition++; /* update repetition count */
            return 1; /* return true */
        }
    }
    /* if no match exists return false */
    return 0;
}

/**
 * Free the memory allocated for the hash table and its nodes
 */
void free_hash_table() {
    int i; /* index for iterating through loop */

    /* free nodes in each bucket */
    for ( i = 0; i < TABLE_SIZE; i++) {
        /* get head of list at index i of table */
        Node* current = global_hash_table.table[i];

        while (current != NULL) { /* free all the nodes in this list */
            Node* temp = current;
            current = current->next;
            free(temp);
        }
        /* set bucket to NULL after freeing nodes */
        global_hash_table.table[i] = NULL;
    }
}
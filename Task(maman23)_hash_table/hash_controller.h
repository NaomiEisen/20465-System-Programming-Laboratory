#ifndef HASH_CONTROLLER_H
#define HASH_CONTROLLER_H

/* --------------------------- Function Prototypes -------------------------- */
/**
 * Executes the program - irritates through the inputted arguments and handles the
 * content insertion. Returns if error occurs.
 * @param argc - number of arguments
 * @param argv - array of the file names
 */
void controller(int argc, char* argv[]);

/**
 * Reads the contents of a specified file and handles the insertion of this
 * data into the hash table.
 * @param hash_table - pointer to the hash table
 * @param file_name - name of the file to be read
 */
void read_file(HashTable *hash_table, char *file_name);

/**
 * Prints the data stored in the given hash table.
 * @param hash_table - pointer to the hash table
 */
void print_hash(HashTable *hash_table);

/**
 * Prints the stored data in the linked list.
 * @param node - pointer to the head of the linked list.
 */
void print_nodes(Node* node);

/**
 * Utility function for determining the appropriate output format.
 * Returns an empty string if the inputted repetition attribute is equal to 1,
 * otherwise returns the 's' ending for pluralization.
 * @param rep - the repetition attribute
 * @return  the appropriate ending pronunciation, if needed
 */
char* single_rep(int rep);

/**
 * Utility function for determining the appropriate punctuation in the output format.
 * Returns a period '.' if it is the end of a sentence, otherwise returns a comma and a space ', '.
 * @param flag - boolean argument to determine if it is the end of a sentence.
 * @return  the corresponding punctuation string
 */
char* last(int flag);

/* -------------------------------------------------------------------------- */
#endif /* HASH_CONTROLLER_H */

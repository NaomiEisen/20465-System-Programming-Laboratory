#include "hash.h"
#include "error.h"

/* functions declarations */
void read_file(char *file_name);
char* single_rep(int rep);
char* last(int flag);
void print_hash();
void print_nodes(Node* node);

/**
 * Executes the program - irritates through the inputted arguments and handles the content
 * insertion. Returns if error occurs.
 * @param argc - number of arguments
 * @param argv - array of the file names
 */
void controller(int argc, char* argv[]) {
    int i = 1; /* index for iterating through loop */

    /* read inputted files */
    while (argc > 1  && global_error.type == NO_ERROR ) {
        read_file(argv[i]); /* read this file */
        i++;
        argc--;
    }

    /* if error occurred  */
    if (global_error.type != NO_ERROR) {
        /* print error message and return */
        handle_error();
        free_hash_table();
        return;
    }

    /* print result */
    print_hash();

    /* free memory */
    free_hash_table();
}

/**
 * Reads the contents of a specified file and handles the insertion of this
 * data into the hash table.
 * @param file_name - desired file name
 */
void read_file(char *file_name){
    FILE* fd; /* the corresponding file */
    int num; /* variable for reading file's content */

    /* open file in read mode */
    if (!(fd = fopen(file_name, "r"))) {
        /* if the file fails to open, set an error and return */
        set_error(CANNOT_OPEN_FILE_ERROR);
        fclose(fd); /* close the file */
        return;
    }

    /* read integers from the file */
    while (fscanf(fd, "%d", &num) == 1) {

        if (num < 0 || num >= TABLE_SIZE ){ /* integer out of bonds */
            set_error(OUT_OF_RANGE);
            fclose(fd); /* close the file */
            return;
        }

        /* insert integer to hash table */
        insert(num, file_name);
    }

    /* close the file */
    fclose(fd);
}

/**
 * Prints the data stored in the hash table.
 */
void print_hash() {
    int i; /* index for iterating through loop */
    Node* node = NULL; /* first node, if exists, in the hash table */

    for( i = 0 ; i < TABLE_SIZE; i++) {
        node = global_hash_table.table[i];
        if (node) { /* if node exists */
            printf("\n%d appears in ", i);
            print_nodes(node); /* print the linked list of nodes */
        }
    }
}

/**
 * Prints the stored data in the linked list.
 * @param node - pointer to the head of the linked list.
 */
void print_nodes(Node* node){
    Node* next = NULL; /* next node of current node */
    int rep; /* repetition attribute of current node */
    int last_flag = 0; /* flag indicates the end of linked list */

    while (node) { /* while node exists */
        next = node->next; /* set next */
        rep = node->repetition; /* set the current rep */

        if (!next) /* if next node does not exist, set the flag to true */
            last_flag = 1;

        /* print nodes data in the appropriate format */
        printf("file %s- %d time%s%s", node->file_name, rep, single_rep(rep), last(last_flag));

        node = next; /* set node to the next node */
    }
}

/**
 * Utility function for determining the appropriate output format.
 * Returns an empty string if the inputted repetition attribute is equal to 1,
 * otherwise returns the 's' ending for pluralization.
 * @param rep - the repetition attribute
 * @return  the appropriate ending pronunciation, if needed
 */
char* single_rep(int rep) {
    if (rep == 1)
        return ""; /* return true */
    return "s"; /* return false */
}

/**
 * Utility function for determining the appropriate punctuation in the output format.
 * Returns a period '.' if it is the end of a sentence, otherwise returns a comma and a space ', '.
 * @param flag - boolean argument to determine if it is the end of a sentence.
 * @return  the corresponding punctuation string
 */
char* last(int flag) {
    if (flag) /* if flag is true */
        return ".";
    return ", "; /* if flag if false */
}
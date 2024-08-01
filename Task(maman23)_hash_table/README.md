# hash_table Program

### Short description:
This program processes a list of files specified via command line arguments. Each file contains a series of integers (from 0 to 28) separated by one or more white spaces. The program reads all the integers from these files and calculates the frequency of each number. It then generates a summary output that lists each number, along with the names of the files in which it appears and the number of times it appears in each file. Numbers that do not appear in any of the files are not included in the summary. The results are printed to the standard output.

## Components

- **`hash`** Contains the main function to run the program.
- **`hash_controller`** Controls the program flow by irritates through the inputted arguments and handles the content insertion.
- **`hash_table`** Hash table structure for saving and managing the readed data from the files.
- **`errors`** Structures and methods for handling errors in the program.

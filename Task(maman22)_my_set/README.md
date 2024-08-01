# my_set Program

### Short description:
A program that functions as an interactive "pocket computer" for performing operations on sets or groups. Commonly referred to as a "group theory calculator" or "set theory calculator."

## Components

- **myset:** Contains the main function to run the program, continuing execution until EOF, an error, or a manual termination is encountered.
-<kbd>**`myset`**</kbd>
<a href="#myset" style="background-color: #f0f0f0; border: 1px solid #ccc; border-radius: 3px; padding: 3px 10px; text-decoration: none; font-family: Arial, sans-serif; font-size: 14px;">**myset**</a>: 
: Contains the main function to run the program, continuing execution until EOF, an error, or a manual termination is encountered.

- **controller:** Controls the program flow by scanning the inputted command line and executing the corresponding instructions.
- **scan**: Responsible for tokenizing and parsing the scanned line.
- **set**: Contains operations on the sets.
- **errors**: Structures and methods for handling errors in the program.

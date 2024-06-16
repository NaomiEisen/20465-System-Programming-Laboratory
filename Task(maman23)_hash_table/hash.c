/* --------------------------- Function Prototypes -------------------------- */
void controller(int argc, char* argv[]);

/* -------------------------------------------------------------------------- */
/**
 * main function - activates the program.
 * @return 0
 */
int main(int argc, char* argv[]) {
    /* read files */
    controller(argc, argv);
    return 0; /* return value of main */
}
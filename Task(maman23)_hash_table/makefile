CC = gcc
CFLAGS = -Wall -ansi -pedantic -std=c90
SRC = hash.c hash_controller.c hash_table.c error.c
OBJ = $(SRC:.c=.o)
EXEC = hash

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

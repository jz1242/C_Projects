# Lines starting with # are comments

# Some variable definitions to save typing later on
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -g

# Default (first) target -- fill this in
hw6: hw6.o menuUtil.o
	$(CC) $(CFLAGS) -o hw6 hw6.o menuUtil.o

# Links the test executable
unittest: unittest.o prompts.o methods.o
	$(CC) $(CFLAGS) -o unittest unittest.o prompts.o methods.o

# Compiles hw5.c into an object file
hw6.o: hw6.c methods.h
	$(CC) $(CFLAGS) -c hw6.c

# Compiles dnasearch.c into an object file
prompts.o: prompts.c prompts.h
	$(CC) $(CFLAGS) -c prompts.c
	
menuUtil.o: menuUtil.c methods.h
	$(CC) $(CFLAGS) -c menuUtil.c

# Compiles unittest.c into an object file
unittest.o: unittest.c methods.h prompts.h
	$(CC) $(CFLAGS) -c unittest.c

# 'make clean' will remove intermediate & executable files
clean:
	rm -f *.o unittest hw6


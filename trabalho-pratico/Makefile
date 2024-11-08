# Compiler and flags
CC = gcc
CFLAGS = -Wall `pkg-config --cflags --libs glib-2.0` -I./include

# Directory for source files
SRC_DIR = src

# Main program source files
MAIN_SRC = main.c
MAIN_SRC += $(wildcard src/catalogos/*.c)
MAIN_SRC += $(wildcard src/entidades/*.c)
MAIN_SRC += $(wildcard src/manager_dados/*.c)
MAIN_SRC += $(wildcard src/modos_execucao/*.c)
MAIN_SRC += $(wildcard src/queries/*.c)

# Test source files
TEST_SRC = $(wildcard src/testes/*.c)
TEST_SRC = $(wildcard src/**/*.c)

# Object files for the main program and tests
MAIN_OBJ = $(MAIN_SRC:.c=.o)
TEST_OBJ = $(TEST_SRC:.c=.o)

# Executable names
MAIN_EXEC = programa-principal
TEST_EXEC = programa-testes

# Results directory
RESULTS_DIR = resultados

# Default target: compile both the main program and the test program
all: $(MAIN_EXEC) $(TEST_EXEC) $(RESULTS_DIR)

# Compile the main program
$(MAIN_EXEC): $(MAIN_OBJ)
	$(CC) $^ -o $@ $(CFLAGS)

# Compile the test executable
$(TEST_EXEC): $(TEST_OBJ)
	$(CC) $^ -o $@ $(CFLAGS)

# Compile the results folder
$(RESULTS_DIR):
	mkdir -p $(RESULTS_DIR)

# Generic rule to compile object files for both main program and tests
%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

# Clean up generated files
clean:
	rm -rf $(MAIN_OBJ) $(TEST_OBJ) $(MAIN_EXEC) $(TEST_EXEC) $(RESULTS_DIR)

.PHONY: all clean
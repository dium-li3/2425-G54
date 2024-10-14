CC = gcc
CFLAGS = -O2 -Wall `pkg-config --cflags --libs glib-2.0` 

BIN_DIR = bin
BLD_DIR = build
INC_DIR = include
SRC_DIR = src

SRC = $(wildcard $(SRC_DIR)/**/*c) main.c
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BLD_DIR)/%.o,$(SRC))

PROGRAM = programa-principal

.DEFAULT_GOAL = build

build: setup $(PROGRAM) 

$(PROGRAM): $(OBJS)
	$(CC) -I $(INC_DIR) -o $@ $^ $(CFLAGS)

$(BLD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) -c -I $(INC_DIR) -o $@ $^ $(CFLAGS)

.PHONY: setup
setup:
	@mkdir -p $(BLD_DIR)

.PHONY: clean
clean:
	@-rm -r $(BLD_DIR)
	@-rm $(PROGRAM)
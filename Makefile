SRC = ./src
INCLUDE = ./include
OBJ = ./obj
BIN = ./bin

all:
	gcc -Wall -g3 $(SRC)/*.c -I $(INCLUDE) main.c -o $(BIN)/programaTrab

run:
	$(BIN)/programaTrab

test:
	gcc -Wall -g3 $(SRC)/*.c -I $(INCLUDE) main.c -o $(BIN)/programaTrab
	$(BIN)/programaTrab
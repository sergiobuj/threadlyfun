##
## Sergio Botero
## Makefile dealer
##

SRC = src/sb_*.c
HEA = src/sb_*.h
CC = gcc
CFLAGS = -g
FEDFLAGS = -g -lpthread -lc
RM = rm -rf
BIN = dealer

$(BIN): $(SRC) $(HEA)
	$(CC) -o $@ $^ $(FEDFLAGS)

mac:	$(SRC) $(HEA)
	$(CC) -o $(BIN) $^ $(CFLAGS)

clean:
	$(RM) $(BIN) $(BIN).dSYM resultados


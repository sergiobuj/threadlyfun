##
## Sergio Botero
## Makefile dealer
##

SRC = src/sb_*.c
HEA = src/sb_*.h
CC = gcc
CFLAGS =
FEDFLAGS = -lpthread -lc
RM = rm -f
BIN = dealer

$(BIN): $(SRC) $(HEA)
	$(CC) -o $@ $^ $(CFLAGS)

fedora: $(SRC) $(HEA)
	$(CC) -o $(BIN) $^ $(FEDFLAGS)

clean:
	$(RM) $(BIN)
CC=gcc
CFLAGS=-W -Wall -ansi -pedantic
LDFLAGS=
EXEC=c-air1
SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)

all: $(EXEC)

run: all
	@./$(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	@rm -fr *.o

mrproper: clean
	@rm -fr $(EXEC)

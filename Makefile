CC=gcc
CFLAGS=-W -Wall
LDFLAGS=
EXEC=c-air1
TEXEC=test-c-air1
SRC=$(wildcard src/*.c)
TSRC:=$(SRC) test/test.c
TSRC:= $(filter-out src/main.c, $(TSRC))
OBJ=$(SRC:.c=.o)
TOBJ=$(TSRC:.c=.o)

all: $(EXEC)

run: all
	@./$(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

test: $(TEXEC)
	@./$(TEXEC)

$(TEXEC): $(TOBJ)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	@rm -fr *.o src/*.o test/*.o

mrproper: clean
	@rm -fr $(EXEC)
	@rm -fr $(TEXEC)

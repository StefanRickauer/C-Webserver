CC=gcc
LDFLAGS=# add Libraries here, e.g. -lcrypt

RM=rm -rf

SRC=src
HDR=include
OBJ=obj
BIN=bin

SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
HDRS=$(wildcard $(HDR)/*.h)

PROG=webserv

CFLAGS=-g -iquote $(HDR) -Wall -Wextra

all: $(BIN)/$(PROG)

release: CFLAGS=-iquote $(HDR) -Wall -O2 -DNDEBUG
release: clean
release: $(BIN)/$(PROG)

$(BIN)/$(PROG): $(OBJS) $(OBJ)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(OBJ)/%.o: $(SRC)/%.c $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ):
	mkdir -p $@
	mkdir -p $(BIN)

clean:
	$(RM) $(OBJ)
	$(RM) $(BIN)
	$(RM) $(PROG)

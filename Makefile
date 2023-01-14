CC=gcc
CFLAGS=-Wall

SVR=bit-reader

BIN_DIR=./bin/

run:
	@mkdir -p bin
	@$(CC) $(CFLAGS) -o $(BIN_DIR)$(SVR).o $(SVR).c && $(BIN_DIR)$(SVR).o

clean:
	@rm $(BIN_DIR)/*.o

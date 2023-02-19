CC=gcc
CFLAGS=-Wall

APP=bit-reader
FR=fraction

BIN_DIR=./bin/
SRC_DIR=./src/
LIBS_DIR=./libs/

INCLUDE = -Ilibs/
DEPS=$(LIBS_DIR)$(FR).h

# source: https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
#
# special macros $@ and $^, which are the left and right sides of the :, respectively.

%.o: %.c $(DEPS)
	$(CC) -c -o $(BIN_DIR)$@ $< $(CFLAGS)

run:
	@mkdir -p bin
	@$(CC) $(CFLAGS) -o $(BIN_DIR)$(APP).o $(SRC_DIR)$(APP).c $(LIBS_DIR)$(FR).c $(INCLUDE) && $(BIN_DIR)$(APP).o

clean:
	@rm $(BIN_DIR)/*.o

CC       := gcc
DEBUGGER := gdb
LD 		 := gcc
CFLAGS   := -c -pthread \
		   -Ilibs/zlib -I./ \
		   -D_POSIX_C_SOURCE -D_GNU_SOURCE
CDEBUG   := -O0 -g
CRELEASE := -O3 

LFLAGS   := -ldl -lm -lpthread -lz

SRC_DIR  := ./src
BIN_DIR  := ./bin # Anxiety kicks in if it not relative path :')
OBJ_DIR  := ./obj
TARGET   := ./bin/tiny-zip

SRC 	 := $(shell find $(SRC_DIR) -name '*.c')
OBJ      := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.c.o,$(filter %c,$(SRC)))

## FIlE RELATED MAKE

$(TARGET): $(OBJ) | $(BIN_DIR)
	$(LD) $^ -o $@ $(LFLAGS)

$(OBJ_DIR)/%.c.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $^ -o $@ 

$(OBJ_DIR):
	mkdir -p $@
$(BIN_DIR):
	mkdir -p $@

## NON FILE MAKE
.PHONY: all build setTimeAndDate debug release clean

clean: 
	rm -rfv $(OBJ_DIR)
	rm -rfv $(BIN_DIR)

all: debug

build: setTimeAndDate $(TARGET)

setTimeAndDate:
	./predef.sh

debug: CFLAGS += $(CDEBUG)
debug: build

release: CFLAGS += $(CRELEASE)
release: build


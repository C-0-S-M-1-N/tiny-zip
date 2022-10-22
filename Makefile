CC       = gcc
DEBUGGER = gdb
LINKER   = $(CC)
CFLAGS   = -std=c99 -O0 -pthread -Ilibs/zlib
LFLAGS   = -ldl -lm -lpthread -lz

TARGET    = tiny-zip
SRC_DIR   = src
BIN_DIR   = bin
OBJ_DIR   = $(BIN_DIR)

SRC      = $(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/*/*.c)
OBJ      = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

build: $(BIN_DIR) $(BIN_DIR)/$(TARGET)

$(BIN_DIR):
	mkdir -p $@

$(OBJ): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $< -o $@

$(BIN_DIR)/$(TARGET): $(OBJ)
	$(LINKER) $(OBJ) $(LFLAGS) -o $@

run: build
	./$(BIN_DIR)/$(TARGET)

debug: build
	$(DEBUGGER) $(BIN_DIR)/$(TARGET)

clean:
	rm -f $(OBJ)

remove: clean
	rm -f $(BIN_DIR)/$(TARGET)

.PHONY: build run debug clean remove

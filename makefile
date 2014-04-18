SRC := src
OBJ := obj
BIN := bin

CC := gcc
C_FILES := $(wildcard $(SRC)/*/*.c)
OBJ_FILES := $(addprefix $(OBJ)/,$(subst $(SRC)/, ,$(C_FILES:.c=.o)))
LD_FLAGS := -lm -L/usr/local/lib -Llibs/lib -lxml2
CC_FLAGS := -Wall -g -I/usr/local/include -Ilibs/include -std=c99

INSTALL := /usr/local/bin

build: bin/ obj/ cas

bin/:
	mkdir bin

obj/:
	mkdir obj

cas: $(OBJ_FILES)
	$(CC) $(CC_FLAGS) $^ $(LD_FLAGS) -o $(BIN)/$@

$(OBJ)/%.o: $(SRC)/%.c
	test -d $(dir $@) || mkdir $(dir $@)
	$(CC) $(CC_FLAGS) -c -o $@ $<

install:
	cp -r $(BIN)/* $(INSTALL)

.PHONY: clean
clean:
	rm -rf $(OBJ)/*
	rm -rf $(BIN)/*

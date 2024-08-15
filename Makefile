CC = gcc
CFLAGS = -I./include
LDFLAGS_SHARED = -shared -fPIC

SRC = src/main.c src/argparse.c src/utils.c src/image.c src/helpers.c src/editor.c
OBJ = $(SRC:src/%.c=build/%.o)

EXTERNAL = -lpng

TARGET = bin/image-edit
SHARED_TARGET = bin/image-edit.so
PACKAGE_TARGET = pyimage/libs/image-edit.so

all: clean build compile

build:
	mkdir -p build
	mkdir -p bin

compile: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(EXTERNAL)

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

move_package:
	mv $(SHARED_TARGET) $(PACKAGE_TARGET)
shared: clean build $(SHARED_TARGET) move_package

$(SHARED_TARGET): $(OBJ)
	$(CC) $(LDFLAGS_SHARED) -o $@ $^ $(EXTERNAL)

.PHONY: clean

clean:
	rm -rf build
	rm -rf bin

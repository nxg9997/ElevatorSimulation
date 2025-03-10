# Compiler
CC = g++
CFLAGS = -g -Wall -fpermissive

# Project name
PROJECT = build/out

INCS = -I./src/headers

SRCS = $(shell find src -name '*.cpp')
DIRS = $(shell find src -type d | sed 's/src/./g' ) 
OBJS = $(patsubst src/%.cpp,build/%.o,$(SRCS))

# Targets
$(PROJECT): buildrepo $(OBJS)
	$(CC) $(CFLAGS) $(INCS) $(OBJS) -o $@

build/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $(INCS) $< -o $@

clean:
	rm $(PROJECT) build -Rf

full: clean $(PROJECT)

buildrepo:
	mkdir -p build
	for dir in $(DIRS); do mkdir -p build/$$dir; done
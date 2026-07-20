CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra $(shell pkg-config --cflags sdl2)
LDLIBS := $(shell pkg-config --libs sdl2)
GAME ?= PONG

.PHONY: build run clean

build:
	$(CXX) $(CXXFLAGS) -o chip8.out main.cpp chip8.cpp screen.cpp $(LDLIBS)

run: build
	./chip8.out $(GAME)

clean:
	rm -f chip8.out

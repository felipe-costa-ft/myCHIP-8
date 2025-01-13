build:
	g++ -o chip8.out -lSDL2 main.cpp chip8.h chip8.cpp 


run:
	./chip8.out

clean:

	rm chip8.out
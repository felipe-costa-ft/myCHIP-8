build:
	g++ -o chip8.out main.cpp chip8.h chip8.cpp screen.h screen.cpp -lSDL2


run:
	./chip8.out

clean:

	rm chip8.out
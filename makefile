all: 
	g++ src/*.cpp -o main -lSDL2 -lSDL2_mixer

clean:
	rm main

.PHONY = all clean

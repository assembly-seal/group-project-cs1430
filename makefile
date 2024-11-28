all: 
	g++ src/*.cpp -o main -lSDL2 -lSDL2_mixer -lSDL2_image

clean:
	rm main

.PHONY = all clean

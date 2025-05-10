CC = gcc
CFLAGS = -O2 -Wall -Wextra
LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm 

all: snake_game

snake_game: main.c snake.c
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f snake_game
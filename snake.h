#ifndef SNAKE_H
#define SNAKE_H

#include <raylib.h>
#include <stdbool.h>

typedef enum Directions
{
    STOP = 10,
    UP = 1,
    DOWN = 2,
    LEFT = 3,
    RIGHT = 4,
} Direction;

typedef struct snake
{
    Rectangle snake_box;
    struct snake *next;
} Snake;

// Game functions
void InitGame(Snake **snake, int screenWidth, int screenHeight);
void ResetGame(Snake **snake, int screenWidth, int screenHeight);
void HandleInput(Direction *direction);
void UpdateGame(Snake **snake, Direction direction, Rectangle *loot, int screenWidth, int screenHeight, bool *lost);
void DrawGame(Snake *snake, Rectangle loot, bool lost);

// Snake functions
void SnakeMove(Snake **head, Direction dir);
bool CheckCollision(Snake *head);
void AddSnakeNode(Snake **head, Direction direction);

void LoadResources(void);
void UnloadResources(void);

typedef struct
{
    Sound eat;
    Sound game_over;
    Image icon;
} GameAssets;

extern GameAssets assets;

#endif
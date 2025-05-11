
#include "snake.h"
#include <stdlib.h>

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "snake game");
    SetTargetFPS(10);
    LoadResources();

    Snake *my_snake;
    InitGame(&my_snake, screenWidth, screenHeight);
    Direction direction = STOP;
    Rectangle loot = {
        (GetRandomValue(0, (screenWidth - 20) / 20) * 20),
        (GetRandomValue(0, (screenHeight - 20) / 20) * 20),
        20, 20};

    bool lost = false;

    while (!WindowShouldClose())
    {
        if (lost)
        {
            DrawGame(my_snake, loot, lost);
            if (IsKeyPressed(KEY_R))
            {
                ResetGame(&my_snake, screenWidth, screenHeight);
                direction = STOP;
                lost = false;
                loot.x = (GetRandomValue(0, (screenWidth - 20) / 20) * 20);
                loot.y = (GetRandomValue(0, (screenHeight - 20) / 20) * 20);
            }
            continue;
        }

        HandleInput(&direction);
        UpdateGame(&my_snake, direction, &loot, screenWidth, screenHeight, &lost);
        DrawGame(my_snake, loot, lost);
    }

    // Cleanup
    Snake *ptr = my_snake;
    while (ptr != NULL)
    {
        Snake *temp = ptr;
        ptr = ptr->next;
        free(temp);
    }

    CloseWindow();
    return 0;
}

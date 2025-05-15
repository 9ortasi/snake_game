#include "snake.h"
#include <stdlib.h>

void InitGame(Snake **snake, int screenWidth, int screenHeight)
{
    *snake = malloc(sizeof(Snake));
    (*snake)->snake_box = (Rectangle){screenWidth / 2, screenHeight / 2, 20, 20};
    (*snake)->next = NULL;
}

void ResetGame(Snake **snake, int screenWidth, int screenHeight)
{
    Snake *ptr = *snake;
    while (ptr != NULL)
    {
        Snake *temp = ptr;
        ptr = ptr->next;
        free(temp);
    }
    InitGame(snake, screenWidth, screenHeight);
}

void HandleInput(Direction *direction)
{
    if (IsKeyPressed(KEY_UP) && *direction != DOWN)
        *direction = UP;
    else if (IsKeyPressed(KEY_DOWN) && *direction != UP)
        *direction = DOWN;
    else if (IsKeyPressed(KEY_RIGHT) && *direction != LEFT)
        *direction = RIGHT;
    else if (IsKeyPressed(KEY_LEFT) && *direction != RIGHT)
        *direction = LEFT;
}

void UpdateGame(Snake **snake, Direction direction, Rectangle *loot, int screenWidth, int screenHeight, bool *lost)
{
    if (CheckCollisionRecs((*snake)->snake_box, *loot))
    {
        PlaySound(assets.eat);
        AddSnakeNode(snake, direction);
        loot->x = (GetRandomValue(0, (screenWidth - 20) / 20) * 20);
        loot->y = (GetRandomValue(0, (screenHeight - 20) / 20) * 20);
    }
    else
    {
        SnakeMove(snake, direction);
    }

    *lost = CheckCollision(*snake);
    if (*lost)
    {
        PlaySound(assets.game_over);
    }
    // Screen wrapping
    if ((*snake)->snake_box.x > screenWidth)
        (*snake)->snake_box.x = 0;
    if ((*snake)->snake_box.x < 0)
        (*snake)->snake_box.x = screenWidth;
    if ((*snake)->snake_box.y < 0)
        (*snake)->snake_box.y = screenHeight;
    if ((*snake)->snake_box.y > screenHeight)
        (*snake)->snake_box.y = 0;
}

void DrawGame(Snake *snake, Rectangle loot, bool lost)
{
    BeginDrawing();
    ClearBackground(BLACK);

    if (lost)
    {
        DrawText("You lost! Press [R] to restart", 200, 250, 30, RED);
    }
    else
    {
        DrawRectangleRec(loot, RED);

        int score = 0;
        Snake *ptr = snake;
        while (ptr != NULL)
        {
            DrawRectangleRec(ptr->snake_box, GREEN);
            score++;
            ptr = ptr->next;
        }
        DrawRectangle(snake->snake_box.x + snake->snake_box.width / 4, snake->snake_box.y + snake->snake_box.height / 4, 10, 10, DARKBLUE);
        DrawText(TextFormat("SCORE: %d", (score - 1) * 10), 10, 10, 20, WHITE);
    }

    EndDrawing();
}

void SnakeMove(Snake **head, Direction dir)
{
    if (dir == STOP)
        return;

    Snake *ptr = *head;
    Snake *newNull = *head;

    while (ptr->next != NULL)
    {
        newNull = ptr;
        ptr = ptr->next;
    }

    switch (dir)
    {
    case UP:
        ptr->snake_box.y = (*head)->snake_box.y - (*head)->snake_box.height;
        ptr->snake_box.x = (*head)->snake_box.x;
        break;
    case DOWN:
        ptr->snake_box.y = (*head)->snake_box.y + (*head)->snake_box.height;
        ptr->snake_box.x = (*head)->snake_box.x;
        break;
    case RIGHT:
        ptr->snake_box.x = (*head)->snake_box.x + (*head)->snake_box.width;
        ptr->snake_box.y = (*head)->snake_box.y;
        break;
    case LEFT:
        ptr->snake_box.x = (*head)->snake_box.x - (*head)->snake_box.width;
        ptr->snake_box.y = (*head)->snake_box.y;
        break;
    }

    if ((*head)->next != NULL)
        ptr->next = *head;

    newNull->next = NULL;
    *head = ptr;
}

bool CheckCollision(Snake *head)
{
    Snake *ptr = head->next;
    while (ptr != NULL)
    {
        if (CheckCollisionRecs(head->snake_box, ptr->snake_box))
        {
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

void AddSnakeNode(Snake **head, Direction direction)
{
    Snake *ptr = malloc(sizeof(Snake));
    ptr->snake_box = (*head)->snake_box;
    ptr->next = NULL;

    switch (direction)
    {
    case UP:
        ptr->snake_box.y -= ptr->snake_box.height;
        break;
    case DOWN:
        ptr->snake_box.y += ptr->snake_box.height;
        break;
    case LEFT:
        ptr->snake_box.x -= ptr->snake_box.width;
        break;
    case RIGHT:
        ptr->snake_box.x += ptr->snake_box.width;
        break;
    }

    ptr->next = *head;
    *head = ptr;
}

GameAssets assets;

void LoadResources(void)
{
    assets.icon = LoadImage("assets/icon.png");

    SetWindowIcon(assets.icon);

    InitAudioDevice();
    assets.eat = LoadSound("assets/eat.wav");
    assets.game_over = LoadSound("assets/game_over.wav");
}

void UnloadResources(void)
{
    UnloadImage(assets.icon);
    UnloadSound(assets.eat);
    UnloadSound(assets.game_over);
    CloseAudioDevice();
}
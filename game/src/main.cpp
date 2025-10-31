#include "raylib.h"
#include "raymath.h"
#include <iostream>

int main()
{
    int health = 100;
    health++;

    // Counts from 0 to 4
    for (int number = 0; number < 5; number++)
    {
        std::cout << number << std::endl;
    }
    
    // Counts from 1 to 5
    for (int number = 1; number <= 5; number++)
    {
        std::cout << number << std::endl;
    }

    InitWindow(800, 800, "Game");
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        DrawText("Hello world!", 10, 10, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

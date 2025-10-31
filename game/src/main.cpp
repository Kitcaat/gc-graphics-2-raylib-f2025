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

        for (int i = 0; i < 800; i += 80)
        {
            float size = 40.0f;

            // Move this to the bottom of the screen
            DrawRectangle(i, 50, size, size, BLUE); //Lines in the middle

            DrawRectangle(i, 750, size, size, PINK); //Rectangles at the bottom 

            // For vertical squares, use i as the y-coordinate, and set x to screen left (0) or screen right (750)

            DrawRectangle(750, i, size, size, YELLOW);

           

            DrawRectangle(i, 0, size, size, RED );
            
            DrawRectangle(i, 0, size, size, GREEN);
        }

        DrawText("Hello world!", 10, 10, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

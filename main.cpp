#include <raylib.h>

#include <iostream>

Color green = {173, 204, 96, 255};

int main(int, char **)
{
    std::cout << "Hello, from rlibSnakeGame!\n";

    const int screenWidth = 800;
    const int screenHeight = 800;

    const int targetFPS = 144;

    InitWindow(screenWidth, screenHeight, "Snek Game");

    SetTargetFPS(targetFPS);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        DrawFPS(10, 40);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

#include <deque>
#include <iostream>
#include <raylib.h>
#include <raymath.h>

using namespace std;

Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};
Color darkGrayOne = {51, 51, 51, 255};
Color darkGrayTwo = {102, 102, 102, 255};
Color darkGrayThree = {153, 153, 153, 255};

int cellSize = 32;
int cellCount = 25;
int offset = 75;

double lastUpdateTime = 0;

bool ElementInDeque(Vector2 element, deque<Vector2> &deque)
{
    for (unsigned int i = 0; i < deque.size(); i++)
    {
        if (Vector2Equals(deque[i], element))
            return true;
    }
    return false;
}

bool eventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

class Snake
{
  public:
    deque<Vector2> body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    Vector2 direction = {1, 0};
    bool addSegment = false;
    void Draw()
    {
        for (unsigned int i = 0; i < body.size(); i++)
        {
            float x = body[i].x;
            float y = body[i].y;
            Rectangle segment =
                Rectangle{offset + x * cellSize, offset + y * cellSize,
                          (float)cellSize, (float)cellSize};
            DrawRectangleRounded(segment, 0.5, 6, darkGreen);
        }
    }

    void Reset()
    {
        body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
        direction = {1, 0};
    }

    void Update()
    {
        body.push_front(Vector2Add(body[0], direction));

        if (addSegment == true)
        {
            addSegment = false;
        }
        else
        {
            body.pop_back();
        }
    }
};

class Food
{
  public:
    Vector2 position = {0, 0};
    Texture2D texture;

    Food(deque<Vector2> &body)
    {
        Image image = LoadImage("textures/apple.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        position = GenerateRandomPos(body);
    }

    ~Food() { UnloadTexture(texture); }

    void Draw()
    {
        DrawTexture(texture, offset + position.x * cellSize,
                    offset + position.y * cellSize, WHITE);
    }

    void BeEaten(Snake &snake) { position = GenerateRandomPos(snake.body); }

    Vector2 GenerateRandomCell()
    {
        float x = GetRandomValue(0, cellCount - 1);
        float y = GetRandomValue(0, cellCount - 1);
        return Vector2{x, y};
    }

    Vector2 GenerateRandomPos(deque<Vector2> &body)
    {
        Vector2 position = GenerateRandomCell();

        while (ElementInDeque(position, body))
        {
            position = GenerateRandomCell();
        }

        return position;
    }
};

class Game
{
  public:
    Game() {}

    int score = 0;
    Snake snake = Snake();
    Food food = Food(snake.body);

    void HandleInput()
    {
        if (IsKeyPressed(KEY_D) && snake.direction.x != -1)
        {
            snake.direction = {1, 0};
        }
        else if (IsKeyPressed(KEY_A) && snake.direction.x != 1)
        {
            snake.direction = {-1, 0};
        }
        else if (IsKeyPressed(KEY_S) && snake.direction.y != -1)
        {
            snake.direction = {0, 1};
        }
        else if (IsKeyPressed(KEY_W) && snake.direction.y != 1)
        {
            snake.direction = {0, -1};
        }
    }

    void GameOver()
    {
        snake.Reset();
        food.BeEaten(snake);
        score = 0;
        lastUpdateTime = GetTime();
    }

    void HandleFoodCollision()
    {
        if (Vector2Equals(snake.body[0], food.position))
        {
            food.BeEaten(snake);
            snake.addSegment = true;
            score++;
        }
    }

    void HandleEdgesCollision()
    {
        if (snake.body[0].x == cellCount || snake.body[0].x == -1 ||
            snake.body[0].y == cellCount || snake.body[0].y == -1)
        {
            GameOver();
        }
    }

    void HandleTailCollision()
    {
        deque<Vector2> headlessBody = snake.body;
        headlessBody.pop_front();
        if (ElementInDeque(snake.body[0], headlessBody))
        {
            GameOver();
        }
    }

    void Draw()
    {
        food.Draw();
        snake.Draw();
    }

    void Update()
    {
        HandleInput();

        if (eventTriggered(0.05))
        {
            HandleFoodCollision();
            HandleEdgesCollision();
            HandleTailCollision();

            snake.Update();
        }
    }
};

int main(int, char **)
{
    std::cout << "Hello, from rlibSnakeGame!\n";

    const int targetFPS = 144;

    InitWindow(2 * offset + cellSize * cellCount,
               2 * offset + cellSize * cellCount, "Snek Game");

    SetTargetFPS(targetFPS);

    Game game = Game();

    while (!WindowShouldClose())
    {
        BeginDrawing();

        game.Update();

        ClearBackground(green);

        DrawRectangleLinesEx(Rectangle{(float)offset - 5, (float)offset - 5,
                                       (float)cellSize * cellCount + 10,
                                       (float)cellSize * cellCount + 10},
                             5, darkGreen);
        DrawText("Snek by Manel", offset - 5, 20, 40, darkGreen);
        DrawText(TextFormat("%i", game.score), offset - 5,
                 offset + cellSize * cellCount + 10, 40, darkGreen);
        game.Draw();

        DrawFPS(10, 40);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

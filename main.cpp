/*******************************************************************************************
*
*   raylib [core] example - Basic 3d example
*
*   Welcome to raylib!
*
*   To compile example, just press F5.
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/
#include<iostream>
#include <raylib.h>
#include <deque>
#include<raymath.h>
using namespace std;

Color green = {173,204,96,255};
Color darkGreen = {43,51,24,255};

int cellSize = 30;
int cellCount = 25;

double lastUpdateTime=0;

bool eventTriggered(double interval)
{
    double currentTime = GetTime();
    if(currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;       
}

class Snake
{
public:
    deque<Vector2> body = {Vector2{6,9}, Vector2{5,9}, Vector2{4,9}};
    Vector2 direction ={1,0};

    void Draw()
    {
        for(unsigned int i=0; i<body.size(); i++)
        {
            float x = body[i].x;
            float y = body[i].y;
            Rectangle segment = Rectangle{x * cellSize,y * cellSize, (float)cellSize, (float)cellSize};
            DrawRectangleRounded(segment,0.5,6, darkGreen);

        }    
    }
    void Update()
    {
        body.pop_back();
        //body 0  is snakes head 
        body.push_front(Vector2Add(body[0],direction));
    }
    
};

class Food {
public:
    Vector2 position;

    Food() {
        // Initialize position with proper float values
        position.x = static_cast<float>(GetRandomValue(0, cellCount-1));
        position.y = static_cast<float>(GetRandomValue(0, cellCount-1));
    }

    void Draw() {
        DrawRectangle(position.x * cellSize, position.y * cellSize, cellSize, cellSize, darkGreen);
    }

    void randomizePosition() {
        position.x = static_cast<float>(GetRandomValue(0, cellCount-1));
        position.y = static_cast<float>(GetRandomValue(0, cellCount-1));
    }
};

class Game{
public:
    Snake snake = Snake();
    Food food = Food();

    void Draw()
    {
        food.Draw();
        snake.Draw();
    }
    void Update()
    {
        snake.Update();
    }
    void CheckCollisionWithFood()
    {
        if(Vector2Equals(snake.body[0], food.position))
        {
            food.randomizePosition();
            // Add new segment to snake bo
            snake.body.push_front(Vector2Add(snake.body[0],snake.direction));
        }
    }
};
int main() {
    InitWindow(750, 750, "NAGIN");
    SetTargetFPS(60);

    Game game =  Game();

    while(!WindowShouldClose()) {
        BeginDrawing();

            if(eventTriggered(0.2))
            {
                game.Update();
                game.CheckCollisionWithFood();
            }
            if(IsKeyPressed(KEY_UP) && game.snake.direction.y !=1)
            {
                game.snake.direction = {0,-1};
            }
            if(IsKeyPressed(KEY_DOWN)&& game.snake.direction.y !=-1)
            {
                game.snake.direction = {0,1};
            }
            if(IsKeyPressed(KEY_LEFT)&& game.snake.direction.x !=1)
            {
                game.snake.direction = {-1,-0};
            }
            if(IsKeyPressed(KEY_RIGHT)&& game.snake.direction.x !=-1)
            {
                game.snake.direction = {1,0};
            }

            ClearBackground(green);
            game.Draw();
            
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
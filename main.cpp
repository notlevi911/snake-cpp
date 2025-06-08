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

int main() {
    InitWindow(750, 750, "NAGIN");
    SetTargetFPS(60);

    Food food = Food();
    Snake snake = Snake();

    while(!WindowShouldClose()) {
        BeginDrawing();

            if(eventTriggered(0.2))
            {
                snake.Update();
            }
            if(IsKeyPressed(KEY_UP) && snake.direction.y !=1)
            {
                snake.direction = {0,-1};
            }
            if(IsKeyPressed(KEY_DOWN)&& snake.direction.y !=-1)
            {
                snake.direction = {0,1};
            }
            if(IsKeyPressed(KEY_LEFT)&& snake.direction.x !=1)
            {
                snake.direction = {-1,-0};
            }
            if(IsKeyPressed(KEY_RIGHT)&& snake.direction.x !=-1)
            {
                snake.direction = {1,0};
            }
            ClearBackground(green);
            food.Draw();
            snake.Draw();
            
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
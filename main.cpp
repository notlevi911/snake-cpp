
#include<iostream>
#include <raylib.h>
#include <deque>
#include<raymath.h>
using namespace std;

Color green = {173,204,96,255};
Color darkGreen = {43,51,24,255};

int cellSize = 30;
int cellCount = 25;
int offset = 100;


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

bool ElementInDeque(Vector2 a , deque<Vector2> b)
{
    for(unsigned int i = 0; i < b.size(); i++)
    {
        if(Vector2Equals(a, b[i]))
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
            Rectangle segment = Rectangle{offset+x * cellSize,offset+y * cellSize, (float)cellSize, (float)cellSize};
            DrawRectangleRounded(segment,0.5,6, darkGreen);

        }    
    }
    void Update()
    {
        body.pop_back();
        //body 0  is snakes head 
        body.push_front(Vector2Add(body[0],direction));
    }
    void Reset(){
        body = {Vector2{6,9}, Vector2{5,9}, Vector2{4,9}};
        direction ={1,0};
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
        DrawRectangle(offset+position.x * cellSize, offset+position.y * cellSize, cellSize, cellSize, darkGreen);
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
    bool running = true;
    int score = 0;
    int highScore = 0;
    float speed = 0.20;

    void Draw()
    {
        food.Draw();
        snake.Draw();
    }
    void Update()
    {
        if(running)
        {
            snake.Update();
            CheckCollisionWithFood();
            CheckCollionWithEdges();
            CheckCollisionWithTail();
        }
    }
    void CheckCollisionWithFood()
    {
        if(Vector2Equals(snake.body[0], food.position))
        {
            food.randomizePosition();
            // Add new segment to snake bo
            snake.body.push_front(Vector2Add(snake.body[0],snake.direction));
            score++;
            if(speed>=0.01){
            speed=speed-0.01;}
        }
    }
    void CheckCollionWithEdges()
    {
        if(snake.body[0].x ==cellCount || snake.body[0].x == -1)
        {
            GameOver();
        }
        if(snake.body[0].y ==cellCount || snake.body[0].y == -1)
        {
            GameOver();
        }
    }
    void CheckCollisionWithTail()
    {

        deque<Vector2> headlessBody = snake.body;
        headlessBody.pop_front();
        if(ElementInDeque(snake.body[0],headlessBody))
        {
            GameOver();
        }
    }
    void GameOver()
    {
        snake.Reset();
        food.randomizePosition();
        running = false;
        if (score >= highScore){
            highScore = score;
        }
        score = 0;
        speed = 0.2;
        


    }
};
int main() {
    InitWindow(2*offset+cellSize * cellCount, 2*offset+cellSize * cellCount, "NAGIN");
    SetTargetFPS(60);

    Game game =  Game();

    while(!WindowShouldClose()) {
        BeginDrawing();

            if(eventTriggered(game.speed))
            {
                game.Update();
                // could have made these two calls in the game update, but am too lazy
                //UPDATE I JUST DID CAUSE THAT WAS BETTER 
            }
            if(IsKeyPressed(KEY_UP) && game.snake.direction.y !=1)
            {
                game.snake.direction = {0,-1};
                game.running=true;
            }
            if(IsKeyPressed(KEY_DOWN)&& game.snake.direction.y !=-1)
            {
                game.snake.direction = {0,1};
                game.running=true;
            }
            if(IsKeyPressed(KEY_LEFT)&& game.snake.direction.x !=1)
            {
                game.snake.direction = {-1,-0};
                game.running=true;
            }
            if(IsKeyPressed(KEY_RIGHT)&& game.snake.direction.x !=-1)
            {
                game.snake.direction = {1,0};
                game.running=true;
            }

            ClearBackground(green);
            DrawRectangleLinesEx(Rectangle{(float)offset-5,(float)offset-5,(float)cellSize*cellCount+10,(float)cellSize*cellCount+10},5, darkGreen);
            DrawText("SAANP",offset-5,20,20,darkGreen);
            DrawText(TextFormat("%i",game.score),offset-5,offset+cellSize*cellCount+10,20,darkGreen);
            DrawText(TextFormat("HIGH SCORE %i",game.highScore),offset-5,offset+cellSize*cellCount+50,10,darkGreen);
            game.Draw();
            
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
#include <stdio.h>
#include "raylib.h"

void move(int * x);

int main ()
{
    // Position
    int posX, posY;
    int * pntX;
    int * pntY;
    posX = 100;
    posY = 100;
    pntX = &posX;
    pntY = &posY;

    // Initialization
    InitWindow(1280,960,"raylib - basic window");

    SetTargetFPS(60);
    printf("gametemplate");

    // Gameloop
    while(!WindowShouldClose())
    {
        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawRectangle(posX,100,100,100,GOLD);
            move(pntX);
        
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
void move(int * x) 
{
    if (IsKeyPressed(KEY_RIGHT))
    {
    (*x)+= GetFrameTime() * 1000;
    }
    if (IsKeyDown(KEY_RIGHT))
    {
    (*x)+= GetFrameTime() * 1500;
    }

    if (IsKeyPressed(KEY_LEFT))
    {
    (*x)-= GetFrameTime() * 1500;
    }

    if (IsKeyPressed(KEY_UP))
    {
    (*x)+= GetFrameTime() * 1000;
    }

    if (IsKeyPressed(KEY_DOWN))
    {
    (*x)+= GetFrameTime() * 1000;
    }
}
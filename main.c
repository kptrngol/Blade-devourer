#include <stdio.h>
#include "raylib.h"

void move(int * x,int * y);

int main ()
{
    // Position
    int posX, posY, windowX, windowY;
    windowX = 1280;
    windowY = 960;
    int * pntX;
    int * pntY;

    // Element initial positons
    posX = windowX/2;
    posY = windowY/2+300;
    pntX = &posX;
    pntY = &posY;

    // Initialization
    InitWindow(windowX,windowY,"raylib - basic window");

    SetTargetFPS(60);
    printf("gametemplate");

    // Gameloop
    while(!WindowShouldClose())
    {
        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawText("Hello Window",(windowX/2-125),(windowY/16+50/2),50,BLACK);
            DrawRectangle(posX,posY,32,32,GOLD);
            DrawRectangle(1280/2-125,960/2,250,50,RED);
            move(pntX,pntY);
            // collision()
        
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

void move(int * x,int * y) 
{
    if (IsKeyDown(KEY_RIGHT))
    {
    (*x)+= GetFrameTime() * 1000;
    }

    if (IsKeyDown(KEY_LEFT))
    {
    (*x)-= GetFrameTime() * 1000;
    }

    if (IsKeyDown(KEY_UP))
    {
    (*y)-= GetFrameTime() * 1000;
    }

    if (IsKeyDown(KEY_DOWN))
    {
    (*y)+= GetFrameTime() * 1000;
    }
}
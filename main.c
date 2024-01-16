#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"


/*
- Adding textures of skull and knives
- Adding dice which determines when there is a second element falling on the screen

*/


// Function declarations

void move(int * x,int * y);
void fallingObjects(int * paletteX,int * paletteY, int * fallingX, int * fallingY,int isGameOverStatus);
void collision(int skullX ,int skullY, int knifeX, int knifeY, int * pntScore, int * pntKnifeX,int * pntKnifeY, struct Sound sound);
void gameover(int windowBottom, int fallingY, int * GameOverStatus, int isGameOverStatus, int score);

int main ()
{
    // Variable declarations
    
    int isGameOver, posX, posY, windowX, windowY, fallX, fallY, score;
 
    int * pntIsGameOver;
    int * pntX;
    int * pntY;

    int * pntfX;
    int * pntfY;

    int * pntScore; 


    // Textures

    Texture2D background;
    Texture2D skull;
    Texture2D knife;

    // Sound

    Sound sound;
    Music music;


    // Variable definitions | initial positions of game elements

    isGameOver = 0;
    pntIsGameOver = &isGameOver; 

    windowX = 1280;
    windowY = 960;

    score = 0;

    posX = windowX/2;
    posY = windowY/2+150;

    fallX = windowX/2;
    fallY = 0;

    pntX = &posX;
    pntY = &posY;

    pntfX = &fallX;
    pntfY = &fallY;

    pntScore = &score;

    // Initialization

    InitWindow(windowX,windowY,"SKULLDEVOUR");
    
    InitAudioDevice();

    background = LoadTexture("./background.png");
    skull = LoadTexture("./skull.png");
    knife = LoadTexture("./knife.png");

    music = LoadMusicStream("music.mp3");
    sound = LoadSound("laugh.ogg");
    
    PlayMusicStream(music);
    SetTargetFPS(60);

    // Gameloop

    while(!WindowShouldClose())
    {
        // Elements movement and collision logic
        UpdateMusicStream(music);
        move(pntX,pntY);
        fallingObjects(pntX,pntY,pntfX,pntfY, isGameOver);
        collision(posX,posY,fallX,fallY,pntScore, pntfX, pntfY, sound);

        // Drawing loop

        BeginDrawing();

            ClearBackground(BLACK);
            DrawTexture(background,0,0,WHITE);
            DrawTexture(skull,posX,posY,WHITE);
            DrawTexture(knife,fallX,fallY,GREEN);
            DrawText(TextFormat("Score: %d",score),10,10,10,RED);
            gameover(windowY, fallY, pntIsGameOver,isGameOver, score);

        EndDrawing();

        // Adding collision boolean removal
    }
    UnloadSound(sound);
    StopMusicStream(music);
    UnloadTexture(background);
    UnloadTexture(knife);
    UnloadTexture(skull);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}

// Function definitions

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

}
void fallingObjects(int * paletteX,int * paletteY, int * fallingX, int * fallingY, int isGameOverStatus) 
{

    if (isGameOverStatus == 0) 
    {
        (*fallingY)+= GetFrameTime() * 500;
    }
    
}
void collision(int skullX ,int skullY, int knifeX, int knifeY, int * pntScore, int * pntKnifeX,int * pntKnifeY, struct Sound sound)
{
    int random = 0+ rand() / (RAND_MAX / (1280 +1) +1);

    if (((knifeX <= skullX+200)&&(knifeX >= skullX)) && ((knifeY >= skullY-50)&&(knifeY <= skullY+10)))
    {
        (*pntScore)++;
        *pntKnifeX = random;
        printf("%d",random);
        *pntKnifeY = 0;
    }
        if (((knifeX <= skullX+20)&&(knifeX >= skullX)) && ((knifeY >= skullY-50)&&(knifeY <= skullY+10)))
    {
        PlaySound(sound);
    }

}
void gameover(int windowBottom, int fallingY, int * GameOverStatus, int isGameOverStatus, int score) 
{
    if (fallingY >= 960)
    {
        *GameOverStatus = 1;
    }
    if (isGameOverStatus == 1) 
    {

        DrawText(TextFormat("YOU ARE EVEN MORE"),200,240,70,GREEN);
        DrawText(TextFormat("DEAD NOW! GAME OVER"),200,340,70,GREEN);
        DrawText(TextFormat("Score: %d",score),200,440,70,WHITE);
    }
}
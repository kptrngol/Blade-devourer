#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"


/*
- Issues:
Second object rendering
*/


// Function declarations

void move(int * x,int * y);
void fallingObjects(int * paletteX,int * paletteY, int * fallingX, int * fallingY,int isGameOverStatus);
void fallingObjects2(int * fallingY, int isGameOverStatus, int activation);
void collision(int skullX ,int skullY, int knifeX, int knifeY, int * pntScore, int * pntKnifeX,int * pntKnifeY, struct Sound sound, int knifeX2, int knifeY2, int * pntKnifeX2,int * pntKnifeY2, int activation);
void gameover(int windowBottom, int fallingY, int * GameOverStatus, int isGameOverStatus, int score);
void eventsRandomiser(int counterValue, int * counter, int * r, const double max);

int main ()
{
    // Variable declarations
    
    int activation, counter, randomValue, isGameOver, posX, posY, windowX, windowY, fallX, fallY, fallX2, fallY2, score;

    int * pntIsGameOver;
    int * pntX;
    int * pntY;
    int * pntfX;
    int * pntfY;
    int * pntfX2;
    int * pntfY2;
    int * pntScore; 
    int * pntRandomValue;
    int * pntCounter;

    // Textures

    Texture2D background;
    Texture2D skull;
    Texture2D knife;
    Texture2D knifeEx;

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
    fallX2 = 0;
    fallY2 = -300;
    counter = 0;
    randomValue = 0;
    activation = 0;

    pntX = &posX;
    pntY = &posY;
    pntfX = &fallX;
    pntfY = &fallY;
    pntfX2 = &fallX2;
    pntfY2 = &fallY2;
    pntScore = &score;
    pntCounter = &counter;
    pntRandomValue = &randomValue;

    // Initialization

    InitWindow(windowX,windowY,"BLADEDEVOUR");
    
    InitAudioDevice();

    background = LoadTexture("./background.png");
    skull = LoadTexture("./skull.png");
    knife = LoadTexture("./knife.png");
    knifeEx = LoadTexture("./knife.png");
    music = LoadMusicStream("music.mp3");
    sound = LoadSound("laugh.ogg");
    
    PlayMusicStream(music);
    SetTargetFPS(60);

    // Gameloop

    while(!WindowShouldClose())
    {
        // Elements movement and collision logic
        UpdateMusicStream(music);

        eventsRandomiser(counter, pntCounter, pntRandomValue, 360);
        counter++;

        move(pntX,pntY);

        fallingObjects(pntX,pntY,pntfX,pntfY, isGameOver);

        fallingObjects2(pntfY2, isGameOver, activation);

        collision(posX,posY,fallX,fallY,pntScore, pntfX, pntfY, sound, fallX2, fallY2, pntfX2, pntfY2, activation);

        // Drawing loop

        BeginDrawing();

            ClearBackground(BLACK);
            DrawTexture(background,0,0,WHITE);
            DrawTexture(skull,posX,posY,WHITE);
            if ((counter == randomValue) && ( fallY2 <= 0)) 
            {
                fallX2 = GetRandomValue(20,1260);
                activation = 1;
            }
            DrawTexture(knifeEx,fallX2,fallY2,RED);
            DrawTexture(knife,fallX,fallY,GREEN);
            DrawText(TextFormat("Score: %d",score),10,10,20,GREEN);
            DrawText(TextFormat("Random: %d",randomValue),10,45,20,WHITE);
            DrawText(TextFormat("Counter: %d", counter),10,65,20,WHITE);
            DrawText(TextFormat("Activation: %d", activation),10,85,20,WHITE);
            gameover(windowY, fallY, pntIsGameOver,isGameOver, score);

        EndDrawing();

        // Adding collision boolean removal
    }
    UnloadSound(sound);
    StopMusicStream(music);
    UnloadTexture(background);
    UnloadTexture(knife);
    UnloadTexture(knifeEx);
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
void fallingObjects2(int * fallingY, int isGameOverStatus, int activation) 
{

    if ((isGameOverStatus == 0) && (activation == 1))  
    {
        (*fallingY)+= GetFrameTime() * 600;
    }
    
}
void collision(int skullX ,int skullY, int knifeX, int knifeY, int * pntScore, int * pntKnifeX,int * pntKnifeY, struct Sound sound, int knifeX2, int knifeY2, int * pntKnifeX2,int * pntKnifeY2, int activation)
{
    int random = 0+ rand() / (RAND_MAX / (1280 +1) +1);

    if (((knifeX <= skullX+200)&&(knifeX >= skullX)) && ((knifeY >= skullY-50)&&(knifeY <= skullY+10)))
    {
        (*pntScore)++;
        *pntKnifeX = random;
        *pntKnifeY = 0;
    }
        if (((knifeX <= skullX+20)&&(knifeX >= skullX)) && ((knifeY >= skullY-50)&&(knifeY <= skullY+10)))
    {
        PlaySound(sound);
    }

    // Second knife collision logic

        if (((knifeX2 <= skullX+200)&&(knifeX2 >= skullX)) && ((knifeY2 >= skullY-50)&&(knifeY2 <= skullY+10)))
    {
        (*pntScore)+=10;
        // *pntknifeX2 = random;
        *pntKnifeY2 = -300;
        activation = 0;
    }
        if (((knifeX2 <= skullX+20)&&(knifeX2 >= skullX)) && ((knifeY2 >= skullY-50)&&(knifeY2 <= skullY+10)))
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
void eventsRandomiser(int counterValue, int * counter, int * r, const double max)
{
    if (counterValue == 1) 
    {
        
        (*r) = GetRandomValue(0,max); 


    } else if (counterValue == max)
    {
        *counter = 0;
    }
}
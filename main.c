#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"


/*
#Issues:
-green sword stop rendering after loosing one
*/


// Function declarations

void move(int * x,int * y);
void fallingObjects(int * paletteX,int * paletteY, int * fallingX, int * fallingY,int isGameOverStatus);
void fallingObjects2(int * fallingY, int isGameOverStatus, int activation);
void collision(int skullX ,int skullY, int knifeX, int knifeY, int * pntScore, int * pntKnifeX,int * pntKnifeY, struct Sound sound, int knifeX2, int knifeY2, int * pntKnifeX2,int * pntKnifeY2, int activation, int * php);
void gameover(int windowBottom, int fallingY, int * GameOverStatus, int isGameOverStatus, int score, int hp, int * php);
void eventsRandomiser(int counterValue, int * counter, int * r, const double max);

int main ()
{
    // Variable declarations
    
    int activation, counter, randomValue, isGameOver, posX, posY, windowX, windowY, fallX, fallY, fallX2, fallY2, score, hp;

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
    int * pntHP;

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
    hp = 2;
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
    activation = 1;

    pntHP = &hp;
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

        if(activation == 1)
        {
            fallingObjects2(pntfY2, isGameOver, activation);
        }    

        collision(posX,posY,fallX,fallY,pntScore, pntfX, pntfY, sound, fallX2, fallY2, pntfX2, pntfY2, activation, pntHP);

        // Drawing loop

        BeginDrawing();

            ClearBackground(BLACK);
            DrawTexture(background,0,0,WHITE);
            DrawTexture(skull,posX,posY,WHITE);
            if ((counter == randomValue) && (fallY2 >= 0)) 
            {
                fallX2 = GetRandomValue(20,1260);
                fallY2 = 0;
                activation = 1;
            }
            DrawTexture(knife,fallX,fallY,GREEN);
            if ((activation == 1)) {
                DrawTexture(knifeEx,fallX2,fallY2,RED);
            }
            DrawText(TextFormat("DeathPoits (Score): %d", score),10,10,15,GREEN);
            // DrawText(TextFormat("DeathEssence (HP): %d", hp),10,30,15,PURPLE);
            // DrawText(TextFormat("IsGameOver?: %d", isGameOver),10,50,15,PURPLE);

            // Dev info 

            // DrawText(TextFormat("Random: %d",randomValue),10,45,20,WHITE);
            // DrawText(TextFormat("Counter: %d", counter),10,65,20,WHITE);
            // DrawText(TextFormat("Activation: %d", activation),10,85,20,WHITE);
            // DrawText(TextFormat("x: %d", fallX2),10,105,20,WHITE);
            // DrawText(TextFormat("y: %d", fallY2),10,125,20,WHITE);

            gameover(windowY, fallY, pntIsGameOver,isGameOver, score, hp, pntHP);

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
void collision(int skullX ,int skullY, int knifeX, int knifeY, int * pntScore, int * pntKnifeX,int * pntKnifeY, struct Sound sound, int knifeX2, int knifeY2, int * pntKnifeX2,int * pntKnifeY2, int activation, int * php)
{

    if (((knifeX+45 <= skullX+155)&&(knifeX+45 >= skullX+35)) && ((knifeY+200 >= skullY+140)&&(knifeY+200 <= skullY+190)))
    {
        (*pntScore)++;
        *pntKnifeX = GetRandomValue(20,1240);
        *pntKnifeY = 0;
    }


    // Second knife collision logic

        if (((knifeX2+45 <= skullX+165)&&(knifeX2+45 >= skullX+25)) && ((knifeY2+200 >= skullY+130)&&(knifeY2+200 <= skullY+200)))
    {
        PlaySound(sound);
        (*pntScore)+=10;
        (*php)++;
        activation = 0;
        (*pntKnifeX2) = GetRandomValue(20,1240);
        (*pntKnifeY2) = 0;
    } else if((knifeY2 >= skullY))
    {
        activation = 0;
    }

}
void gameover(int windowBottom, int fallingY, int * GameOverStatus, int isGameOverStatus, int score, int hp, int * php) 
{
    if ((fallingY >= 960) && (hp >= 1))
    {
        (*php)--;
    }

    if (hp == 0)
    {
        (*GameOverStatus) = 1;    
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
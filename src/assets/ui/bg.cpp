#include "raylib.h"
#include <iostream>
#include "../../class/class.h"


struct Cloud {
    Vector2 pos; 
    float speed;
    int textureIndex;
};


static Texture2D bgFoor;
static Texture2D Tree;
static float scrolling = 0.0;
static Texture2D cloudT[3];
const int mClouds = 15;
static Cloud clouds[mClouds];

static Rectangle rFoor = { 0.0f, 480.0f, 20.0f, 80.0f };
static Rectangle rTree = { 0.0f, 460.0f, 20.0f, 80.0f };

void InitBackGround() {
    bgFoor = LoadTexture("assets/sprites/background/dirt.png");
    Tree = LoadTexture("assets/sprites/background/tree.png");
    cloudT[0] = LoadTexture("assets/sprites/background/cloud1.png"); 
    cloudT[1] = LoadTexture("assets/sprites/background/cloud2.png");
    cloudT[2] = LoadTexture("assets/sprites/background/cloud3.png");

    for(int i = 0; i < mClouds; i++){
        clouds[i].pos.x = (float)(rand() % 900); // Espacio horizontal
        clouds[i].pos.y = (float)(rand() % 150 + 30); // Altura aleatoria 
        clouds[i].textureIndex = (float)(rand() % 3); // Elegir nube aleatoria
        clouds[i].speed = (float)(rand() % 10 + 10); // Velocidad lenta entre 10 y 20.
    }
}

void UpdateBackGround(float speed){
    scrolling -=speed * GetFrameTime();
    
    if(scrolling <= -bgFoor.width){
        scrolling = 0.0;
    }

    for(int i = 0; i < mClouds; i++){
        clouds[i].pos.x -= clouds[i].speed * GetFrameTime();

        Texture2D cCt = cloudT[clouds[i].textureIndex];
        
        if(clouds[i].pos.x < - cCt.width){
            clouds[i].pos.x = 800.0f + (float)(rand() % 300);
            clouds[i].pos.y = (float)(rand() % 150 + 30);
            clouds[i].textureIndex = rand() % 3;
            clouds[i].speed = float(rand() % 10 + 10);
        }
    }
}

void DrawingBackGround(){
    DrawTextureEx(bgFoor, (Vector2){ scrolling, 480.0}, 0.0, 1.0, WHITE);
    float floorY = 480.0;
    float screenWidth = 800;
    int rep = (floorY / screenWidth) + 10;
    int rep2 = (floorY / 80) + 40;
    for(int i = 0; i < rep; i++){
        float poX = scrolling + (i * bgFoor.width);
        DrawTextureEx(bgFoor,(Vector2){poX , floorY}, 0.0, 1.0, WHITE);
    }

    for(int i = 0; i < rep2; i++){
        float poX = scrolling + (i * Tree.width);
        DrawTextureEx(Tree,(Vector2){poX , 460.0f}, 0.0, 1.0, WHITE);
    }

    for(int i = 0; i < mClouds; i++){
        Texture2D t = cloudT[clouds[i].textureIndex];
        DrawTextureEx(t, clouds[i].pos, 0.0f, 1.0f, WHITE);
    }
}

void UnloadBackGround(){
    UnloadTexture(bgFoor);
    UnloadTexture(Tree);
    for(int i = 0; i < mClouds; i++){
        UnloadTexture(cloudT[i]);
    }
}

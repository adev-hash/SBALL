#include "raylib.h"
#include <iostream>
#include "../../class/class.h"

static Texture2D bgFoor;
static Texture2D Tree;
static float scrolling = 0.0;

static Rectangle rFoor = { 0.0f, 480.0f, 20.0f, 80.0f };
static Rectangle rTree = { 0.0f, 460.0f, 20.0f, 80.0f };

void InitBackGround() {
    bgFoor = LoadTexture("assets/sprites/background/dirt.png");
    Tree = LoadTexture("assets/sprites/background/tree.png");
}

void UpdateBackGround(float speed){
    scrolling -=speed * GetFrameTime();
    
    if(scrolling <= -bgFoor.width){
        scrolling = 0.0;
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
}

void UnloadBackGround(){
    UnloadTexture(bgFoor);
}

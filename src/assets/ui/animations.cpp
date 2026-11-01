#include "raylib.h"
#include <iostream>
#include "../../class/class.h"

struct Bird{
    Vector2 pos; 
    float speed;
    int currentF; 
    float frTime;
};

const int mBirds = 2;
static Bird birds[mBirds];

static Texture2D birdFr;

const int TotalFrames = 4; // no. total de fotogramas 
static float frameWith = 0.0f;
static float frameHeight = 0.0f;


void InitAnimations(){
    Image birdsFr= LoadImage("assets/sprites/objects/birds.png");

    Rectangle box = GetImageAlphaBorder(birdsFr, 0.0f); // área con píxeles visibles
    ImageCrop(&birdsFr, box);                           // elimina el margen vacío

    birdFr = LoadTextureFromImage(birdsFr);
    UnloadImage(birdsFr);
    SetTextureFilter(birdFr, TEXTURE_FILTER_POINT);

    frameWith  = birdFr.width / TotalFrames;
    frameHeight = birdFr.height;
    frameWith = (float)birdFr.width / TotalFrames;
    frameHeight = (float)birdFr.height;

    for(int i = 0; i<mBirds; i++){
        birds[i].pos.x = (float)(rand() % 900 + 800);
        birds[i].pos.y = (float)(rand() % 200 + 50);
        birds[i].speed = (float)(rand() % 30 + 40);
        birds[i].currentF = 0;
        birds[i].frTime = 0.0f;
    }
}

void executeAnimations(float speed){
    for(int i = 0; i<mBirds; i++){
        birds[i].pos.x -= (birds[i].speed + speed * 1.0f) * GetFrameTime();

        birds[i].frTime += GetFrameTime();

        if(birds[i].frTime >= 0.15f){
            birds[i].frTime = 0.0f;
            birds[i].currentF = (birds[i].currentF + 1) % TotalFrames;
        }

        if(birds[i].pos.x < -frameWith){
            birds[i].pos.x= 850.0f + (float)(rand() % 300);
            birds[i].pos.y = (float)(rand() % 200 + 50);
        }


        Rectangle sourceRec = {birds[i].currentF * frameWith, 0.0f, frameWith, frameHeight};
        Rectangle destRec = {birds[i].pos.x, birds[i].pos.y, frameWith,frameHeight};

        Vector2 origin = { 0.0f, 0.0f};
        
        DrawTexturePro(birdFr, sourceRec, destRec, origin, 0.0, WHITE);
    }

}

void UnloadAnimations(){
    UnloadTexture(birdFr);
}

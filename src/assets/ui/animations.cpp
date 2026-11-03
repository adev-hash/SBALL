#include "raylib.h"
#include <iostream>
#include "../../class/class.h"


//Birds of Background
struct Bird{
    Vector2 pos; 
    float speed;
    int currentF; 
    float frTime;
};

const int mBirds = 2;
static Bird birds[mBirds];
static Texture2D birdFr;
const int birdFrames = 4; // no. total de fotogramas 

static float birdsFWith = 0.0f;
static float birdsFHeight = 0.0f;

//Plane user 

struct Plane
    {
        Vector2 position = {0,0};
        float planeSpeed=5.0;
        int currentF;
        float fPtime;
};

static Plane planes;
static Texture2D planeTexture;
const int planeFrames = 5;

static float planeFWith = 0.0f;
static float planeFHeight = 0.0f;



void InitPlane(){
    Image planeImage = LoadImage("assets/sprites/objects/planesprites.png");

    Rectangle planeBox = GetImageAlphaBorder(planeImage, 0.0f); // área con píxeles visibles
    ImageCrop(&planeImage, planeBox);   
    
    // elimina el margen vacío

    planeTexture = LoadTextureFromImage(planeImage);
    UnloadImage(planeImage);

    SetTextureFilter(planeTexture, TEXTURE_FILTER_POINT);

    planeFWith  = planeTexture.width /planeFrames +10;
    planeFHeight = planeTexture.height;
    planeFWith = (float)planeTexture.width /planeFrames;
    planeFHeight = (float)planeTexture.height;
    planes.fPtime = 0.0f;
}

void ShowPlane(){
    planes.fPtime += GetFrameTime();

    if(planes.fPtime >= 0.05){
        planes.fPtime = 0.0f;
        planes.currentF = (planes.currentF + 1) % planeFrames;
    }

    if(IsKeyDown(KEY_W)) {
        if(planes.position.y == 0.0f){
            planes.position.y = 0.0f;
        }else{
            planes.position.y -= planes.planeSpeed;
        }
    }else if(IsKeyDown(KEY_S)){
        if(planes.position.y == 340.0f){
            planes.position.y = 340.0f;
        }else{
            planes.position.y += planes.planeSpeed;
        }
    }

     Rectangle srPlane = {(float)(planes.currentF * planeFWith), 0.0f, planeFWith, planeFHeight};
     Rectangle drPlane = {planes.position.x, planes.position.y, planeFWith, planeFHeight};
     DrawTexturePro(planeTexture, srPlane, drPlane,{0,0},0,WHITE);
}

void UnloadPlane(){
    UnloadTexture(planeTexture);
}


void InitBirds(){
    Image birdsFr= LoadImage("assets/sprites/objects/birds.png");

    Rectangle box = GetImageAlphaBorder(birdsFr, 0.0f); // área con píxeles visibles
    ImageCrop(&birdsFr, box);                           // elimina el margen vacío

    birdFr = LoadTextureFromImage(birdsFr);
    UnloadImage(birdsFr);
    SetTextureFilter(birdFr, TEXTURE_FILTER_POINT);

    birdsFWith  = birdFr.width / birdFrames;
    birdsFHeight = birdFr.height;
    birdsFWith = (float)birdFr.width / birdFrames;
    birdsFHeight = (float)birdFr.height;

    for(int i = 0; i<mBirds; i++){
        birds[i].pos.x = (float)(rand() % 900 + 800);
        birds[i].pos.y = (float)(rand() % 200 + 50);
        birds[i].speed = (float)(rand() % 30 + 40);
        birds[i].currentF = 0;
        birds[i].frTime = 0.0f;
    }
}

void showBirds(float speed){
    for(int i = 0; i<mBirds; i++){
        birds[i].pos.x -= (birds[i].speed + speed * 1.0f) * GetFrameTime();

        birds[i].frTime += GetFrameTime();

        if(birds[i].frTime >= 0.15f){
            birds[i].frTime = 0.0f;
            birds[i].currentF = (birds[i].currentF + 1) % birdFrames;
        }

        if(birds[i].pos.x < -birdsFWith){
            birds[i].pos.x= 850.0f + (float)(rand() % 300);
            birds[i].pos.y = (float)(rand() % 200 + 50);
        }


        Rectangle sourceRec = {birds[i].currentF * birdsFWith, 0.0f, birdsFWith, birdsFHeight};
        Rectangle destRec = {birds[i].pos.x, birds[i].pos.y, birdsFWith,birdsFHeight};

        DrawTexturePro(birdFr, sourceRec, destRec, {0.0f, 0.0f}, 0.0, WHITE);
    }

}

void UnloadBirds(){
    UnloadTexture(birdFr);
}
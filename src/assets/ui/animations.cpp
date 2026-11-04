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
//Plane user 
struct Avion
{
    Vector2 posicion = {0,0};
    float velocidad=5.0;
    int currentF;
    float fPtime;
};

const int mBirds = 2;
static Bird birds[mBirds];

static Texture2D birdFr;

const int TotalFrames = 4; // no. total de fotogramas 
static float frameWith = 0.0f;
static float frameHeight = 0.0f;

static Avion av;
static Texture2D planeTexture;
const int planeFrames = 5;

static float planeFWith = 0.0f;
static float planeFHeight = 0.0f;

double tiempo_juego = 0;//Tiempo que lleva el jugador jugando

void iniciarAvion(){
    Image planeImage = LoadImage("assets/sprites/objects/planesprites.png");

    Rectangle planeBox = GetImageAlphaBorder(planeImage, 0.0f); // Area con pixeles visibles
    ImageCrop(&planeImage, planeBox);   
    
    // elimina el margen vacio

    planeTexture = LoadTextureFromImage(planeImage);
    UnloadImage(planeImage);

    SetTextureFilter(planeTexture, TEXTURE_FILTER_POINT);

    planeFWith  = planeTexture.width /planeFrames +10;
    planeFHeight = planeTexture.height;
    planeFWith = (float)planeTexture.width /planeFrames;
    planeFHeight = (float)planeTexture.height;
    av.fPtime = 0.0f;
}

void mostrarAvion(){
    av.fPtime += GetFrameTime();
    if(av.fPtime >= 0.05){
        av.fPtime = 0.0f;
        av.currentF = (av.currentF + 1) % planeFrames;
    }
    tiempo_juego+=GetFrameTime();
    srPlane = {(float)(av.currentF * planeFWith), 0.0f, planeFWith, planeFHeight};
    drPlane = {av.posicion.x, av.posicion.y, planeFWith, planeFHeight};
    DrawTexturePro(planeTexture, srPlane, drPlane,{0,0},0,WHITE);
}
void accionesAvion(){
        if(tiempo_juego >= 60.0f){
        av.velocidad++;
        tiempo_juego = 0.0f;
    }
    if(IsKeyDown(KEY_W)) {
        if(av.posicion.y <= 1.0f){
            av.posicion.y = 1.0f;            
        }
        else{
            av.posicion.y -= av.velocidad;
        }
        DrawRectangleLinesEx(drPlane,3,RED);
    }
    else if(IsKeyDown(KEY_S)) {
        if(av.posicion.y >= 340.0f){
            av.posicion.y = 340.0f;
        }
        else{
            av.posicion.y += av.velocidad;
        }
        DrawRectangleLinesEx(drPlane,3,RED);
    }
    //bool choco = CheckCollisionRecs(drPlane,rec2);
    //Devuelve true si dos rectángulos se superponen. Ideal para juegos de plataformas o sprites cuadrados
}
void descargarAvion(){
    UnloadTexture(planeTexture);
}

void iniciarAves(){
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

void ejecutarAnimaciones(float speed){
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

void descargarAves(){
    UnloadTexture(birdFr);
}
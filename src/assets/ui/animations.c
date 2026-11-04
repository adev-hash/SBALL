#include "raylib.h"
#include "../../class/class.h"
#include <stdlib.h>

// Pajaros del fondo!
typedef struct {
    Vector2 pos;
    float speed;
    int currentF; 
    float frTime;
} Bird;

// Avion del jugador!
typedef struct {
    Vector2 posicion;
    float velocidad;
    int currentF;
    float fPtime;
} Avion;

#define M_BIRDS 2 // Número máximo de pájaros
static Bird birds[M_BIRDS];

static Texture2D birdFr;

#define TOTAL_FRAMES 4 // no. total de fotogramas 
static float frameWith = 0.0f;
static float frameHeight = 0.0f;

static Avion av;
static Texture2D planeTexture;
#define PLANE_FRAMES 5

static float planeFWith = 0.0f;
static float planeFHeight = 0.0f;

static double tiempo_juego = 0.0; // Tiempo que lleva el jugador jugando

void iniciarAvion(void) {
    Image planeImage = LoadImage("assets/sprites/objects/planesprites.png");

    Rectangle planeBox = GetImageAlphaBorder(planeImage, 0.0f); // Area con pixeles visibles
    ImageCrop(&planeImage, planeBox);   
    
    planeTexture = LoadTextureFromImage(planeImage);
    UnloadImage(planeImage);

    SetTextureFilter(planeTexture, TEXTURE_FILTER_POINT);

    planeFWith = (float)planeTexture.width / PLANE_FRAMES;
    planeFHeight = (float)planeTexture.height;
    
    // Inicialización de campos de la estructura en C
    av.posicion = (Vector2){ 0.0f, 0.0f };
    av.velocidad = 5.0f;
    av.currentF = 0;
    av.fPtime = 0.0f;
}

void mostrarAvion(void) {
    av.fPtime += GetFrameTime();

    if(av.fPtime >= 0.05f){
        av.fPtime = 0.0f;
        av.currentF = (av.currentF + 1) % PLANE_FRAMES;
    }
    
    tiempo_juego += GetFrameTime();
    if(tiempo_juego >= 60.0){
        av.velocidad++;
        tiempo_juego = 0.0;
    }
    
    if(IsKeyDown(KEY_W)) {
        if(av.posicion.y <= 1.0f){
            av.posicion.y = 1.0f;            
        } else {
            av.posicion.y -= av.velocidad;
        }
    } else if(IsKeyDown(KEY_S)) {
        if(av.posicion.y >= 340.0f){
            av.posicion.y = 340.0f;
        } else {
            av.posicion.y += av.velocidad;
        }
    }
    
    Rectangle srPlane = { (float)(av.currentF * planeFWith), 0.0f, planeFWith, planeFHeight };
    Rectangle drPlane = { av.posicion.x, av.posicion.y, planeFWith, planeFHeight };
    DrawTexturePro(planeTexture, srPlane, drPlane, (Vector2){0, 0}, 0.0f, WHITE);
}

void descargarAvion(void) {
    UnloadTexture(planeTexture);
}

void iniciarAves(void) {
    Image birdsFrImg = LoadImage("assets/sprites/objects/birds.png");

    Rectangle box = GetImageAlphaBorder(birdsFrImg, 0.0f); // área con píxeles visibles
    ImageCrop(&birdsFrImg, box);                           // elimina el margen vacío

    birdFr = LoadTextureFromImage(birdsFrImg);
    UnloadImage(birdsFrImg);
    SetTextureFilter(birdFr, TEXTURE_FILTER_POINT);

    frameWith = (float)birdFr.width / TOTAL_FRAMES;
    frameHeight = (float)birdFr.height;

    for(int i = 0; i < M_BIRDS; i++){
        birds[i].pos.x = (float)(rand() % 900 + 800);
        birds[i].pos.y = (float)(rand() % 200 + 50);
        birds[i].speed = (float)(rand() % 30 + 40);
        birds[i].currentF = 0;
        birds[i].frTime = 0.0f;
    }
}

void ejecutarAnimaciones(float speed) {
    for(int i = 0; i < M_BIRDS; i++){
        birds[i].pos.x -= (birds[i].speed + speed * 1.0f) * GetFrameTime();

        birds[i].frTime += GetFrameTime();

        if(birds[i].frTime >= 0.15f){
            birds[i].frTime = 0.0f;
            birds[i].currentF = (birds[i].currentF + 1) % TOTAL_FRAMES;
        }

        if(birds[i].pos.x < -frameWith){
            birds[i].pos.x = 850.0f + (float)(rand() % 300);
            birds[i].pos.y = (float)(rand() % 200 + 50);
        }

        Rectangle sourceRec = { (float)(birds[i].currentF * frameWith), 0.0f, frameWith, frameHeight };
        Rectangle destRec = { birds[i].pos.x, birds[i].pos.y, frameWith, frameHeight };

        Vector2 origin = { 0.0f, 0.0f };
        
        DrawTexturePro(birdFr, sourceRec, destRec, origin, 0.0f, WHITE);
    }
}

void descargarAves(void) {
    UnloadTexture(birdFr);
}
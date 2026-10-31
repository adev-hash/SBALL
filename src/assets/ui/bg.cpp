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
static Texture2D Sun;
static float sunR = 0.0f; // giros del sol 
static Texture2D Logo;
static bool showLogo = true;
static Texture2D Mountains;

void InitBackGround() {
    bgFoor = LoadTexture("assets/sprites/background/dirt.png");
    Tree = LoadTexture("assets/sprites/background/tree.png");
    cloudT[0] = LoadTexture("assets/sprites/background/cloud1.png"); 
    cloudT[1] = LoadTexture("assets/sprites/background/cloud2.png");
    cloudT[2] = LoadTexture("assets/sprites/background/cloud3.png");
    Sun = LoadTexture("assets/sprites/background/sun.png");
    Logo = LoadTexture("assets/sprites/background/logo.png");
    Mountains = LoadTexture("assets/sprites/background/mountains.png");


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

    // Le damos una velocidad de 20 revoluciones y la reiniciamos cada angulo de 360 grados
    sunR += 1.0f * GetFrameTime();

    if(sunR >= 360.0f){
        sunR = 0.0f;
    }
}

void ShowLogo(bool visible){
    showLogo = visible;
}

void DrawingBackGround(){

    float screenWidth = 800;
    int rep = (480.0f / screenWidth) + 10;
    int rep2 = (480.0f / 80) + 40;
    int rep3 = (460.0f / 80) + 100;
    for(int i = 0; i < rep; i++){
        float poX = scrolling + (i * bgFoor.width);
        DrawTextureEx(bgFoor,(Vector2){poX , 480.0f}, 0.0, 1.0, WHITE);
    }

    for(int i = 0; i < rep3; i++){
        float poX = scrolling + (i * Mountains.width) -100; // determina la posicion en la que se hace la repeticion.
        DrawTextureEx(Mountains,(Vector2){poX , 460.0f}, 0.0, 2.0, WHITE);
    }

    for(int i = 0; i < rep2; i++){
        float poX = scrolling + (i * Tree.width);
        DrawTextureEx(Tree,(Vector2){poX , 460.0f}, 0.0, 1.0, WHITE);
    }



    Vector2 sunOrg = { (float)Sun.width / 40.0f, (float)Sun.height};
    Rectangle SunRise =  {0.0f, 0.0f, (float)Sun.width, (float)Sun.height};
    Rectangle SunRest = {650.0f, 50.0f, (float)Sun.width, (float)Sun.height};
    DrawTexturePro(Sun, SunRise, SunRest, sunOrg, sunR, WHITE);

    
    for(int i = 0; i < mClouds; i++){
        Texture2D t = cloudT[clouds[i].textureIndex];
        DrawTextureEx(t, clouds[i].pos, 0.0f, 1.0f, WHITE);
    }

    //oordenadas x,y, rotacion, tamaño, dibujar imagen con sus colores originales.
    if(showLogo){
        DrawTextureEx(Logo,(Vector2){320 , 100.0f}, 0.0, 3.0f, WHITE);

    }
    
    //En caso de nuevos objetos, el orden de encimado es de arriba hacia abajo.
}

void UnloadBackGround(){
    UnloadTexture(bgFoor);
    UnloadTexture(Tree);
    for(int i = 0; i < mClouds; i++){
        UnloadTexture(cloudT[i]);
    }
    UnloadTexture(Logo);
    UnloadTexture(Mountains);
}

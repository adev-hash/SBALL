#include "raylib.h"
#include "../../class/class.h"
#include <stdlib.h> // Necesario para rand() y srand() si se requiere

typedef struct {
    Vector2 pos; 
    float speed;
    int textureIndex;
} Cloud;

#define M_CLOUDS 15 // Número máximo de nubes
static Texture2D bgFoor;
static Texture2D Tree;
static float scrolling = 0.0f;
static Texture2D cloudT[3];
static Cloud clouds[M_CLOUDS];
static Texture2D Sun;
static float sunR = 0.0f; // giros del sol 
static Texture2D Logo;
static bool showLogo = true;
static Texture2D Mountains;

void iniciarFondo(void) {
    bgFoor = LoadTexture("assets/sprites/background/dirt.png");
    Tree = LoadTexture("assets/sprites/background/tree.png");
    cloudT[0] = LoadTexture("assets/sprites/background/cloud1.png"); 
    cloudT[1] = LoadTexture("assets/sprites/background/cloud2.png");
    cloudT[2] = LoadTexture("assets/sprites/background/cloud3.png");
    Sun = LoadTexture("assets/sprites/background/sun.png");
    Logo = LoadTexture("assets/sprites/background/logo.png");
    Mountains = LoadTexture("assets/sprites/background/mountains.png");
    iniciarAves();

    for(int i = 0; i < M_CLOUDS; i++){
        clouds[i].pos.x = (float)(rand() % 900); // Espacio horizontal
        clouds[i].pos.y = (float)(rand() % 150 + 30); // Altura aleatoria 
        clouds[i].textureIndex = rand() % 3; // Elegir nube aleatoria
        clouds[i].speed = (float)(rand() % 10 + 10); // Velocidad lenta entre 10 y 20.
    }
}

void actualizarFondo(float speed){
    scrolling -= speed * GetFrameTime();
    
    if(scrolling <= -(float)bgFoor.width){
        scrolling = 0.0f;
    }

    for(int i = 0; i < M_CLOUDS; i++){
        clouds[i].pos.x -= clouds[i].speed * GetFrameTime();

        Texture2D cCt = cloudT[clouds[i].textureIndex];
        
        if(clouds[i].pos.x < - (float)cCt.width){
            clouds[i].pos.x = 800.0f + (float)(rand() % 300);
            clouds[i].pos.y = (float)(rand() % 150 + 30);
            clouds[i].textureIndex = rand() % 3;
            clouds[i].speed = (float)(rand() % 10 + 10);
        }
    }

    // Le damos velocidad al sol y lo reiniciamos cada 360 grados
    sunR += 1.0f * GetFrameTime();

    if(sunR >= 360.0f){
        sunR = 0.0f;
    }
}

void ShowLogo(bool visible){
    showLogo = visible;
}

void dibujarFondo(void){
    ejecutarAnimaciones(10.0f);
    float screenWidth = 800.0f;
    int rep = (int)(480.0f / screenWidth) + 10;
    int rep2 = (int)(480.0f / 80.0f) + 10;
    int rep3 = (int)(480.0f / 80.0f) + 10;

    for(int i = 0; i < rep; i++){
        float poX = scrolling + (i * bgFoor.width);
        DrawTextureEx(bgFoor, (Vector2){poX, 480.0f}, 0.0f, 1.0f, WHITE);
    }

    for(int i = 0; i < rep3; i++){
        float poX = scrolling + (i * Mountains.width) - 100.0f; // posición de repetición
        DrawTextureEx(Mountains, (Vector2){poX, 460.0f}, 0.0f, 2.0f, WHITE);
    }

    for(int i = 0; i < rep2; i++){
        float poX = scrolling + (i * Tree.width);
        DrawTextureEx(Tree, (Vector2){poX, 460.0f}, 0.0f, 1.0f, WHITE);
    }

    Vector2 sunOrg = { (float)Sun.width / 40.0f, (float)Sun.height };
    Rectangle SunRise = { 0.0f, 0.0f, (float)Sun.width, (float)Sun.height };
    Rectangle SunRest = { 650.0f, 50.0f, (float)Sun.width, (float)Sun.height };
    DrawTexturePro(Sun, SunRise, SunRest, sunOrg, sunR, WHITE);
    
    for(int i = 0; i < M_CLOUDS; i++){
        Texture2D t = cloudT[clouds[i].textureIndex];
        DrawTextureEx(t, clouds[i].pos, 0.0f, 1.0f, WHITE);
    }

    if(showLogo){
        DrawTextureEx(Logo, (Vector2){320.0f, 100.0f}, 0.0f, 3.0f, WHITE);
    }
}

void descargarFondo(void){
    UnloadTexture(bgFoor);
    UnloadTexture(Tree);
    for(int i = 0; i < 3; i++){
        UnloadTexture(cloudT[i]);
    }
    UnloadTexture(Sun);
    UnloadTexture(Logo);
    UnloadTexture(Mountains);
    descargarAves();
}
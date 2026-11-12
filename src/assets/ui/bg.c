#include "raylib.h"
#include "../../class/class.h"
#include <stdlib.h> 

typedef struct {
    Vector2 pos; 
    float speed;
    int textureIndex;
} Cloud;

typedef struct {
    Vector2 pos;
    float speed;
    int currentF;
    float frTime;
} BackgroundBird;


#define M_CLOUDS 15 
#define M_BG_BIRDS 2
#define BIRD_FRAMES 4 
#define MOUNTAIN_SCALE 5.0f

static Texture2D bgFoor;
static Texture2D Tree;
static Texture2D Mountains;
static Texture2D Sun;
static Texture2D Logo;
static Texture2D cloudT[3];
static Texture2D bgBirdTexture;


static Cloud clouds[M_CLOUDS];
static BackgroundBird bgBirds[M_BG_BIRDS];

static float scrolling = 0.0f;
static float treeScrolling = 0.0f;
static float mountainScrolling = 0.0f;
static float sunR = 0.0f;
static bool showLogo = true;
static float birdFrameWidth = 0.0f;
static float birdFrameHeight = 0.0f;

static Texture2D texturavida;
static Texture2D vidafondo;


static Texture2D alarm;
float timeAlarm = 0.0f;
bool activate = true;



void iniciarFondo(void) {
    bgFoor = LoadTexture("assets/sprites/background/dirt.png");
    Tree = LoadTexture("assets/sprites/background/tree.png");
    cloudT[0] = LoadTexture("assets/sprites/background/cloud1.png"); 
    cloudT[1] = LoadTexture("assets/sprites/background/cloud2.png");
    cloudT[2] = LoadTexture("assets/sprites/background/cloud3.png");
    Sun = LoadTexture("assets/sprites/background/sun.png");
    Logo = LoadTexture("assets/sprites/background/logo.png");
    Mountains = LoadTexture("assets/sprites/background/mountains.png");
    texturavida = LoadTexture("assets/sprites/background/lifebar.png"); 
    vidafondo = LoadTexture("assets/sprites/background/lifebg.png");
    alarm = LoadTexture("assets/sprites/background/alert.png");

    for(int i = 0; i < M_CLOUDS; i++){
        clouds[i].pos.x = (float)(rand() % 900);
        clouds[i].pos.y = (float)(rand() % 150 + 30);
        clouds[i].textureIndex = rand() % 3;
        clouds[i].speed = (float)(rand() % 10 + 10);
    }

    Image birdsImg = LoadImage("assets/sprites/objects/birds.png");
    Rectangle box = GetImageAlphaBorder(birdsImg, 0.0f);
    ImageCrop(&birdsImg, box);
    
    bgBirdTexture = LoadTextureFromImage(birdsImg);
    UnloadImage(birdsImg);
    SetTextureFilter(bgBirdTexture, TEXTURE_FILTER_POINT);

    birdFrameWidth = (float)bgBirdTexture.width / BIRD_FRAMES;
    birdFrameHeight = (float)bgBirdTexture.height;

    for(int i = 0; i < M_BG_BIRDS; i++){
        bgBirds[i].pos.x = (float)(rand() % 900 + 800);
        bgBirds[i].pos.y = (float)(rand() % 200 + 50);
        bgBirds[i].speed = (float)(rand() % 30 + 40);
        bgBirds[i].currentF = 0;
        bgBirds[i].frTime = 0.0f;
    }
}


void activarAlarma(float speed){
    if(speed <= 0) return;

    timeAlarm += GetFrameTime();
    if(timeAlarm >= 0.1f){
        activate = !activate;
        timeAlarm = 0.0f;
    }
    if(activate){
        DrawTexturePro(alarm,(Rectangle){0, 0, (float)alarm.width, (float)alarm.height},(Rectangle){500, 300, 120, 120},(Vector2){0, 0},0,WHITE);
    }
}



void actualizarFondo(float speed){
    float delta_t = GetFrameTime();
    scrolling -= speed * delta_t;
    if(scrolling <= -(float)bgFoor.width){
        scrolling = 0.0f;
    }

    treeScrolling -= speed * delta_t;
    while(treeScrolling <= -(float)Tree.width){
        treeScrolling += (float)Tree.width;
    }

    mountainScrolling -= speed * 0.25f * delta_t;
    float mountainWidth = (float)Mountains.width * MOUNTAIN_SCALE;
    while(mountainScrolling <= -mountainWidth){
        mountainScrolling += mountainWidth;
    }

    for(int i = 0; i < M_CLOUDS; i++){
        clouds[i].pos.x -= clouds[i].speed * delta_t;
        Texture2D cCt = cloudT[clouds[i].textureIndex];
        
        if(clouds[i].pos.x < - (float)cCt.width){
            clouds[i].pos.x = 800.0f + (float)(rand() % 300);
            clouds[i].pos.y = (float)(rand() % 150 + 30);
            clouds[i].textureIndex = rand() % 3;
            clouds[i].speed = (float)(rand() % 10 + 10);
        }
    }

    for(int i = 0; i < M_BG_BIRDS; i++){
        bgBirds[i].pos.x -= (bgBirds[i].speed + speed * 0.5f) * delta_t;
        bgBirds[i].frTime += delta_t;

        if(bgBirds[i].frTime >= 0.15f){
            bgBirds[i].frTime = 0.0f;
            bgBirds[i].currentF = (bgBirds[i].currentF + 1) % BIRD_FRAMES;
        }

        if(bgBirds[i].pos.x < -birdFrameWidth){
            bgBirds[i].pos.x = 850.0f + (float)(rand() % 300);
            bgBirds[i].pos.y = (float)(rand() % 200 + 50);
        }
    }

    sunR += 1.0f * delta_t;
    if(sunR >= 360.0f){
        sunR = 0.0f;
    }
}

void ShowLogo(bool visible){
    showLogo = visible;
}


void dibujarFondo(void){
    float screenWidth = 800.0f;
    int rep = (int)(480.0f / screenWidth) + 10;
    int rep2 = (int)(480.0f / 80.0f) + 10;

    float mountainWidth = (float)Mountains.width * MOUNTAIN_SCALE;
    for(float poX = mountainScrolling - 100.0f; poX < screenWidth; poX += mountainWidth){
        DrawTextureEx(Mountains, (Vector2){poX, 274.0f}, 0.0f, MOUNTAIN_SCALE, WHITE);
    }
    for(int i = 0; i < rep; i++){
        float poX = scrolling + (i * bgFoor.width);
        DrawTextureEx(bgFoor, (Vector2){poX, 480.0f}, 0.0f, 1.0f, WHITE);
    }

    for(int i = 0; i < rep2; i++){
        float poX = treeScrolling + (i * Tree.width);
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

    for(int i = 0; i < M_BG_BIRDS; i++){
        Rectangle sourceRec = { (float)(bgBirds[i].currentF * birdFrameWidth), 0.0f, birdFrameWidth, birdFrameHeight };
        Rectangle destRec = { bgBirds[i].pos.x, bgBirds[i].pos.y, birdFrameWidth, birdFrameHeight };
        DrawTexturePro(bgBirdTexture, sourceRec, destRec, (Vector2){0.0f, 0.0f}, 0.0f, WHITE);
    }

    if(showLogo){
        DrawTextureEx(Logo, (Vector2){320.0f, 100.0f}, 0.0f, 3.0f, WHITE);
    }
}

void mostrarVida(int vida){
    DrawTexturePro(vidafondo,
    (Rectangle){0, 0, (float)vidafondo.width, (float)vidafondo.height},
    (Rectangle){460, -10, 300, 100},
    (Vector2){0, 0},0,WHITE);
    Rectangle rectangulo = {500,25,(float)vida*2.0f,25};
    DrawRectangleRec(rectangulo,GREEN);
    DrawTexturePro(texturavida,
    (Rectangle){0, 0, (float)texturavida.width, (float)texturavida.height},
    (Rectangle){460, -10, 300, 100},
    (Vector2){0, 0},0,WHITE);
    
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
    UnloadTexture(bgBirdTexture);
    UnloadTexture(texturavida);
    UnloadTexture(alarm);
    UnloadTexture(vidafondo);
}

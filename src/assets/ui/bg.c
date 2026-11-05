#include "raylib.h"
#include "../../class/class.h"
#include <stdlib.h> 

// ESTRUCTURAS DEL FONDO ^^ ---------------------------------------------

// Nubes decorativas
typedef struct {
    Vector2 pos; 
    float speed;
    int textureIndex;
} Cloud;

// Pajaro del fondoo
typedef struct {
    Vector2 pos;
    float speed;
    int currentF;
    float frTime;
} BackgroundBird;

// CONSTANTES ^^ ---------------------------------------------------------

#define M_CLOUDS 15 // Número máximo de nubes
#define M_BG_BIRDS 2 // Número máximo de pájaros
#define BIRD_FRAMES 4 // no. total de fotogramas del pajaro

// VARIABLES ESTÁTICAS DE RECURSOS ^^ -------------------------------------------------

// Texturas
static Texture2D bgFoor;
static Texture2D Tree;
static Texture2D Mountains;
static Texture2D Sun;
static Texture2D Logo;
static Texture2D cloudT[3];
static Texture2D bgBirdTexture;


// listas de instancias de objetos animados
static Cloud clouds[M_CLOUDS];
static BackgroundBird bgBirds[M_BG_BIRDS];

// dezplazamiento del fondo
static float scrolling = 0.0f;
static float sunR = 0.0f; // giros del sol 
static bool showLogo = true;
static float birdFrameWidth = 0.0f;
static float birdFrameHeight = 0.0f;

// INICIALIZACION ^^ -------------------------------------------------------------

void iniciarFondo(void) {
    // carga texturas estaticas
    bgFoor = LoadTexture("assets/sprites/background/dirt.png");
    Tree = LoadTexture("assets/sprites/background/tree.png");
    cloudT[0] = LoadTexture("assets/sprites/background/cloud1.png"); 
    cloudT[1] = LoadTexture("assets/sprites/background/cloud2.png");
    cloudT[2] = LoadTexture("assets/sprites/background/cloud3.png");
    Sun = LoadTexture("assets/sprites/background/sun.png");
    Logo = LoadTexture("assets/sprites/background/logo.png");
    Mountains = LoadTexture("assets/sprites/background/mountains.png");

    //inicializa nubes
    for(int i = 0; i < M_CLOUDS; i++){
        clouds[i].pos.x = (float)(rand() % 900); // Espacio horizontal
        clouds[i].pos.y = (float)(rand() % 150 + 30); // Altura aleatoria 
        clouds[i].textureIndex = rand() % 3; // Elegir nube aleatoria
        clouds[i].speed = (float)(rand() % 10 + 10); // Velocidad lenta entre 10 y 20.
    }

    //carga sprites de pájaros del fondo
    Image birdsImg = LoadImage("assets/sprites/objects/birds.png");
    Rectangle box = GetImageAlphaBorder(birdsImg, 0.0f);
    ImageCrop(&birdsImg, box);
    
    bgBirdTexture = LoadTextureFromImage(birdsImg);
    UnloadImage(birdsImg);
    SetTextureFilter(bgBirdTexture, TEXTURE_FILTER_POINT);

    birdFrameWidth = (float)bgBirdTexture.width / BIRD_FRAMES;
    birdFrameHeight = (float)bgBirdTexture.height;

    //inicializa pájaros del fondo
    for(int i = 0; i < M_BG_BIRDS; i++){
        bgBirds[i].pos.x = (float)(rand() % 900 + 800);
        bgBirds[i].pos.y = (float)(rand() % 200 + 50);
        bgBirds[i].speed = (float)(rand() % 30 + 40);
        bgBirds[i].currentF = 0;
        bgBirds[i].frTime = 0.0f;
    }
}

// FUNCIONES DE ACTUALIZACION ^^ ---------------------------------------------

void actualizarFondo(float speed){
    // guardar frame time para ahorrar llamadas a GetFrameTime() y mejorar el rendimiento
    float delta_t = GetFrameTime();

    // desplzamiento del suelo
    scrolling -= speed * delta_t;
    if(scrolling <= -(float)bgFoor.width){
        scrolling = 0.0f;
    }

    // dezplazamiento de nubes
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

    // desplazamiento y animacion de pájaros del fondo
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

    // Le damos velocidad al sol y lo reiniciamos cada 360 grados
    sunR += 1.0f * delta_t;
    if(sunR >= 360.0f){
        sunR = 0.0f;
    }
}

void ShowLogo(bool visible){
    showLogo = visible;
}

// FUNCIONES DRAW ^^ -------------------------------------------------------------

void dibujarFondo(void){
    float screenWidth = 800.0f;
    int rep = (int)(480.0f / screenWidth) + 10;
    int rep2 = (int)(480.0f / 80.0f) + 10;
    int rep3 = (int)(480.0f / 80.0f) + 10;

    // dibujar suelo
    for(int i = 0; i < rep; i++){
        float poX = scrolling + (i * bgFoor.width);
        DrawTextureEx(bgFoor, (Vector2){poX, 480.0f}, 0.0f, 1.0f, WHITE);
    }

    // dibujar montañas
    for(int i = 0; i < rep3; i++){
        float poX = scrolling + (i * Mountains.width) - 100.0f; // posición de repetición
        DrawTextureEx(Mountains, (Vector2){poX, 460.0f}, 0.0f, 2.0f, WHITE);
    }

    // dibujar arboles
    for(int i = 0; i < rep2; i++){
        float poX = scrolling + (i * Tree.width);
        DrawTextureEx(Tree, (Vector2){poX, 460.0f}, 0.0f, 1.0f, WHITE);
    }

    // dibujar solecito!!
    Vector2 sunOrg = { (float)Sun.width / 40.0f, (float)Sun.height };
    Rectangle SunRise = { 0.0f, 0.0f, (float)Sun.width, (float)Sun.height };
    Rectangle SunRest = { 650.0f, 50.0f, (float)Sun.width, (float)Sun.height };
    DrawTexturePro(Sun, SunRise, SunRest, sunOrg, sunR, WHITE);
    
    // dibujar nubes
    for(int i = 0; i < M_CLOUDS; i++){
        Texture2D t = cloudT[clouds[i].textureIndex];
        DrawTextureEx(t, clouds[i].pos, 0.0f, 1.0f, WHITE);
    }

    // dibujar pájaros del fondo
    for(int i = 0; i < M_BG_BIRDS; i++){
        Rectangle sourceRec = { (float)(bgBirds[i].currentF * birdFrameWidth), 0.0f, birdFrameWidth, birdFrameHeight };
        Rectangle destRec = { bgBirds[i].pos.x, bgBirds[i].pos.y, birdFrameWidth, birdFrameHeight };
        DrawTexturePro(bgBirdTexture, sourceRec, destRec, (Vector2){0.0f, 0.0f}, 0.0f, WHITE);
    }

    // dibujar logo
    if(showLogo){
        DrawTextureEx(Logo, (Vector2){320.0f, 100.0f}, 0.0f, 3.0f, WHITE);
    }
}
void mostrarVida(int vida){
    Rectangle rectangulo = {300,25,(float)vida*2.0f,25};
    DrawRectangleRec(rectangulo,GREEN);
    DrawRectangleLinesEx(rectangulo,3,BLACK);
}

// LIBERACION DE RECURSOS ^^ -------------------------------------------------------------
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
}
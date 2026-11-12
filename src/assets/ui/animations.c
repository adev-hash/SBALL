#include "raylib.h"
#include "../../class/class.h"
#include <stdlib.h>
#include <math.h>
 
typedef struct {
    Vector2 posicion;
    float velocidad;
    int currentF;
    float fPtime;
    int vida;
    Rectangle hitbox;
    int skinID ; 
} Avion;

typedef struct {
    Vector2 pos;
    float speed;
    int currentF; 
    int currentFy;
    float frTime;
    bool activo; 
    bool colisianado; 
    Rectangle hitbox;
} Pajarraco;

typedef struct {
    Vector2 pos;
    float speed;
    bool activo;
    Rectangle hitbox;
} Moneda;

static Avion av;
static Texture2D planeTexture;
#define PLANE_FRAMES 5
#define GRAVEDAD_AVION 500.0f
#define IMPULSO_AVION 900.0f
#define VELOCIDAD_MAX_CAIDA 300.0f
#define VELOCIDAD_MAX_ASCENSO 250.0f
static float planeFWith = 0.0f;
static float planeFHeight = 0.0f;
static double tiempo_inicio_juego = 0.0;
static double tiempo_final_juego = 0.0;
static bool temporizador_activo = false;

#define MAX_PAJARRACOS 30 
#define PAJARRACO_FRAMES 8 
#define PAJARRACO_COLUMNAS 6
#define PAJARRACO_FILAS 2
#define PAJARRACOS_INICIALES 10
#define PAJARRACO_INTERVALO_ACTIVACION 10.0
#define PAJARRACO_INCREMENTO_VELOCIDAD 0.07f
static Pajarraco pajarracos[MAX_PAJARRACOS];
static Texture2D pajarracoTexture;
static float pajarracoFWidth = 0.0f;
static float pajarracoFHeight = 0.0f;
static int pajarracosActivos = PAJARRACOS_INICIALES;

static Texture2D planeTextureSkin0; 
static Texture2D planeTextureSkin1; 
static Texture2D planeTextureSkin2;
static Texture2D planeTextureSkin3;

static Texture2D textureCoin;

#define MAX_MONEDAS 10
#define INTERVALO 2.5f
static Moneda coins[MAX_MONEDAS];
static float monedaTimer = 0.0f;
static float monedasPartida = 0.0f;
static float coinW = 0.0f, coinH = 0.0f;


void iniciarAvion(void) {
    Image planeImage0 = LoadImage("assets/sprites/objects/planesprites.png");
    Rectangle planeBox = GetImageAlphaBorder(planeImage0, 0.0f); 
    ImageCrop(&planeImage0, planeBox); 
    planeTextureSkin0 = LoadTextureFromImage(planeImage0);
    UnloadImage(planeImage0);  

    Image planeImage1 = LoadImage("assets/sprites/objects/jet.png");
    Rectangle planeBox1 = GetImageAlphaBorder(planeImage1, 0.0f); 
    ImageCrop(&planeImage1, planeBox1);
    planeTextureSkin1 = LoadTextureFromImage(planeImage1);
    UnloadImage(planeImage1);

    Image planeImage2 = LoadImage("assets/sprites/objects/ovni.png");
    Rectangle planeBox2 = GetImageAlphaBorder(planeImage2, 0.0f);
    ImageCrop(&planeImage2, planeBox2);
    planeTextureSkin2 = LoadTextureFromImage(planeImage2);
    UnloadImage(planeImage2);

    Image planeImage3 = LoadImage("assets/sprites/objects/paperplane.png");
    Rectangle planeBox3 = GetImageAlphaBorder(planeImage3, 0.0f); 
    ImageCrop(&planeImage3, planeBox3);
    planeTextureSkin3 = LoadTextureFromImage(planeImage3);
    UnloadImage(planeImage3);

    planeTexture = planeTextureSkin0 ; 
    SetTextureFilter(planeTexture, TEXTURE_FILTER_POINT);

    planeFWith = (float)planeTexture.width / PLANE_FRAMES;
    planeFHeight = (float)planeTexture.height;

    av.posicion = (Vector2){ 50.0f, 200.0f };
    av.velocidad = 5.0f;
    av.currentF = 0;
    av.fPtime = 0.0f;
    av.vida = 100; 
    av.skinID = 0;

    av.hitbox = (Rectangle){ av.posicion.x + 6.0f, av.posicion.y + 6.0f, planeFWith - 12.0f, planeFHeight - 12.0f };
}

void actualizarSkinAvion(int nuevoSkinID) {
    av.skinID = nuevoSkinID;
    if (av.skinID == 1) planeTexture = planeTextureSkin1;
    else if (av.skinID == 2) planeTexture = planeTextureSkin2;
    else if (av.skinID == 3) planeTexture = planeTextureSkin3;
    else planeTexture = planeTextureSkin0;

    planeFWith = (float)planeTexture.width / PLANE_FRAMES;
    planeFHeight = (float)planeTexture.height;
}

void actualizarAvion(void) {
    float delta_t = GetFrameTime();
    av.fPtime += delta_t;

    if (av.fPtime >= 0.05f) {
        av.fPtime = 0.0f;
        av.currentF = (av.currentF + 1) % PLANE_FRAMES;
    }
    
    float aceleracionY = GRAVEDAD_AVION;
    if (IsKeyDown(KEY_SPACE)) {
        aceleracionY -= IMPULSO_AVION;
    }

    if (IsKeyDown(KEY_LEFT)) av.posicion.x -= 50.0f * delta_t;
    if (IsKeyDown(KEY_RIGHT)) av.posicion.x += 50.0f * delta_t;
    if (av.posicion.x < 0.0f) av.posicion.x = 0.0f;
    if (av.posicion.x > GetScreenWidth() - planeFWith) {
        av.posicion.x = GetScreenWidth() - planeFWith;
    }

    av.velocidad += aceleracionY * delta_t;
    if (av.velocidad < -VELOCIDAD_MAX_ASCENSO) {
        av.velocidad = -VELOCIDAD_MAX_ASCENSO;
    } else if (av.velocidad > VELOCIDAD_MAX_CAIDA) {
        av.velocidad = VELOCIDAD_MAX_CAIDA;
    }
    av.posicion.y += av.velocidad * delta_t;

    if (av.posicion.y < 50.0f) {
        av.posicion.y = 50.0f;
        if (av.velocidad < 0.0f) av.velocidad = 0.0f;
    } else if (av.posicion.y > 450.0f) {
        av.vida -= 0.5; 
        activarAlarma(1);
        if (av.posicion.y > 550.0f) av.vida = 0;
        if (av.vida <= 0) {
            av.vida = 0;
            gameOver = 1;
            temporizador_activo = false;
            tiempo_final_juego = GetTime() - tiempo_inicio_juego;
        }
    }
    
    av.hitbox.x = av.posicion.x + 6.0f;
    av.hitbox.y = av.posicion.y + 6.0f;
}

void mostrarAvion(void) {
    Rectangle srPlane = { (float)(av.currentF * planeFWith), 0.0f, planeFWith, planeFHeight };
    Rectangle drPlane = { av.posicion.x, av.posicion.y, planeFWith, planeFHeight };
    DrawTexturePro(planeTexture, srPlane, drPlane, (Vector2){0, 0}, 0.0f, WHITE);
    mostrarVida(av.vida);
}

void descargarAvion(void) {
    UnloadTexture(planeTexture);
}

void iniciarPajarracos(void) {
    Image pajarracoImg = LoadImage("assets/sprites/objects/enemyBirds.png"); 
    Rectangle box = GetImageAlphaBorder(pajarracoImg, 0.0f);
    ImageCrop(&pajarracoImg, box);                         

    pajarracoTexture = LoadTextureFromImage(pajarracoImg);
    UnloadImage(pajarracoImg);
    SetTextureFilter(pajarracoTexture, TEXTURE_FILTER_POINT);

    pajarracoFWidth = (float)pajarracoTexture.width / PAJARRACO_COLUMNAS;
    pajarracoFHeight = (float)pajarracoTexture.height / PAJARRACO_FILAS;

    for(int i = 0; i < MAX_PAJARRACOS; i++){
        pajarracos[i].pos.x = (float)(rand() % 900 + 800);
        pajarracos[i].pos.y = (float)(rand() % 400 + 50);
        pajarracos[i].speed = (float)(rand() % 40 + 50); 
        pajarracos[i].currentF = 0;
        pajarracos[i].currentFy = 0;
        pajarracos[i].frTime = 0.0f;
        pajarracos[i].activo = (i < pajarracosActivos);
        pajarracos[i].colisianado = false; 
        
        float diffx = pajarracoFWidth * 0.15f;
        float diffy = pajarracoFHeight * 0.15f;
        pajarracos[i].hitbox = (Rectangle){ pajarracos[i].pos.x + diffx, pajarracos[i].pos.y + diffy, pajarracoFWidth - 2 * diffx, pajarracoFHeight - 2 * diffy };
    }
}

void actualizarPajarracos(float speed) {
    float delta_t = GetFrameTime();
    double tiempo_juego = temporizador_activo ? GetTime() - tiempo_inicio_juego : 0.0;
    int etapa = (int)(tiempo_juego / PAJARRACO_INTERVALO_ACTIVACION);
    int pajarracosObjetivo = PAJARRACOS_INICIALES + etapa;
    if (pajarracosObjetivo > MAX_PAJARRACOS) {
        pajarracosObjetivo = MAX_PAJARRACOS;
    }
    float multiplicadorVelocidad = 1.0f + etapa * PAJARRACO_INCREMENTO_VELOCIDAD;

    for (int i = pajarracosActivos; i < pajarracosObjetivo; i++) {
        pajarracos[i].pos.x = 850.0f + (float)(rand() % 300);
        pajarracos[i].pos.y = (float)(rand() % 400 + 50);
        pajarracos[i].speed = (float)(rand() % 40 + 50);
        pajarracos[i].currentF = 0;
        pajarracos[i].currentFy = 0;
        pajarracos[i].frTime = 0.0f;
        pajarracos[i].activo = true;
        pajarracos[i].colisianado = false;
        float diffx = pajarracoFWidth * 0.15f;
        float diffy = pajarracoFHeight * 0.15f;
        pajarracos[i].hitbox = (Rectangle){
            pajarracos[i].pos.x + diffx,
            pajarracos[i].pos.y + diffy,
            pajarracoFWidth - 2 * diffx,
            pajarracoFHeight - 2 * diffy
        };
    }
    pajarracosActivos = pajarracosObjetivo;

    for(int i = 0; i < MAX_PAJARRACOS; i++){
        if(pajarracos[i].activo){
            pajarracos[i].pos.x -= (pajarracos[i].speed + speed) * multiplicadorVelocidad * delta_t;
            pajarracos[i].frTime += delta_t;

            if(pajarracos[i].frTime >= 0.10f){
                pajarracos[i].frTime = 0.0f;
                int frame = pajarracos[i].currentFy * PAJARRACO_COLUMNAS + pajarracos[i].currentF;
                frame = (frame + 1) % PAJARRACO_FRAMES;
                pajarracos[i].currentFy = frame / PAJARRACO_COLUMNAS;
                pajarracos[i].currentF = frame % PAJARRACO_COLUMNAS;
            }

            if(pajarracos[i].pos.x < -pajarracoFWidth){
                pajarracos[i].pos.x = 850.0f + (float)(rand() % 300);


                pajarracos[i].pos.y = (float)(rand() % 400 + 50);
                pajarracos[i].speed = (float)(rand() % 40 + 50);
                pajarracos[i].colisianado = false;
            }
            float diffx = pajarracoFWidth * 0.15f; 
            float diffy = pajarracoFHeight * 0.15f; 
            pajarracos[i].hitbox.x = pajarracos[i].pos.x + diffx;
            pajarracos[i].hitbox.y = pajarracos[i].pos.y + diffy;
        }
    }
}

void mostrarPajarracos(void) {
    for(int i = 0; i < MAX_PAJARRACOS; i++){
        if(pajarracos[i].activo){
            Rectangle sourceRec = { 
                pajarracos[i].currentF * pajarracoFWidth, 
                pajarracos[i].currentFy* pajarracoFHeight, 
                pajarracoFWidth, 
                pajarracoFHeight};

            Rectangle destRec = { pajarracos[i].pos.x, pajarracos[i].pos.y, pajarracoFWidth, pajarracoFHeight};
            Vector2 origin = { 0.0f, 0.0f };
            DrawTexturePro(pajarracoTexture, sourceRec, destRec, origin, 0.0f, WHITE);
        }
    }
}

bool verificarColisionPajarraco() {
    for(int i = 0; i < MAX_PAJARRACOS; i++){
        if(pajarracos[i].activo && !pajarracos[i].colisianado && CheckCollisionRecs(av.hitbox, pajarracos[i].hitbox)) {
            pajarracos[i].colisianado = true;
            av.vida -= 10; 
            if (av.vida <= 0) {
                av.vida = 0; 
                gameOver = 1;
                temporizador_activo = false;
                tiempo_final_juego = GetTime() - tiempo_inicio_juego;
            }
            return true; 
        }
    }
    return false;
}

void descargarPajarracos(void) {
    UnloadTexture(pajarracoTexture);
}

void iniciarMonedas(void){
    textureCoin = LoadTexture("assets/sprites/objects/coins.png");
    SetTextureFilter(textureCoin, TEXTURE_FILTER_POINT);
    coinW = (float)textureCoin.width;
    coinH = (float)textureCoin.height;
    for(int i = 0; i < MAX_MONEDAS; i++) coins[i].activo = false;
    monedaTimer = 0.0f;
    monedasPartida = 0.0f;
}

void actualizarMonedas(float speed){
    float dt = GetFrameTime();
    monedaTimer+= dt;

    if(monedaTimer >= INTERVALO){
        monedaTimer = 0.0f;
        for(int i = 0; i < MAX_MONEDAS; i++){
            if(!coins[i].activo){
                coins[i].pos = (Vector2){ 850.0f, (float)(rand() % 380 + 50) };
                coins[i].speed = (float)(rand() % 30 + 40);
                coins[i].activo = true;
                coins[i].hitbox = (Rectangle){ coins[i].pos.x, coins[i].pos.y, coinW, coinH };
                break;
            }
        }
    }

    for(int i = 0; i < MAX_MONEDAS; i++){
        if(!coins[i].activo ) continue;

         coins[i].pos.x -= (coins[i].speed + speed) * dt;
        coins[i].hitbox.x = coins[i].pos.x;
        coins[i].hitbox.y = coins[i].pos.y;

        if (CheckCollisionRecs(av.hitbox, coins[i].hitbox)) {
            coins[i].activo = false;
            monedasPartida+=5;
            monedasGlobales+=5;
        } else if (coins[i].pos.x < -coinW) {
            coins[i].activo = false;
        }
    }
    
}

void mostrarMonedas(void){
    for(int i = 0; i < MAX_MONEDAS; i++){
            if (coins[i].activo) DrawTextureV(textureCoin, coins[i].pos, WHITE);
    }
    DrawText(TextFormat("ZENITS: %.0f", monedasPartida), 18, 55, 20, YELLOW);
}

void descargarMonedas(void) {
     UnloadTexture(textureCoin); 
}

void reiniciarMonedas(void){
    for(int i = 0; i < MAX_MONEDAS; i++) coins[i].activo = false;
    monedasPartida = 0;
    monedaTimer = 0.0f;
}


void iniciarTemporizador(void) {
    tiempo_inicio_juego = GetTime();
    tiempo_final_juego = 0.0;
    temporizador_activo = true;
}

void mostrarTemporizador(void) {
    double tiempo_juego = temporizador_activo ? GetTime() - tiempo_inicio_juego : tiempo_final_juego;
    const char *texto = TextFormat(
        "TIME:   %02d : %02d : %02d",
        (int)(tiempo_juego / 60),
        (int)tiempo_juego % 60,
        (int)((tiempo_juego - (int)tiempo_juego) * 100)
    );
    DrawText(texto, 18, 28, 20, WHITE);
}

void reiniciarPartida(void) {
    pajarracosActivos = PAJARRACOS_INICIALES;

    av.posicion = (Vector2){ 50.0f, 200.0f };
    av.velocidad = 5.0f;
    av.currentF = 0;
    av.fPtime = 0.0f;
    av.vida = 100;
    av.hitbox = (Rectangle){ av.posicion.x + 6.0f, av.posicion.y + 6.0f, planeFWith - 12.0f, planeFHeight - 12.0f };

    for (int i = 0; i < MAX_PAJARRACOS; i++) {
        pajarracos[i].pos.x = (float)(rand() % 900 + 800);
        pajarracos[i].pos.y = (float)(rand() % 400 + 50);
        pajarracos[i].speed = (float)(rand() % 40 + 50);
        pajarracos[i].currentF = 0;
        pajarracos[i].currentFy = 0;
        pajarracos[i].frTime = 0.0f;
        pajarracos[i].activo = (i < pajarracosActivos);
        pajarracos[i].colisianado = false;

        float diffx = pajarracoFWidth * 0.15f;
        float diffy = pajarracoFHeight * 0.15f;
        pajarracos[i].hitbox = (Rectangle){ pajarracos[i].pos.x + diffx, pajarracos[i].pos.y + diffy, pajarracoFWidth - 2 * diffx, pajarracoFHeight - 2 * diffy };
    }

    gameOver = 0;
    iniciarTemporizador();
}

double obtenerTiempoFinal(void){
    return tiempo_final_juego;
}

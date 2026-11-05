#include "raylib.h"
#include "../../class/class.h"
#include <stdlib.h>
#include <math.h>

// ESTRUCTURAS DE OBJETOS ANIMADOS ^^ ------------------------------
 
// Avion del jugador
typedef struct {
    Vector2 posicion;
    float velocidad;
    int currentF;
    float fPtime;
    int vida;
    Rectangle hitbox;
} Avion;

// Pajarraco enemigo (nombre provisional xd)
typedef struct {
    Vector2 pos;
    float speed;
    int currentF; 
    int currentFy;
    float frTime;
    bool activo; // para poder agregar y quitar pájaros del juego sin tener que eliminar el objeto de la lista
    bool colisianado; // para saber si el pajarraco ha colisionado con el avión
    Rectangle hitbox;
} Pajarraco;

//Moneda
typedef struct {
    Vector2 pos;
    float speed;
    bool activo; // para poder agregar y quitar monedas al recolectar o salir de pantalla
    Rectangle hitbox;
} Moneda;

// CONSTANTES ^^ ---------------------------------------------------------

// del avion...
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

// de los pajarracos enemigos...
#define MAX_PAJARRACOS 15 // Número máximo de pájaros
#define PAJARRACO_FRAMES 8 // no. total de fotogramas del pajarraco
#define PAJARRACO_COLUMNAS 6
#define PAJARRACO_FILAS 2
static Pajarraco pajarracos[MAX_PAJARRACOS];
static Texture2D pajarracoTexture;
static float pajarracoFWidth = 0.0f;
static float pajarracoFHeight = 0.0f;
static int pajarracosActivos = 15; // Contador de pájaros activos en el juego

// de las monedas... (por agregar xd)

// FUNCIONES AVION ------------------------------

void iniciarAvion(void) {
    //Inicializa las propiedades, textura y dimension del avión del jugador
    Image planeImage = LoadImage("assets/sprites/objects/planesprites.png");
    Rectangle planeBox = GetImageAlphaBorder(planeImage, 0.0f); // Area con pixeles visibles
    ImageCrop(&planeImage, planeBox);   
    
    planeTexture = LoadTextureFromImage(planeImage);
    UnloadImage(planeImage);
    SetTextureFilter(planeTexture, TEXTURE_FILTER_POINT);

    planeFWith = (float)planeTexture.width / PLANE_FRAMES;
    planeFHeight = (float)planeTexture.height;
    
    // Valores iniciales del avión
    av.posicion = (Vector2){ 50.0f, 200.0f };
    av.velocidad = 5.0f;
    av.currentF = 0;
    av.fPtime = 0.0f;
    av.vida = 100; // Vida inicial del jugador

    // Inicializa la hitbox del avión (mueve el eje 6 unidades y reduce el tamaño 12 unidades para que la colisión sea más justa)
    av.hitbox = (Rectangle){ av.posicion.x + 6.0f, av.posicion.y + 6.0f, planeFWith - 12.0f, planeFHeight - 12.0f };
}

void actualizarAvion(void) {
    // se separa la actualización de la animacion para no solapar los frames y se alcance a calcular la colision !!
    float delta_t = GetFrameTime();
    av.fPtime += delta_t;

    if (av.fPtime >= 0.05f) {
        av.fPtime = 0.0f;
        av.currentF = (av.currentF + 1) % PLANE_FRAMES;
    }
    
    float aceleracionY = GRAVEDAD_AVION;
    if (IsKeyDown(KEY_W)) {
        aceleracionY -= IMPULSO_AVION;
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
    } else if (av.posicion.y > 400.0f) {
        av.posicion.y = 400.0f;
        if (av.velocidad > 0.0f) av.velocidad = 0.0f;
    }
    
    // actualización de Hitbox del Avión
    av.hitbox.x = av.posicion.x + 6.0f;
    av.hitbox.y = av.posicion.y + 6.0f;
}

void mostrarAvion(void) {
    // Actualiza la animación del avión y dibuja el avión en la pantalla
    Rectangle srPlane = { (float)(av.currentF * planeFWith), 0.0f, planeFWith, planeFHeight };
    Rectangle drPlane = { av.posicion.x, av.posicion.y, planeFWith, planeFHeight };
    DrawTexturePro(planeTexture, srPlane, drPlane, (Vector2){0, 0}, 0.0f, WHITE);
    //DrawRectangleLinesEx(av.hitbox, 3, RED); // Dibuja la hitbox del avión en rojo para depuración
    mostrarVida(av.vida);
}

void descargarAvion(void) {
    // Libera la memoria de la textura del avión
    UnloadTexture(planeTexture);
}

void reiniciarPartida(void) {
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

// FUNCIONES PAJARRACOS ------------------------------

void iniciarPajarracos(void) {
    // Inicializa las propiedades, textura y posiciones aleatorias de los pajarracos enemigos
    Image pajarracoImg = LoadImage("assets/sprites/objects/enemyBirds.png"); //mientras usa la textura de pájaros del fondo xd
    Rectangle box = GetImageAlphaBorder(pajarracoImg, 0.0f); // área con píxeles visibles
    ImageCrop(&pajarracoImg, box);                           // elimina el margen vacío

    pajarracoTexture = LoadTextureFromImage(pajarracoImg);
    UnloadImage(pajarracoImg);
    SetTextureFilter(pajarracoTexture, TEXTURE_FILTER_POINT);

    pajarracoFWidth = (float)pajarracoTexture.width / PAJARRACO_COLUMNAS;
    pajarracoFHeight = (float)pajarracoTexture.height / PAJARRACO_FILAS;

    for(int i = 0; i < MAX_PAJARRACOS; i++){
        pajarracos[i].pos.x = (float)(rand() % 900 + 800);
        pajarracos[i].pos.y = (float)(rand() % 400 + 50);
        pajarracos[i].speed = (float)(rand() % 40 + 50); //más rapidos que el fondo
        pajarracos[i].currentF = 0;
        pajarracos[i].currentFy = 0;
        pajarracos[i].frTime = 0.0f;
        pajarracos[i].activo = (i < pajarracosActivos); // Activa solo los primeros pájaros
        pajarracos[i].colisianado = false; // Inicialmente no han colisionado
        
        // calcula la hitbox del pajarraco
        float diffx = pajarracoFWidth * 0.15f; // 15% de diferencia en el eje x
        float diffy = pajarracoFHeight * 0.15f; // 15% de diferencia en el eje y
        pajarracos[i].hitbox = (Rectangle){ pajarracos[i].pos.x + diffx, pajarracos[i].pos.y + diffy, pajarracoFWidth - 2 * diffx, pajarracoFHeight - 2 * diffy };
    }
}

void actualizarPajarracos(float speed) {
    // Actualiza la posición y animación de los pajarracos enemigos
    float delta_t = GetFrameTime();

    for(int i = 0; i < MAX_PAJARRACOS; i++){
        if(pajarracos[i].activo){

            //avanza a la izquierda
            pajarracos[i].pos.x -= (pajarracos[i].speed + speed * 1.0f) * delta_t;
            pajarracos[i].frTime += delta_t;

            //animacion del sprite del pajarraco
            if(pajarracos[i].frTime >= 0.10f){
                pajarracos[i].frTime = 0.0f;
                int frame = pajarracos[i].currentFy * PAJARRACO_COLUMNAS + pajarracos[i].currentF;
                frame = (frame + 1) % PAJARRACO_FRAMES;
                pajarracos[i].currentFy = frame / PAJARRACO_COLUMNAS;
                pajarracos[i].currentF = frame % PAJARRACO_COLUMNAS;
            }

            // si el pajarraco sale de la pantalla, lo reinicia en una posición aleatoria a la derecha
            if(pajarracos[i].pos.x < -pajarracoFWidth){
                pajarracos[i].pos.x = 850.0f + (float)(rand() % 300);


                pajarracos[i].pos.y = (float)(rand() % 400 + 50);
                pajarracos[i].speed = (float)(rand() % 40 + 50); // asigna nueva velocidad
                pajarracos[i].colisianado = false; // reinicia el estado de colisión
            }

            // Actualiza la hitbox del pajarraco
            float diffx = pajarracoFWidth * 0.15f; // 15% de diferencia en el eje x
            float diffy = pajarracoFHeight * 0.15f; // 15% de diferencia en el eje y
            pajarracos[i].hitbox.x = pajarracos[i].pos.x + diffx;
            pajarracos[i].hitbox.y = pajarracos[i].pos.y + diffy;
        }
    }
}

void mostrarPajarracos(void) {
    // Dibuja los pajarracos enemigos en la pantalla
    for(int i = 0; i < MAX_PAJARRACOS; i++){
        if(pajarracos[i].activo){
            //recorte del sprite
            Rectangle sourceRec = { 
                pajarracos[i].currentF * pajarracoFWidth, 
                pajarracos[i].currentFy* pajarracoFHeight, 
                pajarracoFWidth, 
                pajarracoFHeight};

            // destino del sprite en pantalla
            Rectangle destRec = { pajarracos[i].pos.x, pajarracos[i].pos.y, pajarracoFWidth, pajarracoFHeight};
            Vector2 origin = { 0.0f, 0.0f };
            DrawTexturePro(pajarracoTexture, sourceRec, destRec, origin, 0.0f, WHITE);

            /*Dibujar la hitbox del pajarraco
            if (pajarracos[i].colisianado) {
                DrawRectangleLinesEx(pajarracos[i].hitbox, 3, BLACK); // Hitbox en rojo si ha colisionado
            } else {
                DrawRectangleLinesEx(pajarracos[i].hitbox, 3, GREEN); // Hitbox en verde si no ha colisionado
            }*/
        }
    }
}

bool verificarColisionPajarraco() {
    for(int i = 0; i < MAX_PAJARRACOS; i++){
        if(pajarracos[i].activo && !pajarracos[i].colisianado && CheckCollisionRecs(av.hitbox, pajarracos[i].hitbox)) {
            pajarracos[i].colisianado = true; // Marca el pajarraco como colisionado
            av.vida -= 10; // Reduce la vida del jugador en 10 puntos
            if (av.vida <= 0) {
                av.vida = 0; // Asegura que la vida no sea negativa
                gameOver = 1;
                temporizador_activo = false;
                tiempo_final_juego = GetTime() - tiempo_inicio_juego;
            }
            return true; // Retorna true si hay colisión
        }
    }
    return false; // Retorna false si no hay colisión
}

void descargarPajarracos(void) {
    // Libera la memoria de la textura de los pajarracos enemigos
    UnloadTexture(pajarracoTexture);
}

// FUNCIONES MONEDAS ------------------------------


// AGREGADOS (VIDA, MONEDAS, TEMPORIZADOR) -----------------------------

void iniciarTemporizador(void) {
    tiempo_inicio_juego = GetTime();
    tiempo_final_juego = 0.0;
    temporizador_activo = true;
}

void mostrarTemporizador(void) {
    double tiempo_juego = temporizador_activo ? GetTime() - tiempo_inicio_juego : tiempo_final_juego;
    int segundos_enteros = (int)tiempo_juego;
    int minutos = segundos_enteros / 60;
    int segundos = segundos_enteros % 60;
    int microsegundos = (int)((tiempo_juego - segundos_enteros) * 1000000.0);
    const char *texto = TextFormat("Tiempo %02d:%02d.%06d", minutos, segundos, microsegundos);

    DrawRectangle(10, 10, MeasureText(texto, 20) + 16, 34, Fade(BLACK, 0.65f));
    DrawText(texto, 18, 16, 20, WHITE);
}

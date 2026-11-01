#include "raylib.h"
#include "fondo.h"
#include <stdlib.h>

typedef struct {
    Vector2 pos; 
    float speed;
    int textureIndex;
} Nube;

enum { CANTIDAD_NUBES = 15 };

static Texture2D suelo_fondo;
static Texture2D arbol;
static float desplazamiento = 0.0f;
static Texture2D texturas_nubes[3];
static Nube nubes[CANTIDAD_NUBES];
static Texture2D sol;
static float rotacion_sol = 0.0f;
static Texture2D logo;
static bool mostrar_logo_activo = true;
static Texture2D montanas;

void inicializar_fondo(void) {
    suelo_fondo = LoadTexture("assets/sprites/background/dirt.png");
    arbol = LoadTexture("assets/sprites/background/tree.png");
    texturas_nubes[0] = LoadTexture("assets/sprites/background/cloud1.png");
    texturas_nubes[1] = LoadTexture("assets/sprites/background/cloud2.png");
    texturas_nubes[2] = LoadTexture("assets/sprites/background/cloud3.png");
    sol = LoadTexture("assets/sprites/background/sun.png");
    logo = LoadTexture("assets/sprites/background/logo.png");
    montanas = LoadTexture("assets/sprites/background/mountains.png");

    for (int i = 0; i < CANTIDAD_NUBES; i++) {
        nubes[i].pos.x = (float)(rand() % 900);
        nubes[i].pos.y = (float)(rand() % 150 + 30);
        nubes[i].textureIndex = rand() % 3;
        nubes[i].speed = (float)(rand() % 10 + 10);
    }
}

void actualizar_fondo(float velocidad) {
    desplazamiento -= velocidad * GetFrameTime();
    
    if (desplazamiento <= -suelo_fondo.width) {
        desplazamiento = 0.0f;
    }

    for (int i = 0; i < CANTIDAD_NUBES; i++) {
        nubes[i].pos.x -= nubes[i].speed * GetFrameTime();

        Texture2D textura_nube = texturas_nubes[nubes[i].textureIndex];
        
        if (nubes[i].pos.x < -textura_nube.width) {
            nubes[i].pos.x = 800.0f + (float)(rand() % 300);
            nubes[i].pos.y = (float)(rand() % 150 + 30);
            nubes[i].textureIndex = rand() % 3;
            nubes[i].speed = (float)(rand() % 10 + 10);
        }
    }

    rotacion_sol += GetFrameTime();

    if (rotacion_sol >= 360.0f) {
        rotacion_sol = 0.0f;
    }
}

void mostrar_logo(bool visible) {
    mostrar_logo_activo = visible;
}

void dibujar_fondo(void) {
    float ancho_pantalla = 800.0f;
    int repeticiones_suelo = (480.0f / ancho_pantalla) + 10;
    int repeticiones_arboles = (480.0f / 80) + 40;
    int repeticiones_montanas = (460.0f / 80) + 100;
    for (int i = 0; i < repeticiones_suelo; i++) {
        float posicion_x = desplazamiento + (i * suelo_fondo.width);
        DrawTextureEx(suelo_fondo, (Vector2){posicion_x, 480.0f}, 0.0f, 1.0f, WHITE);
    }

    for (int i = 0; i < repeticiones_montanas; i++) {
        float posicion_x = desplazamiento + (i * montanas.width) - 100;
        DrawTextureEx(montanas, (Vector2){posicion_x, 460.0f}, 0.0f, 2.0f, WHITE);
    }

    for (int i = 0; i < repeticiones_arboles; i++) {
        float posicion_x = desplazamiento + (i * arbol.width);
        DrawTextureEx(arbol, (Vector2){posicion_x, 460.0f}, 0.0f, 1.0f, WHITE);
    }

    Vector2 origen_sol = {(float)sol.width / 40.0f, (float)sol.height};
    Rectangle origen_textura_sol = {0.0f, 0.0f, (float)sol.width, (float)sol.height};
    Rectangle destino_sol = {650.0f, 50.0f, (float)sol.width, (float)sol.height};
    DrawTexturePro(sol, origen_textura_sol, destino_sol, origen_sol, rotacion_sol, WHITE);

    
    for (int i = 0; i < CANTIDAD_NUBES; i++) {
        Texture2D textura = texturas_nubes[nubes[i].textureIndex];
        DrawTextureEx(textura, nubes[i].pos, 0.0f, 1.0f, WHITE);
    }

    if (mostrar_logo_activo) {
        DrawTextureEx(logo, (Vector2){320.0f, 100.0f}, 0.0f, 3.0f, WHITE);
    }
}

void liberar_fondo(void) {
    UnloadTexture(suelo_fondo);
    UnloadTexture(arbol);
    for (int i = 0; i < 3; i++) {
        UnloadTexture(texturas_nubes[i]);
    }
    UnloadTexture(sol);
    UnloadTexture(logo);
    UnloadTexture(montanas);
}

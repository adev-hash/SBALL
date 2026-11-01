#include "raylib.h"
#include "animaciones.h"
#include <stdlib.h>

typedef struct {
    Vector2 posicion;
    float velocidad;
    int fotograma_actual;
    float tiempo_fotograma;
} Ave;

enum {
    CANTIDAD_AVES = 2,
    CANTIDAD_FOTOGRAMAS_AVE = 4
};

static Ave aves[CANTIDAD_AVES];
static Texture2D textura_aves;
static float ancho_fotograma;
static float alto_fotograma;

void inicializar_animaciones(void) {
    Image imagen_aves = LoadImage("assets/sprites/objects/birds.png");
    Rectangle borde_visible = GetImageAlphaBorder(imagen_aves, 0.0f);
    ImageCrop(&imagen_aves, borde_visible);
    textura_aves = LoadTextureFromImage(imagen_aves);
    UnloadImage(imagen_aves);
    SetTextureFilter(textura_aves, TEXTURE_FILTER_POINT);

    ancho_fotograma = (float)textura_aves.width / CANTIDAD_FOTOGRAMAS_AVE;
    alto_fotograma = (float)textura_aves.height;

    for (int i = 0; i < CANTIDAD_AVES; i++) {
        aves[i].posicion.x = (float)(rand() % 900 + 800);
        aves[i].posicion.y = (float)(rand() % 200 + 50);
        aves[i].velocidad = (float)(rand() % 30 + 40);
        aves[i].fotograma_actual = 0;
        aves[i].tiempo_fotograma = 0.0f;
    }
}

void actualizar_animaciones(float velocidad) {
    float tiempo = GetFrameTime();

    for (int i = 0; i < CANTIDAD_AVES; i++) {
        aves[i].posicion.x -= (aves[i].velocidad + velocidad) * tiempo;
        aves[i].tiempo_fotograma += tiempo;

        if (aves[i].tiempo_fotograma >= 0.15f) {
            aves[i].tiempo_fotograma -= 0.15f;
            aves[i].fotograma_actual =
                (aves[i].fotograma_actual + 1) % CANTIDAD_FOTOGRAMAS_AVE;
        }

        if (aves[i].posicion.x < -ancho_fotograma) {
            aves[i].posicion.x = 850.0f + (float)(rand() % 300);
            aves[i].posicion.y = (float)(rand() % 200 + 50);
        }
    }
}

void dibujar_animaciones(void) {
    for (int i = 0; i < CANTIDAD_AVES; i++) {
        Rectangle origen = {
            aves[i].fotograma_actual * ancho_fotograma,
            0.0f,
            ancho_fotograma,
            alto_fotograma
        };
        Rectangle destino = {
            aves[i].posicion.x,
            aves[i].posicion.y,
            ancho_fotograma,
            alto_fotograma
        };

        DrawTexturePro(textura_aves, origen, destino, (Vector2){0.0f, 0.0f},
                       0.0f, WHITE);
    }
}

void liberar_animaciones(void) {
    UnloadTexture(textura_aves);
}

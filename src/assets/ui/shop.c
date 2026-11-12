#include "raylib.h"
#include <stdbool.h>
#include "../../class/class.h"


int monedasGlobales = 0; 
int skinSeleccionadaID = 0; 
bool skinComprada[4] = { true, false, false, false }; 


static Rectangle rBotonSkin0 = { 100, 200, 120, 120 }; 
static Rectangle rBotonSkin1 = { 250, 200, 120, 120 }; 
static Rectangle rBotonSkin2 = { 400, 200, 120, 120 }; 
static Rectangle rBotonSkin3 = { 550, 200, 120, 120 }; 
static Rectangle rBotonVolver = { 300, 480, 200, 50 };  

static Texture2D texturaDefault;
static Texture2D texturaJet;
static Texture2D texturaOvni;
static Texture2D texturaPapel;



static void dibujarTextura(Texture2D tex, Rectangle destino, bool comprada) {
    Rectangle origen = { 0, 0, (float)tex.width, (float)tex.height };
    Color colorX = comprada ? Fade(GREEN, 0.6f) : WHITE;
    DrawTexturePro(tex, origen, destino, (Vector2){0, 0}, 0.0f, colorX);
}

void iniciarTienda(void) {
    texturaDefault =LoadTexture("assets/articles/btn0.png");
    texturaOvni=LoadTexture("assets/articles/btn1.png");
    texturaJet=LoadTexture("assets/articles/btn2.png");
    texturaPapel=LoadTexture("assets/articles/btn3.png");
}

void actualizarTienda(void) {
    Vector2 mouse = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    
        if (CheckCollisionPointRec(mouse, rBotonSkin0)) {
            skinSeleccionadaID = 0;
            actualizarSkinAvion(0);
        }
    
        else if (CheckCollisionPointRec(mouse, rBotonSkin1)) {
            if (skinComprada[1]) {
                skinSeleccionadaID = 1;
                actualizarSkinAvion(1); 
            } else if (monedasGlobales >= 50) {
                monedasGlobales -= 50;  
                skinComprada[1] = true; 
                skinSeleccionadaID = 1;
                guardarSkin();
                actualizarSkinAvion(1); 
            }
        }
        
        else if (CheckCollisionPointRec(mouse, rBotonSkin2)) {
            if (skinComprada[2]) {
                skinSeleccionadaID = 2;
                actualizarSkinAvion(2);
            } else if (monedasGlobales >= 100) {
                monedasGlobales -= 100;
                skinComprada[2] = true;
                guardarSkin();
                skinSeleccionadaID = 2;
                actualizarSkinAvion(2);
            }
        }
    
        else if (CheckCollisionPointRec(mouse, rBotonSkin3)) {
            if (skinComprada[3]) {
                skinSeleccionadaID = 3;
                actualizarSkinAvion(3);
            } else if (monedasGlobales >= 150) {
                monedasGlobales -= 150;
                skinComprada[3] = true;
                guardarSkin();
                skinSeleccionadaID = 3;
                actualizarSkinAvion(3);
            }
        }
    }
}


void dibujarTienda(void) {

    ClearBackground(DARKBLUE);
    DrawText("TIENDA DE AVIONES", 250, 80, 30, WHITE);
    
    DrawText(TextFormat("ZENITS: %d", monedasGlobales), 50, 40, 20, WHITE);

    Color color0;
    if (skinSeleccionadaID == 0) {
        color0 = GREEN;
    } else {
        color0 = LIGHTGRAY;
    }
    DrawRectangleRec(rBotonSkin0, color0);
    dibujarTextura(texturaDefault, rBotonSkin0, skinComprada[0]);
    DrawText("FREE", rBotonSkin0.x + 10, rBotonSkin0.y + 10, 20, WHITE);


    Color color1;
    if (skinSeleccionadaID == 1) {
        color1 = GREEN;
    } else {
        if (skinComprada[1]) {
            color1 = LIGHTGRAY;
        } else {
            color1 = GRAY;
        }
    }
    DrawRectangleRec(rBotonSkin1, color1);
    dibujarTextura(texturaJet, rBotonSkin1, skinComprada[1]);
    if (skinComprada[1]) {
        DrawText("PURCHSED!", rBotonSkin1.x + 2, rBotonSkin1.y + 10, 20, WHITE);
    } else {
        DrawText("$50", rBotonSkin1.x + 10, rBotonSkin1.y + 10, 20, WHITE);
    }

    
    Color color2;
    if (skinSeleccionadaID == 2) {
        color2 = GREEN;
    } else {
        if (skinComprada[2]) {
            color2 = LIGHTGRAY;
        } else {
            color2 = GRAY;
        }
    }
    DrawRectangleRec(rBotonSkin2, color2);
    dibujarTextura(texturaOvni, rBotonSkin2, skinComprada[2]);

    if (skinComprada[2]) {
        DrawText("PURCHSED!", rBotonSkin2.x + 2, rBotonSkin2.y + 10, 20, WHITE);
    } else {
        DrawText("$100", rBotonSkin2.x + 10, rBotonSkin2.y + 10, 20, WHITE);
    }

    Color color3;
    if (skinSeleccionadaID == 3) {
        color3 = GREEN;
    } else {
        if (skinComprada[3]) {
            color3 = LIGHTGRAY;
        } else {
            color3 = GRAY;
        }
    }
    DrawRectangleRec(rBotonSkin3, color3);
    dibujarTextura(texturaPapel, rBotonSkin3, skinComprada[3]);
    if (skinComprada[3]) {
        DrawText("PURCHSED", rBotonSkin3.x + 2, rBotonSkin3.y + 10, 20, WHITE);
    } else {
        DrawText("$150", rBotonSkin3.x + 10, rBotonSkin3.y + 10, 20, WHITE);
    }

    DrawRectangleRec(rBotonVolver, RED);
    DrawText("Volver al Menu", rBotonVolver.x + 35, rBotonVolver.y + 15, 16, WHITE);
}


void descargarTienda(void) {
    UnloadTexture(texturaDefault);
    UnloadTexture(texturaJet);
    UnloadTexture(texturaOvni);
    UnloadTexture(texturaPapel);
};

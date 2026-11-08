#include "raylib.h"
#include "../../class/class.h"

//inicia en 100 para pruebas, cambiar al hacer lo de las monedas 
int monedasGlobales = 300; 
static int skinSeleccionadaID = 0; 
static bool skinComprada[4] = { true, false, false, false }; 


//botones provisionales para la ventana de la tienda

static Rectangle rBotonSkin0 = { 100, 200, 120, 120 }; 
static Rectangle rBotonSkin1 = { 250, 200, 120, 120 }; 
static Rectangle rBotonSkin2 = { 400, 200, 120, 120 }; 
static Rectangle rBotonSkin3 = { 550, 200, 120, 120 }; 
static Rectangle rBotonVolver = { 300, 480, 200, 50 };  


extern void actualizarSkinAvion(int nuevoSkinID);

void iniciarTienda(void) {
    // hacer a logica para cargar las texturas 
}

void actualizarTienda(void) {
    Vector2 mouse = GetMousePosition();

    // Lógica de clics para comprar o equipar skins
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
                skinSeleccionadaID = 3;
                actualizarSkinAvion(3);
            }
        }
    }
}


void dibujarTienda(void) {

    ClearBackground(DARKBLUE);
    DrawText("TIENDA DE AVIONES", 250, 80, 30, WHITE);
    
    DrawText(TextFormat("Monedas: %d", monedasGlobales), 50, 40, 20, YELLOW);

    Color color0;
    if (skinSeleccionadaID == 0) {
        color0 = GREEN;
    } else {
        color0 = LIGHTGRAY;
    }
    DrawRectangleRec(rBotonSkin0, color0);
    DrawText("Default", rBotonSkin0.x + 20, rBotonSkin0.y + 50, 14, BLACK);


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
    if (skinComprada[1]) {
        DrawText("Skin 1 (Equipada)", rBotonSkin1.x + 10, rBotonSkin1.y + 50, 12, BLACK);
    } else {
        DrawText("Skin 1 ($50)", rBotonSkin1.x + 10, rBotonSkin1.y + 50, 12, BLACK);
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
    if (skinComprada[2]) {
        DrawText("Skin 2 (Equipada)", rBotonSkin2.x + 10, rBotonSkin2.y + 50, 12, BLACK);
    } else {
        DrawText("Skin 2 ($100)", rBotonSkin2.x + 10, rBotonSkin2.y + 50, 12, BLACK);
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
    if (skinComprada[3]) {
        DrawText("Skin 3 (Equipada)", rBotonSkin3.x + 10, rBotonSkin3.y + 50, 12, BLACK);
    } else {
        DrawText("Skin 3 ($150)", rBotonSkin3.x + 10, rBotonSkin3.y + 50, 12, BLACK);
    }

    DrawRectangleRec(rBotonVolver, RED);
    DrawText("Volver al Menu", rBotonVolver.x + 35, rBotonVolver.y + 15, 16, WHITE);
}


void descargarTienda(void) {
    // hacer la logica para liberar los recursos de la tienda
}
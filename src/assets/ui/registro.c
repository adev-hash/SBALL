#include "raylib.h"
#include "../../class/class.h"
#include <stdio.h>
#include <string.h>
#define RUTA_REGISTROS "scores/Registros.dat"

Texture2D registro; 
Texture2D honor;
Texture2D nada;
Texture2D interfaz;
Vector2 mouse;

typedef struct
{
    char nom[4];
    int t;
} Puntos;

int pantalla;

int escribir_archivo(Puntos *);
int cregistro = 0, cpodio = 0, cnada = 0;

// Coordenadas del dibujo del menú de registro
Rectangle rRegistro = {150, 20, 450, 450};

// Coordenadas de dibujo de las letras
Rectangle letra1 = {299, 260, 50, 45};
Rectangle letra2 = {369, 260, 50, 45};;
Rectangle letra3 = {440, 260, 50, 45};

char l1[2] = "\0";
char l2[2] = "\0";
char l3[2] = "\0";

void iniciarRegistro(void){
    registro = LoadTexture("assets/sprites/background/register.png");
    nada = LoadTexture("assets/sprites/background/noting.png");
    honor = LoadTexture("assets/sprites/background/honor.png");
}

void registrarPuntaje(void){
    ClearBackground(BLUE);
    interfaz = registro;
    int c1 = 0, s1 = 0, s2 = 0, s3 = 0;
    
    DrawTexturePro(interfaz, (Rectangle){0, 0, (float)interfaz.width, (float)interfaz.height}, rRegistro, (Vector2){0,0}, 0.0f, WHITE);
    DrawRectangleRec(letra1, BROWN);
    DrawRectangleRec(letra2, BROWN);
    DrawRectangleRec(letra3, BROWN);
    mouse = GetMousePosition();
    


    if(CheckCollisionPointRec(mouse, letra1)){
        c1 = GetCharPressed();
        if(c1 >= 32 && c1 <= 125){
            l1[0] = (char)c1;
            l1[1] = '\0';
        }
    }
    else if(CheckCollisionPointRec(mouse, letra2)){
        c1 = GetCharPressed();
        if(c1 >= 32 && c1 <= 125){
            l2[0] = (char)c1;
            l2[1] = '\0';
        }
    }
    else if(CheckCollisionPointRec(mouse, letra3)){
        c1 = GetCharPressed();
        if(c1 >= 32 && c1 <= 125){
            l3[0] = (char)c1;
            l3[1] = '\0';
        }
    }

    if(strcmp(l1, "\0") != 0){
        DrawText(TextToUpper(l1), (int)letra1.x + 15, (int)letra1.y + 7, 35, BLACK);
        s1 = 1;
    } else {
        DrawText(TextToUpper("\0"), (int)letra1.x + 25, (int)letra1.y - 5, 85, BLACK);
        s1 = 0;
    }

    if(strcmp(l2, "\0") != 0){
        DrawText(TextToUpper(l2), (int)letra2.x + 15, (int)letra2.y + 7, 35, BLACK);
        s2 = 1;
    } else {
        DrawText(TextToUpper("\0"), (int)letra2.x + 25, (int)letra2.y - 5, 85, BLACK);
        s2 = 0;
    }

    if(strcmp(l3, "\0") != 0) {
        DrawText(TextToUpper(l3), (int)letra3.x + 15, (int)letra3.y + 7, 35, BLACK);
        s3 = 1;
    } else {
        DrawText(TextToUpper(l3), (int)letra3.x + 25, (int)letra3.y - 5, 85, BLACK);
        s3 = 0;
    }

     double tiempo = obtenerTiempoFinal();
    DrawText(TextFormat("FINAL TIME: %02d seg", (int)tiempo), (int)320, (int)335, 18, BLACK);
    DrawText("PRESS ENTER - EXIT", 290, 380, 20, BLACK);

    if(s1 == 1 && s2 == 1 && s3 == 1 && IsKeyPressed(KEY_ENTER)){
        Puntos persona;
         memset(&persona, 0, sizeof(persona));
        persona.nom[0] = l1[0];
        persona.nom[1] = l2[0];
        persona.nom[2] = l3[0];
        persona.t = tiempo; // Guardamos el tiempo capturado
        
        if(escribir_archivo(&persona) == 0) {
            memset(l1, '\0', sizeof(l1));
            memset(l2, '\0', sizeof(l2));
            memset(l3, '\0', sizeof(l3));
            pantalla = 0;
            ShowLogo(true);            
        }
        else{
            puts("No se pudo abrir el archivo para hacer el registro\n");
        }
    }
}

int escribir_archivo(Puntos *n){
    FILE *archivo;
    archivo = fopen(RUTA_REGISTROS, "ab+");
    if(archivo == NULL){
        return 1;
    }
    fwrite(n, sizeof(Puntos), 1, archivo);
    fclose(archivo);
    return 0;
}


void obtenerPuntaje(void){
    FILE *abrir;
    Puntos persona_leer;
    Puntos p1 = {"---", 0};
    Puntos p2 = {"---", 0};
    Puntos p3 = {"---", 0};
    int total_registros = 0;

    abrir = fopen(RUTA_REGISTROS, "rb+");
    if(abrir != NULL) {
        while (fread(&persona_leer, sizeof(Puntos), 1, abrir) > 0)
        {
            persona_leer.nom[3] = '\0';
            total_registros++;
            if(persona_leer.t > p1.t){
                p3 = p2;
                p2 = p1;
                p1 = persona_leer;
            }
            else if(persona_leer.t > p2.t && strcmp(persona_leer.nom, p1.nom) != 0){
                p3 = p2;
                p2 = persona_leer;
            }
            else if(persona_leer.t > p3.t && strcmp(persona_leer.nom, p1.nom) != 0 && strcmp(persona_leer.nom, p2.nom) != 0){
                p3 = persona_leer;
            }
        }
        fclose(abrir);
    }

    // Seleccionar textura según si existen registros válidos
    if(total_registros == 0) {
        interfaz = nada;             
    } else {
        interfaz = honor;
    }

    Rectangle rHonor = {150, 100, 525, 450};
    Rectangle rSalir = {325, 450, 187, 60};
    mouse = GetMousePosition();

    // Usar el ancho y alto real de la textura actual para evitar deformaciones
    DrawTexturePro(interfaz, (Rectangle){0, 0, (float)interfaz.width, (float)interfaz.height}, rHonor, (Vector2){0,0}, 0.0f, WHITE);

    if(total_registros > 0){
        DrawText(TextFormat("%s:%02d seg", TextToUpper(p1.nom), p1.t), (int)320, (int)200, 20, GOLD);
        DrawText(TextFormat("%s:%02d seg", TextToUpper(p2.nom), p2.t), (int)320, (int)270, 20, GRAY);
        DrawText(TextFormat("%s:%02d seg", TextToUpper(p3.nom), p3.t), (int)320, (int)345, 20, ORANGE);
    }

    if(CheckCollisionPointRec(mouse, rSalir) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        pantalla = 0;
    }
}

void liberarRegistro(void){
    UnloadTexture(registro);
    UnloadTexture(honor);
    UnloadTexture(nada);
}

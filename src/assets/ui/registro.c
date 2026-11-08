#include "../../class/class.h"
#include "raylib.h"
#include<stdio.h>
#include<string.h>
Texture2D registro; 
Texture2D salir;
Vector2 mouse;
typedef struct
{
    char nom[3];
    int t;
}Puntos;
int escribir_archivo(Puntos *);
//Coordenadas del dibujo del menu de registro
Rectangle rRegistro = {100,100,600,400};
//Coordenadas de dibujo de las letras
Rectangle letra1 = {215,210,100,65};
Rectangle letra2 = {345,210,100,65};
Rectangle letra3 = {480,210,100,65};
Rectangle registrar = {275,380,247.5,68.7};

char l1[2] = "\0";
char l2[2] = "\0";
char l3[2] = "\0";

void registrar_puntaje(){
    ClearBackground(BLUE);
    registro = LoadTexture("assets/sprites/background/registro.png");
    int c1 = 0,s1 = 0,s2 = 0,s3 = 0;
    DrawTexturePro(registro,(Rectangle){0, 0, (float)registro.width, (float)registro.height},rRegistro,(Vector2){0,0},0.0f,WHITE);
    DrawRectangleRec(letra1,WHITE);
    DrawRectangleRec(letra2,WHITE);
    DrawRectangleRec(letra3,WHITE);
    mouse = GetMousePosition();
    Puntos persona;
    if(CheckCollisionPointRec(mouse,letra1)){
        c1  = GetCharPressed();
        if(c1 >= 32 && c1 <= 125){
            l1[0] = (char)c1;
            l1[1] = '\0';
        }
    }
    else if(CheckCollisionPointRec(mouse,letra2)){
        c1  = GetCharPressed();
        if(c1 >= 32 && c1 <= 125){
            l2[0] = (char)c1;
            l2[1] = '\0';
        }
    }
    else if(CheckCollisionPointRec(mouse,letra3)){
        c1  = GetCharPressed();
        if(c1 >= 32 && c1 <= 125){
            l3[0] = (char)c1;
            l3[1] = '\0';
        }
    }
    if(strcmp(l1,"\0") != 0){
        DrawText(TextToUpper(l1), (int)letra1.x+25, (int)letra1.y-5, 85, BLACK);
        s1 = 1;
    } else 
    {
        DrawText(TextToUpper("\0"), (int)letra1.x+25, (int)letra1.y-5, 85, BLACK);
        s1 = 0;
    }
    if(strcmp(l2,"\0") != 0){
        DrawText(TextToUpper(l2), (int)letra2.x+25, (int)letra2.y-5, 85, BLACK);
        s2 = 1;
    } else {
        DrawText(TextToUpper("\0"), (int)letra2.x+25, (int)letra2.y-5, 85, BLACK);
        s2 = 0;
    }
    if(strcmp(l3,"\0") != 0) {
        DrawText(TextToUpper(l3), (int)letra3.x+25, (int)letra3.y-5, 85, BLACK);
        s3 = 1;
    }else {
        DrawText(TextToUpper(l3), (int)letra3.x+25, (int)letra3.y-5, 85, BLACK);
        s3 = 0;
    }
    DrawText(TextFormat("Tiempo final: %02d seg",(int)tiempo),(int)150, (int)300, 50, BLACK);
    if(CheckCollisionPointRec(mouse,registrar) && s1 == 1 && s2 == 1 && s3 == 1 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        persona.nom[0] = l1[0];
        persona.nom[1] = l2[0];
        persona.nom[2] = l3[0];
        persona.t = (int)tiempo;
        if(escribir_archivo(&persona) == 0) {
            escribir_archivo(&persona);
            memset(l1,'\0',sizeof(l1));
            memset(l2,'\0',sizeof(l2));
            memset(l3,'\0',sizeof(l3));
            pantalla = 0;
            ShowLogo(true);
            reiniciarPartida();
        }
    }
}
void limpiarRegistro(void){
    UnloadTexture(registro);
    UnloadTexture(salir);
}
int escribir_archivo(Puntos * n){
    FILE * archivo;
    archivo = fopen("Registros.dat","ab");
    if(archivo == NULL){
        puts("No se pudo abrir el archivo");
        return 1;
    }
    fwrite(n,sizeof(Puntos),1,archivo);
    fclose(archivo);
    return 0;
}
void obtener_puntaje(){
    FILE *abrir;
    Puntos persona_leer;
    Puntos p1 = {"\0",0};
    Puntos p2 = {"\0",0};
    Puntos p3 = {"\0",0};
    abrir = fopen("Registros.dat","rb");
    if(abrir == NULL) {
        salir = LoadTexture("assets/sprites/background/nada.png");
    }
    else{
        salir = LoadTexture("assets/sprites/background/honor.png");
        while (fread(&persona_leer,sizeof(Puntos),1,abrir) > 0)
        {
            if(persona_leer.t > p1.t){
                p3 = p2;
                p2 = p1;
                p1 = persona_leer;
            }
            else if(persona_leer.t > p2.t){
                p3 = p2;
                p2 = persona_leer;
            }
            else if(persona_leer.t > p3.t){
                p3 = persona_leer;
            }
        }
        fclose(abrir);
    }
    Rectangle rHonor = {150,100,525,450};
    Rectangle rSalir = {325,450,187,60};
    mouse = GetMousePosition();
    DrawTexturePro(salir,(Rectangle){0, 0, (float)rHonor.width, (float)rHonor.height},rHonor,(Vector2){0,0},0.0f,WHITE);
    if(abrir != NULL){
        DrawText(TextFormat("%s-%02d seg",TextToUpper(p1.nom),p1.t),(int)325, (int)205, 50, BLACK);
        DrawText(TextFormat("%s-%02d seg",TextToUpper(p2.nom),p2.t),(int)325, (int)305, 50, BLACK);
        DrawText(TextFormat("%s-%02d seg",TextToUpper(p3.nom),p3.t),(int)325, (int)380, 50, BLACK);
    }
    if(CheckCollisionPointRec(mouse,rSalir) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        pantalla = 0;
    }
    
}
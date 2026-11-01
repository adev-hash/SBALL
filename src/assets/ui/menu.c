#include "raylib.h"
#include "fondo.h"
#include "menu.h"

void iniciar_interfaz(void) {
    InitWindow(800, 600, "Main Menu"); //Medidas de la ventana
    InitAudioDevice();
    SetExitKey(KEY_NULL); // Evita que al persionar Esc se salga. Esto es util para el menu salida
    SetTargetFPS(60); // FPS
    inicializar_fondo();
    float bgSpeed  = 50.0; 


    int pantalla = 0;

    //Texturas de los botones
    Texture2D btnPlay = LoadTexture("assets/sprites/buttons/btnPlay.png");
    Texture2D btnOptions = LoadTexture("assets/sprites/buttons/btnOptions.png");
    Texture2D btnExit = LoadTexture("assets/sprites/buttons/btnExit.png");

                    // x - y - Ancho - Alto 
    //Coordenadas de dibujo de los botones
    Rectangle rPlay =  { 300, 200, 200, 170};
    Rectangle rOption =  { 300, 270, 200, 170};
    Rectangle rExit =  { 300, 340, 200, 170};

    //Coordenadas de presion de los botones [NO TOCAR]
    Rectangle cPlay   = { 300, 260, 200, 50 };
    Rectangle cOption = { 300, 330, 200, 50 };
    Rectangle cExit   = { 300, 400, 200, 50 };

    static Music soundtrack;
    soundtrack = LoadMusicStream("assets/audio/soundtrack.mp3");
    PlayMusicStream(soundtrack);


    //Logica de ventana 
    while(!WindowShouldClose()){
        Vector2 mouse = GetMousePosition();
        UpdateMusicStream(soundtrack);

        if(pantalla == 0){

            if (CheckCollisionPointRec(mouse, cPlay) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                pantalla = 1;
                mostrar_logo(false);
            }

            if (CheckCollisionPointRec(mouse, cOption) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                pantalla = 2;
                mostrar_logo(false);
            }

            if (CheckCollisionPointRec(mouse, cExit) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                break;
            }
           
        } else {
            if(IsKeyPressed(KEY_ESCAPE)){pantalla = 0; mostrar_logo(true);}
        }

        //Dibujado de la ventana

        actualizar_fondo(bgSpeed);
        BeginDrawing();
        ClearBackground(BLUE);
        dibujar_fondo();
        if(pantalla == 0){
                // Textura, Recorte origen (completo), Rectángulo destino (pantalla), Pivote rotación (sup-izq), Ángulo (0°), Color original
                DrawTexturePro(btnPlay, (Rectangle){0, 0, (float)btnPlay.width, (float)btnPlay.height}, rPlay, (Vector2){0, 0}, 0.0f, WHITE);
                DrawTexturePro(btnOptions, (Rectangle){0, 0, (float)btnOptions.width, (float)btnOptions.height}, rOption, (Vector2){0, 0}, 0.0f, WHITE);
                DrawTexturePro(btnExit, (Rectangle){0, 0, (float)btnExit.width, (float)btnExit.height}, rExit, (Vector2){0, 0}, 0.0f, WHITE);
        }else if(pantalla == 1){
            
        }else if(pantalla == 2){
        
        }
        EndDrawing();
    }
    liberar_fondo();
    //Liberamos todas las texturas al cerrar.
    UnloadTexture(btnPlay);
    UnloadTexture(btnOptions);
    UnloadTexture(btnExit);
    CloseAudioDevice();
    CloseWindow();
    return;
}
#include "raylib.h"
#include "../../class/class.h"

// Declaración de función externa (si está en otro módulo)
void ShowLogo(bool visible);

void ejecutarInterfaz(void) {
    InitWindow(800, 600, "Main Menu"); // Medidas de la ventana
    InitAudioDevice();
    SetExitKey(KEY_NULL); // Evita que al presionar Esc se salga
    SetTargetFPS(60);     // FPS

    //inicializa modulos del juego
    iniciarFondo();
    iniciarAvion();
    inciarPajarracos();

    float bgSpeed = 50.0f; 
    int pantalla = 0; // 0: menu, 1: juego, 2: tienda
    
    // Texturas de los botones
    Texture2D btnPlay = LoadTexture("assets/sprites/buttons/btnPlay.png");
    Texture2D btnOptions = LoadTexture("assets/sprites/buttons/btnShop.png");
    Texture2D btnExit = LoadTexture("assets/sprites/buttons/btnExit.png");

    // Coordenadas de dibujo de los botones
    Rectangle rPlay   = { 300, 200, 200, 170 };
    Rectangle rOption = { 300, 270, 200, 170 };
    Rectangle rExit   = { 300, 340, 200, 170 };

    // Coordenadas de presión de los botones
    Rectangle cPlay   = { 300, 260, 200, 50 };
    Rectangle cOption = { 300, 330, 200, 50 };
    Rectangle cExit   = { 300, 400, 200, 50 };

    // En C, las variables estáticas se inicializan de forma limpia
    Music soundtrack = LoadMusicStream("assets/audio/soundtrack.mp3");
    Music forest = LoadMusicStream("assets/audio/forest.mp3");
    PlayMusicStream(soundtrack);
    PlayMusicStream(forest);

    // Lógica de ventana 
    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();
        UpdateMusicStream(soundtrack);

        //Logica (Separada del draw para evitar que se solapen)
        actualizarFondo(bgSpeed);

        if (pantalla == 0) {
            if (CheckCollisionPointRec(mouse, cPlay) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                pantalla = 1;
                ShowLogo(false);
                PauseMusicStream(soundtrack);
            } 
            else if (CheckCollisionPointRec(mouse, cOption) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                pantalla = 2;
                ShowLogo(false);
            } 
            else if (CheckCollisionPointRec(mouse, cExit) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                break;
            }
        } 
        else if (pantalla == 1) {
            UpdateMusicStream(forest);
            actualizarAvion();
            actualizarPajarracos(bgSpeed);

            if (verificarColisionPajarraco()) {
                pantalla = 0;
                ShowLogo(true);
                ResumeMusicStream(soundtrack);
            }
        } 
        else if (pantalla == 2) {
            if (IsKeyPressed(KEY_ESCAPE)) {
                pantalla = 0; 
                ShowLogo(true);
            }
        }

        // draw
        BeginDrawing();
            ClearBackground(BLUE);
            dibujarFondo();
            
            if (pantalla == 0) {
                DrawTexturePro(btnPlay, (Rectangle){0, 0, (float)btnPlay.width, (float)btnPlay.height}, rPlay, (Vector2){0,0}, 0.0f, WHITE);
                DrawTexturePro(btnOptions, (Rectangle){0, 0, (float)btnOptions.width, (float)btnOptions.height}, rOption, (Vector2){0,0}, 0.0f, WHITE);
                DrawTexturePro(btnExit, (Rectangle){0, 0, (float)btnExit.width, (float)btnExit.height}, rExit, (Vector2){0,0}, 0.0f, WHITE);
            } 
            else if (pantalla == 1) {
                mostrarAvion();
                mostrarPajarracos();
                verificarColisionPajarraco();
                mostrarVida();
            } 
            else if (pantalla == 2) {
                // DrawShop(mouse);
            }
        EndDrawing();
    }

    // Liberar recursos

    descargarFondo();
    descargarAvion();
    descargarPajarracos();

    UnloadTexture(btnPlay);
    UnloadTexture(btnOptions);
    UnloadTexture(btnExit);

    UnloadMusicStream(soundtrack);
    UnloadMusicStream(forest);
    CloseAudioDevice();
    CloseWindow();
}

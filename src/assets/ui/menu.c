#include "raylib.h"
#include "../../class/class.h"

// Declaración de función externa (si está en otro módulo)
void ShowLogo(bool visible);
int gameOver = 0;
void ejecutarInterfaz(void) {
    InitWindow(800, 600, "Main Menu"); // Medidas de la ventana
    InitAudioDevice();
    SetExitKey(KEY_NULL); // Evita que al presionar Esc se salga
    SetTargetFPS(60);     // FPS

    //inicializa modulos del juego
    iniciarFondo();
    iniciarAvion();
    iniciarPajarracos();

    float bgSpeed = 50.0f; 
    int pantalla = 0; // 0: menu, 1: juego, 2: tienda
    
    // Texturas de los botones
    Texture2D btnPlay = LoadTexture("assets/sprites/buttons/btnPlay.png");
    Texture2D btnOptions = LoadTexture("assets/sprites/buttons/btnShop.png");
    Texture2D btnExit = LoadTexture("assets/sprites/buttons/btnExit.png");
    Texture2D btnReload = LoadTexture("assets/sprites/buttons/reload.png");
    Texture2D btnexit = LoadTexture("assets/sprites/buttons/exit.png");
    Texture2D logoGO = LoadTexture("assets/sprites/background/GAMEOVER.png");


    // Coordenadas de dibujo de los botones
    Rectangle rPlay   = { 300, 200, 200, 170 };
    Rectangle rOption = { 300, 270, 200, 170 };
    Rectangle rExit   = { 300, 340, 200, 170 };
    Rectangle reload = {200,300,200,200};
    Rectangle exit = {400,300,200,200};

    // Coordenadas de presión de los botones
    Rectangle cPlay   = { 300, 260, 200, 50 };
    Rectangle cOption = { 300, 330, 200, 50 };
    Rectangle cExit   = { 300, 400, 200, 50 };
    Rectangle cReload = {200,300,200,200};
    Rectangle Cexit = {400,300,200,200};

    // En C, las variables estáticas se inicializan de forma limpia
    Music soundtrack = LoadMusicStream("assets/audio/soundtrack.mp3");
    Music forest = LoadMusicStream("assets/audio/forest.mp3");
    Music engine = LoadMusicStream("assets/audio/planesound.wav");
    Music actionS = LoadMusicStream("assets/audio/soundtrack1.mp3");
    Music gameOverS = LoadMusicStream("assets/audio/gameover.mp3");
    PlayMusicStream(gameOverS);
    PlayMusicStream(actionS);
    PlayMusicStream(soundtrack);
    PlayMusicStream(forest);
    PlayMusicStream(engine);

    // Lógica de ventana 
    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();
        UpdateMusicStream(soundtrack);

        //Logica (Separada del draw para evitar que se solapen)
        if (gameOver == 0) {
            actualizarFondo(bgSpeed);
        }

        if (pantalla == 0) {
            if (CheckCollisionPointRec(mouse, cPlay) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                pantalla = 1;
                reiniciarPartida();
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
            if (gameOver == 0) {
                UpdateMusicStream(forest);
                UpdateMusicStream(engine);
                UpdateMusicStream(actionS);
                actualizarAvion();
                actualizarPajarracos(bgSpeed);
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

        if(gameOver == 0){
            if (pantalla == 0) {
                DrawTexturePro(btnPlay, (Rectangle){0, 0, (float)btnPlay.width, (float)btnPlay.height}, rPlay, (Vector2){0,0}, 0.0f, WHITE);
                DrawTexturePro(btnOptions, (Rectangle){0, 0, (float)btnOptions.width, (float)btnOptions.height}, rOption, (Vector2){0,0}, 0.0f, WHITE);
                DrawTexturePro(btnExit, (Rectangle){0, 0, (float)btnExit.width, (float)btnExit.height}, rExit, (Vector2){0,0}, 0.0f, WHITE);
                ResumeMusicStream(soundtrack);
            } 
            else if (pantalla == 1 && gameOver == 0) {
                mostrarAvion();
                mostrarPajarracos();
                verificarColisionPajarraco();
                mostrarTemporizador();
            } 
            else if (pantalla == 2) {
                // DrawShop(mouse);
            }
        }
        else{
            UpdateMusicStream(gameOverS);
            Vector2 posGameOver = {115,15};
            DrawTexturePro(btnReload, (Rectangle){0, 0, (float)btnReload.width, (float)btnReload.height}, reload, (Vector2){0,0}, 0.0f, WHITE);
            DrawTexturePro(btnexit, (Rectangle){0, 0, (float)btnexit.width, (float)btnexit.height}, exit, (Vector2){0,0}, 0.0f, WHITE);
            DrawTextureEx(logoGO,posGameOver,0.0f,10.0f,WHITE);
            mostrarTemporizador();
            if (CheckCollisionPointRec(mouse, Cexit) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                pantalla = 0;
                gameOver = 0;
                ShowLogo(true);
            }
            if(CheckCollisionPointRec(mouse,cReload) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                pantalla = 1;
                reiniciarPartida();
            }
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
    UnloadTexture(btnReload);
    UnloadTexture(btnexit);
    UnloadTexture(logoGO);
    UnloadMusicStream(soundtrack);
    UnloadMusicStream(engine);
    UnloadMusicStream(forest);
    UnloadMusicStream(actionS);
    CloseAudioDevice();
    CloseWindow();
}
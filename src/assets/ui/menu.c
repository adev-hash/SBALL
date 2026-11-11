#include "raylib.h"
#include "../../class/class.h"

void ShowLogo(bool visible);
int pantalla = 0, cerrado = 0; 
Rectangle menuGameOver;
Vector2 posGameOver;

void ejecutarInterfaz(void) {
    InitWindow(800, 600, "Main Menu");
    InitAudioDevice();
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);

    iniciarFondo();
    iniciarAvion();
    iniciarPajarracos();
    iniciarTienda();
    iniciarRegistro();
    iniciarMonedas();
    float bgSpeed = 50.0f; 
    
    Texture2D btnPlay = LoadTexture("assets/sprites/buttons/btnPlay.png");
    Texture2D btnOptions = LoadTexture("assets/sprites/buttons/btnShop.png");
    Texture2D btnExit = LoadTexture("assets/sprites/buttons/btnExit.png");
    Texture2D btnReload = LoadTexture("assets/sprites/buttons/reload.png");
    Texture2D btnexit = LoadTexture("assets/sprites/buttons/exit.png");
    Texture2D logoGO = LoadTexture("assets/sprites/background/GAMEOVER.png");
    Texture2D btnPodium = LoadTexture("assets/sprites/buttons/podium.png");

    Rectangle rPlay   = { 300, 200, 200, 170 };
    Rectangle rOption = { 300, 270, 200, 170 };
    Rectangle rExit   = { 300, 340, 200, 170 };
    Rectangle reload = {200,300,200,200};
    Rectangle exit = {400,300,200,200};
    Rectangle rPod = {470, 100, 100, 100};

    Rectangle cPlay   = { 300, 260, 200, 50 };
    Rectangle cOption = { 300, 330, 200, 50 };
    Rectangle cExit   = { 300, 400, 200, 50 };
    
    Music soundtrack = LoadMusicStream("assets/audio/soundtrack.mp3");
    Music engine = LoadMusicStream("assets/audio/planesound.wav");
    Music actionS = LoadMusicStream("assets/audio/soundtrack1.mp3");
    Music gameOverS = LoadMusicStream("assets/audio/gameover.mp3");
    Music records = LoadMusicStream("assets/audio/scores.mp3");
    PlayMusicStream(soundtrack);
    PlayMusicStream(gameOverS);
    PlayMusicStream(actionS);
    PlayMusicStream(soundtrack);
    PlayMusicStream(engine);
    PlayMusicStream(records);
    while (!WindowShouldClose() && cerrado == 0) {
        Vector2 mouse = GetMousePosition();
        actualizarFondo(bgSpeed);
        UpdateMusicStream(soundtrack);
        switch (pantalla)
        {
        case 0:
            if (CheckCollisionPointRec(mouse, cPlay) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                pantalla = 1;
                ShowLogo(false);
                iniciarTemporizador();
                PauseMusicStream(soundtrack);
            } 
            else if (CheckCollisionPointRec(mouse, cOption) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                pantalla = 2;
                ShowLogo(false);
            } 
            else if (CheckCollisionPointRec(mouse, cExit) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                cerrado = 1;
                break;
            }
            else if(CheckCollisionPointRec(mouse, rPod) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                pantalla = 5;
            }
            break;
        case 1:
            UpdateMusicStream(actionS);
            UpdateMusicStream(engine);
            if (!IsMusicStreamPlaying(actionS)) {
                PlayMusicStream(actionS);
            }
            if (!IsMusicStreamPlaying(engine)) {
                PlayMusicStream(engine);
            }
            actualizarAvion();
            actualizarPajarracos(bgSpeed);
            actualizarMonedas(bgSpeed);
            break;
        case 2: 
            actualizarTienda();
            if (IsKeyPressed(KEY_ESCAPE)) {
                pantalla = 0; 
                ShowLogo(true);
            }
            break;
        case 3:
            UpdateMusicStream(gameOverS);
            if (!IsMusicStreamPlaying(gameOverS)) {
                PlayMusicStream(gameOverS);
            }
            break;
        case 4:
            UpdateMusicStream(records);
            if (!IsMusicStreamPlaying(records)) {
                PlayMusicStream(records);
            }
            registrarPuntaje();
            break;
        case 5:
            obtenerPuntaje();
            break;
        }
        BeginDrawing();
        ClearBackground(BLUE);
            switch (pantalla)
            {
            case 0:
                dibujarFondo();
                DrawTexturePro(btnPlay, (Rectangle){0, 0, (float)btnPlay.width, (float)btnPlay.height}, rPlay, (Vector2){0,0}, 0.0f, WHITE);
                DrawTexturePro(btnOptions, (Rectangle){0, 0, (float)btnOptions.width, (float)btnOptions.height}, rOption, (Vector2){0,0}, 0.0f, WHITE);
                DrawTexturePro(btnExit, (Rectangle){0, 0, (float)btnExit.width, (float)btnExit.height}, rExit, (Vector2){0,0}, 0.0f, WHITE);
                DrawTexturePro(btnPodium, (Rectangle){0, 0, (float)btnPodium.width, (float)btnPodium.height}, rPod, (Vector2){0,0}, 0.0f, WHITE);
                ResumeMusicStream(soundtrack);
                break;
            case 1:
                dibujarFondo();
                mostrarAvion();
                mostrarPajarracos();
                mostrarMonedas();
                verificarColisionPajarraco();
                mostrarTemporizador();
                break;
            case 2:
                dibujarTienda();
                break;
            case 3:
                posGameOver = (Vector2){115,15};
                menuGameOver = (Rectangle){100,100,600,400};
                DrawTexturePro(btnReload, (Rectangle){0, 0, (float)btnReload.width, (float)btnReload.height}, reload, (Vector2){0,0}, 0.0f, WHITE);
                DrawTexturePro(btnexit, (Rectangle){0, 0, (float)btnexit.width, (float)btnexit.height}, exit, (Vector2){0,0}, 0.0f, WHITE);
                DrawTextureEx(logoGO,posGameOver,0.0f,10.0f,WHITE);
                mostrarTemporizador();
                if (CheckCollisionPointRec(mouse, exit) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    SeekMusicStream(gameOverS, 0.0f);
                    SeekMusicStream(soundtrack, 0.0f);
                    SeekMusicStream(actionS, 0.0f);
                    SeekMusicStream(engine, 0.0f);
                    SeekMusicStream(records, 0.0f);
                    pantalla = 4;
                }
                if(CheckCollisionPointRec(mouse,reload) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    SeekMusicStream(gameOverS, 0.0f);
                    SeekMusicStream(actionS, 0.0f);
                    SeekMusicStream(engine, 0.0f);
                    pantalla = 1;
                    reiniciarPartida();
                    reiniciarMonedas();
                }
                break;
            }
        EndDrawing();
    }
    descargarFondo();
    descargarAvion();
    descargarPajarracos();
    descargarMonedas();
    UnloadTexture(btnPlay);
    UnloadTexture(btnOptions);
    UnloadTexture(btnExit);
    UnloadTexture(btnReload);
    UnloadTexture(btnexit);
    UnloadTexture(logoGO);
    UnloadTexture(btnPodium);
    UnloadMusicStream(soundtrack);
    UnloadMusicStream(engine);
    UnloadMusicStream(actionS);
    UnloadMusicStream(records);
    CloseAudioDevice();
    CloseWindow();
}
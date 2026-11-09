#include "raylib.h"
#include "../../class/class.h"

// Declaración de función externa (si está en otro módulo)
void ShowLogo(bool visible);
int pantalla = 0, cerrado = 0; // 0: menu, 1: juego, 2: tienda
Music soundtrack;
Rectangle menuGameOver;
Vector2 posGameOver;

void ejecutarInterfaz(void) {
    InitWindow(800, 600, "Main Menu"); // Medidas de la ventana
    InitAudioDevice();
    SetExitKey(KEY_NULL); // Evita que al presionar Esc se salga
    SetTargetFPS(60);     // FPS

    //inicializa modulos del juego
    iniciarFondo();
    iniciarAvion();
    iniciarPajarracos();
    iniciarRegistro_podio();

    float bgSpeed = 50.0f; 
    
    // Texturas de los botones
    Texture2D btnPlay = LoadTexture("assets/sprites/buttons/btnPlay.png");
    Texture2D btnOptions = LoadTexture("assets/sprites/buttons/btnShop.png");
    Texture2D btnExit = LoadTexture("assets/sprites/buttons/btnExit.png");
    Texture2D btnReload = LoadTexture("assets/sprites/buttons/reload.png");
    Texture2D btnexit = LoadTexture("assets/sprites/buttons/exit.png");
    Texture2D logoGO = LoadTexture("assets/sprites/background/GAMEOVER.png");
    Texture2D btnPod = LoadTexture("assets/sprites/buttons/podium.png");

    // Coordenadas de dibujo de los botones
    Rectangle rPlay   = { 300, 200, 200, 170 };
    Rectangle rOption = { 300, 270, 200, 170 };
    Rectangle rExit   = { 300, 340, 200, 170 };
    Rectangle podio = {300,410,200,170};
    Rectangle reload = {200,300,200,200};
    Rectangle exit = {400,300,200,200};

    // Coordenadas de presión de los botones
    Rectangle cPlay   = { 300, 260, 200, 50 };
    Rectangle cOption = { 300, 330, 200, 50 };
    Rectangle cExit   = { 300, 400, 200, 50 };

    // En C, las variables estáticas se inicializan de forma limpia
    soundtrack = LoadMusicStream("assets/audio/soundtrack.mp3");
    Music forest = LoadMusicStream("assets/audio/forest.mp3");
    Music engine = LoadMusicStream("assets/audio/planesound.wav");
    Music actionS = LoadMusicStream("assets/audio/soundtrack1.mp3");
    Music gameOverS = LoadMusicStream("assets/audio/gameover.mp3");
    PlayMusicStream(gameOverS);
    PlayMusicStream(actionS);
    PlayMusicStream(forest);
    PlayMusicStream(soundtrack);
    PlayMusicStream(engine);
    
    // Lógica de ventana 
    while (!WindowShouldClose() && cerrado == 0) {
        Vector2 mouse = GetMousePosition();
        UpdateMusicStream(soundtrack);
        //Logica (Separada del draw para evitar que se solapen)
        actualizarFondo(bgSpeed);
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
            else if(CheckCollisionPointRec(mouse, podio) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                pantalla = 5;
            }
            break;
        
        case 1:
            UpdateMusicStream(actionS);
            UpdateMusicStream(engine);
            actualizarAvion();
            actualizarPajarracos(bgSpeed);
            break;
        case 2: 
            if (IsKeyPressed(KEY_ESCAPE)) {
                pantalla = 0; 
                ShowLogo(true);
            }
            break;
        case 5:
            obtener_puntaje();
            break;
        }
        // draw
        BeginDrawing();
        ClearBackground(BLUE);
            switch (pantalla)
            {
            case 0:
                dibujarFondo();
                DrawTexturePro(btnPlay, (Rectangle){0, 0, (float)btnPlay.width, (float)btnPlay.height}, rPlay, (Vector2){0,0}, 0.0f, WHITE);
                DrawTexturePro(btnOptions, (Rectangle){0, 0, (float)btnOptions.width, (float)btnOptions.height}, rOption, (Vector2){0,0}, 0.0f, WHITE);
                DrawTexturePro(btnExit, (Rectangle){0, 0, (float)btnExit.width, (float)btnExit.height}, rExit, (Vector2){0,0}, 0.0f, WHITE);
                DrawTexturePro(btnPod, (Rectangle){0, 0, (float)btnPod.width, (float)btnPod.height}, podio, (Vector2){0,0}, 0.0f, WHITE);
                break;
            case 1:
                dibujarFondo();
                mostrarAvion();
                mostrarPajarracos();
                verificarColisionPajarraco();
                mostrarTemporizador();
                break;
            case 2:
                // DrawShop(mouse);
                break;
            case 3:
                ClearBackground(BLUE);
                posGameOver = (Vector2){115,15};
                //Aqui entra el gameOver
                menuGameOver = (Rectangle){100,100,600,400};
                DrawRectangleRec(menuGameOver,Fade(GREEN,.5));
                DrawRectangleLinesEx(menuGameOver,10,BROWN);
                DrawTexturePro(btnReload, (Rectangle){0, 0, (float)btnReload.width, (float)btnReload.height}, reload, (Vector2){0,0}, 0.0f, WHITE);
                DrawTexturePro(btnexit, (Rectangle){0, 0, (float)btnexit.width, (float)btnexit.height}, exit, (Vector2){0,0}, 0.0f, WHITE);
                DrawTextureEx(logoGO,posGameOver,0.0f,10.0f,WHITE);
                mostrarTemporizador();
                //Revisa si se presiono el boton de salir
                if (CheckCollisionPointRec(mouse, exit) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    pantalla = 4;
                }
                //Revisa si se presiono el boton de reiniciar
                if(CheckCollisionPointRec(mouse,reload) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    SeekMusicStream(actionS, 0.0f); // Mueve el cursor de reproducción al segundo 0.0
                    pantalla = 1;
                    reiniciarPartida();
                }
                break;
            case 4:
                registrar_puntaje();
                break;

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
    liberar_registro_podio();
    UnloadMusicStream(soundtrack);
    UnloadMusicStream(forest);
    UnloadMusicStream(forest);
    UnloadMusicStream(actionS);
    CloseAudioDevice();
    CloseWindow();
}
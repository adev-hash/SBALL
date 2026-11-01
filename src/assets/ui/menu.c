#include "raylib.h"
#include "animaciones.h"
#include "fondo.h"
#include "menu.h"

void iniciar_interfaz(void) {
    InitWindow(800, 600, "Main Menu");
    InitAudioDevice();
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);
    inicializar_fondo();
    inicializar_animaciones();

    const float velocidad_fondo = 50.0f;
    int pantalla = 0;

    Texture2D btnPlay = LoadTexture("assets/sprites/buttons/btnPlay.png");
    Texture2D btnOptions = LoadTexture("assets/sprites/buttons/btnOptions.png");
    Texture2D btnExit = LoadTexture("assets/sprites/buttons/btnExit.png");

    Rectangle rPlay = {300, 200, 200, 170};
    Rectangle rOption = {300, 270, 200, 170};
    Rectangle rExit = {300, 340, 200, 170};

    Rectangle cPlay = {300, 260, 200, 50};
    Rectangle cOption = {300, 330, 200, 50};
    Rectangle cExit = {300, 400, 200, 50};

    Music musica_menu = LoadMusicStream("assets/audio/soundtrack.mp3");
    Music musica_partida = LoadMusicStream("assets/audio/forest.mp3");
    PlayMusicStream(musica_menu);

    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();

        if (pantalla == 0) {
            if (CheckCollisionPointRec(mouse, cPlay) &&
                IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                pantalla = 1;
                mostrar_logo(false);
                PauseMusicStream(musica_menu);
                PlayMusicStream(musica_partida);
            }

            if (CheckCollisionPointRec(mouse, cOption) &&
                IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                pantalla = 2;
                mostrar_logo(false);
            }

            if (CheckCollisionPointRec(mouse, cExit) &&
                IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                break;
            }
        } else if (IsKeyPressed(KEY_ESCAPE)) {
            if (pantalla == 1) {
                PauseMusicStream(musica_partida);
                ResumeMusicStream(musica_menu);
            }
            pantalla = 0;
            mostrar_logo(true);
        }

        if (pantalla == 1) {
            UpdateMusicStream(musica_partida);
            actualizar_animaciones(velocidad_fondo);
        } else {
            UpdateMusicStream(musica_menu);
        }

        actualizar_fondo(velocidad_fondo);
        BeginDrawing();
        ClearBackground(BLUE);
        dibujar_fondo();

        if (pantalla == 0) {
            DrawTexturePro(btnPlay,
                           (Rectangle){0, 0, (float)btnPlay.width, (float)btnPlay.height},
                           rPlay, (Vector2){0, 0}, 0.0f, WHITE);
            DrawTexturePro(btnOptions,
                           (Rectangle){0, 0, (float)btnOptions.width, (float)btnOptions.height},
                           rOption, (Vector2){0, 0}, 0.0f, WHITE);
            DrawTexturePro(btnExit,
                           (Rectangle){0, 0, (float)btnExit.width, (float)btnExit.height},
                           rExit, (Vector2){0, 0}, 0.0f, WHITE);
        } else if (pantalla == 1) {
            dibujar_animaciones();
        }

        EndDrawing();
    }

    liberar_fondo();
    liberar_animaciones();
    UnloadTexture(btnPlay);
    UnloadTexture(btnOptions);
    UnloadTexture(btnExit);
    UnloadMusicStream(musica_menu);
    UnloadMusicStream(musica_partida);
    CloseAudioDevice();
    CloseWindow();
}

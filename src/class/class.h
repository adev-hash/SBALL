#ifndef CLASS_H
#define CLASS_H

#include "raylib.h"

// Menú e interfazzz (menu.c)
void ejecutarInterfaz(void);

// tienda (shop.c)
void iniciarTienda(void);
void actualizarTienda(void);
void dibujarTienda(void);

// Escenario y fondo (bg.c)
void iniciarFondo(void);
void actualizarFondo(float speed);
void dibujarFondo(void);
void descargarFondo(void);
void ShowLogo(bool visible);

// Juego y entidades animadas (animations.c)
extern int gameOver;

// avion
void iniciarAvion(void);
void reiniciarPartida(void);
void actualizarAvion(void);
void mostrarAvion(void);
void descargarAvion(void);
void mostrarVida(int vida);
// pajarracos
void iniciarPajarracos(void);
void actualizarPajarracos(float speed);
void mostrarPajarracos(void);
bool verificarColisionPajarraco(void);
void descargarPajarracos(void);

// monedas (por agregar xd)

// temporizador
void iniciarTemporizador(void);
void mostrarTemporizador(void);

void activarAlarma(void);

//static inline xq si no el compilador llora
static inline void showMenu(void) {
    ejecutarInterfaz();
}

#endif // CLASS_H
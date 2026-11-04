#ifndef CLASS_H
#define CLASS_H

#include "raylib.h"

void ejecutarInterfaz();
void iniciarFondo();
void actualizarFondo(float speed);
void dibujarFondo();
void descargarFondo();

void iniciarAves();
void ejecutarAnimaciones(float speed);
void descargarAves();

void iniciarAvion();
void mostrarAvion();
void descargarAvion();

//static inline pq si no no agarra no se pq
static inline void showMenu(void) {
    ejecutarInterfaz();
}

#endif // CLASS_H
#ifndef FONDO_H
#define FONDO_H

#include <stdbool.h>

void inicializar_fondo(void);
void actualizar_fondo(float velocidad);
void dibujar_fondo(void);
void liberar_fondo(void);
void mostrar_logo(bool visible);

#endif

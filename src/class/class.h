#ifndef CLASS_H
#define CLASS_H

#include "raylib.h"

void ejecutarInterfaz(void);

void iniciarMonedas(void);
void actualizarMonedas(float speed);
void mostrarMonedas(void);
void descargarMonedas(void);
void reiniciarMonedas(void);
void cargarMonedas(void);
void guardarProgreso(void);
void guardarSkin(void);
void cargarSkins(void);


void iniciarTienda(void);
void actualizarTienda(void);
void dibujarTienda(void);
void descargarTienda(void); 

void iniciarRegistro(void);
void registrarPuntaje(void);
void liberarRegistro(void);
void obtenerPuntaje(void);
double obtenerTiempoFinal(void);
void iniciarFondo(void);
void actualizarFondo(float speed);
void dibujarFondo(void);
void descargarFondo(void);
void ShowLogo(bool visible);

extern int gameOver;
extern double tiempo;
extern int pantalla;
extern int monedasGlobales;
extern int skinSeleccionadaID;
extern bool skinComprada[];

extern void actualizarSkinAvion(int nuevoSkinID);

void iniciarAvion(void);
void reiniciarPartida(void);
void actualizarAvion(void);
void mostrarAvion(void);
void descargarAvion(void);
void mostrarVida(int vida);

void iniciarPajarracos(void);
void actualizarPajarracos(float speed);
void mostrarPajarracos(void);
bool verificarColisionPajarraco(void);
void descargarPajarracos(void);

void iniciarTemporizador(void);
void mostrarTemporizador(void);
void activarAlarma(float speed);

static inline void showMenu(void) {
    ejecutarInterfaz();
};

#endif 

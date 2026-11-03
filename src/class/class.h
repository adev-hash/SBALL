#ifndef CLASS_H
#define CLASS_H

#include "raylib.h"

void executeInterface();
void InitBackGround();
void UpdateBackGround(float speed);
void DrawingBackGround();
void UnloadBackGround();

void InitBirds();
void showBirds(float speed);
void UnloadBirds();

void InitPlane();
void ShowPlane();
void UnloadPlane();


inline void showMenu() {
    executeInterface();
}
#endif
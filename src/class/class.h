#ifndef CLASS_H
#define CLASS_H

#include "raylib.h"

void executeInterface();
void InitBackGround();
void UpdateBackGround(float speed);
void DrawingBackGround();
void UnloadBackGround();

void InitAnimations();
void executeAnimations(float speed);
void UnloadAnimations();


inline void showMenu() {
    executeInterface();
}
#endif
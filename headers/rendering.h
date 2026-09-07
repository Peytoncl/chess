#ifndef RENDERING_H
#define RENDERING_H

#include <GL/glut.h>
#include <stdio.h>
#include <windows.h>

#include "../headers/engine.h"
#include "../headers/image.h"

typedef struct RGB { int r; int g; int b; } RGB;

extern RGB darkRGB;
extern RGB lightRGB;

extern int windowX;
extern int windowY;

extern int tileSizeX;
extern int tileSizeY;

extern GLuint textures[12];

extern int gameUpdate;

void Update();
void Display();
void Initialize();

#endif
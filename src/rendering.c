// headers //

#include "../headers/rendering.h"
#include <stdio.h>

// variables //

int windowX;
int windowY;

int tileSizeX;
int tileSizeY;

// functions //

void Display() //runs every frame
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw board //

    // light tiles

    glColor3ub(lightRGB.r, lightRGB.g, lightRGB.b);

    glBegin(GL_QUADS);

    for (int y = 0; y <= 7; y++)
    {
        for (int x = 0; x <= 3; x++)
        {
            int cX1 = tileSizeX * x;
            int cY1 = tileSizeY * y;

            int cX2 = tileSizeX * x + tileSizeX;
            int cY2 = tileSizeY * y + tileSizeY;

            glVertex2i(cX1, cY1);
            glVertex2i(cX1, cY2);
            glVertex2i(cX2, cY2);
            glVertex2i(cX2, cY1);
        }
    } 

    glEnd();

    glutSwapBuffers();

}

void Update()
{
    glutPostRedisplay();
}

void Initialize() //runs at startup
{
    
}

void Resize(int newX, int newY) //runs when the window is resized
{
    windowX = newX;
    windowY = newY;

    tileSizeX = windowX / 8;
    tileSizeY = windowY / 8;

    glutPostRedisplay();
}

// main //

int main(int argc, char *argv[])
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("chess.exe");

    glutDisplayFunc(Display);
    glutReshapeFunc(Resize);

    Resize(500, 500);
    Initialize();
    
    glutIdleFunc(Update);

    glutMainLoop();
}
// headers //

#include "../headers/rendering.h"
#include <stdio.h>

// variables //

int windowX = 800;
int windowY = 800;

int tileSizeX;
int tileSizeY;

// functions //

void Display() //runs every frame
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw board //

    glBegin(GL_QUADS);

    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            // determine if tile is dark or light (if even then its light and if odd then its dark)

            if ((x + y) % 2 == 0) glColor3ub(lightRGB.r, lightRGB.g, lightRGB.b);
            else glColor3ub(darkRGB.r, darkRGB.g, darkRGB.b);

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
    tileSizeX = windowX / 8;
    tileSizeY = windowY / 8;
}

void Resize(int newX, int newY) //runs when the window is resized
{
    windowX = newX;
    windowY = newY;

    tileSizeX = windowX / 8;
    tileSizeY = windowY / 8;

    gluOrtho2D(0, newX, newY, 0);

    glutPostRedisplay();
}

// main //

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowX, windowY);
    glutCreateWindow("chess.exe");

    glClearColor(1, 1, 1, 1);

    gluOrtho2D(0, windowX, windowY, 0);

    glutDisplayFunc(Display);
    glutIdleFunc(Update);

    //glutReshapeFunc(Resize);

    Initialize();

    glutMainLoop();

    return 0;
}
// headers //

#include "../headers/rendering.h"

// variables //

int windowX;
int windowY;

int tileSizeX;
int tileSizeY;

// functions //

void Update() //runs every frame
{
    glClear(GL_COLOR_BUFFER_BIT);

    
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
}

// main //

int main(int argc, char *argv[])
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("chess.exe");
    glutDisplayFunc(Update);

    glutReshapeFunc(Resize);

    Resize(500, 500);
    Initialize();
    
    glutMainLoop();
}
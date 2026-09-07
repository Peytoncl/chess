// headers //

#include "../headers/rendering.h"

// variables //

RGB darkRGB = (RGB){98, 65, 48};
RGB lightRGB = (RGB){225, 215, 180};

int windowX = 800;
int windowY = 800;

int tileSizeX;
int tileSizeY;

GLuint textures[11];

int gameUpdate = 0;

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

    // draw pieces //

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor3ub(255, 255, 255);

    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            // determine if tile is dark or light (if even then its light and if odd then its dark)

            enum PIECES piece = check_square(x + (8 * y)); // find the enum of the piece

            if (piece != -1) // if piece is not empty
            {
                int cX1 = tileSizeX * x;
                int cY1 = tileSizeY * y;
                int cX2 = tileSizeX * x + tileSizeX;
                int cY2 = tileSizeY * y + tileSizeY;

                glBindTexture(GL_TEXTURE_2D, textures[piece]);
                glBegin(GL_QUADS);

                glTexCoord2i(0, 0); glVertex2i(cX1, cY1);
                glTexCoord2i(1, 0); glVertex2i(cX2, cY1);
                glTexCoord2i(1, 1); glVertex2i(cX2, cY2);
                glTexCoord2i(0, 1); glVertex2i(cX1, cY2);

                glEnd();
            }

        }
    } 

    gameUpdate = 0;

    printf("Game Updated\n", gameUpdate);

    glutSwapBuffers();

}

void Update()
{
    if (gameUpdate > 0) glutPostRedisplay();
}

void Initialize() // runs at startup
{
    // adjust tile size //

    tileSizeX = windowX / 8;
    tileSizeY = windowY / 8;

    // load sprites //

    textures[WP_PIECE] = load_texture("sprites/WP.png");
    textures[WN_PIECE] = load_texture("sprites/WN.png");
    textures[WB_PIECE] = load_texture("sprites/WB.png");
    textures[WR_PIECE] = load_texture("sprites/WR.png");
    textures[WQ_PIECE] = load_texture("sprites/WQ.png");
    textures[WK_PIECE] = load_texture("sprites/WK.png");

    textures[BP_PIECE] = load_texture("sprites/BP.png");
    textures[BN_PIECE] = load_texture("sprites/BN.png");
    textures[BB_PIECE] = load_texture("sprites/BB.png");
    textures[BR_PIECE] = load_texture("sprites/BR.png");
    textures[BQ_PIECE] = load_texture("sprites/BQ.png");
    textures[BK_PIECE] = load_texture("sprites/BK.png");

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
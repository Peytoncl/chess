// headers //

#include "../headers/rendering.h"

// variables //

RGB darkRGB = (RGB){98, 65, 48};
RGB lightRGB = (RGB){225, 215, 180};

int windowX = 800;
int windowY = 800;

int tileSizeX;
int tileSizeY;

GLuint textures[12];

int hoveringPiece = -1;
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

    glColor3f(1, 1, 1);

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

                glTexCoord2f(0.0f, 0.0f); glVertex2i(cX1, cY1);
                glTexCoord2f(1.0f, 0.0f); glVertex2i(cX2, cY1);
                glTexCoord2f(1.0f, 1.0f); glVertex2i(cX2, cY2);
                glTexCoord2f(0.0f, 1.0f); glVertex2i(cX1, cY2);

                glEnd();
            }

        }
    } 

    glDisable(GL_TEXTURE_2D);

    if (check_square(hoveringPiece) != -1)
    {
        int y = (hoveringPiece / 8);
        int x = (hoveringPiece % 8);

        int cX1 = tileSizeX * x;
        int cY1 = tileSizeY * y;
        int cX2 = tileSizeX * x + tileSizeX;
        int cY2 = tileSizeY * y + tileSizeY;

        glColor4f(0.2f, 0.2f, 0.2f, 0.2f);

        glBegin(GL_QUADS);

        glVertex2i(cX1, cY1);
        glVertex2i(cX1, cY2);
        glVertex2i(cX2, cY2);
        glVertex2i(cX2, cY1);

        glEnd();
    }

    gameUpdate = 0;

    //printf("Redisplay\n", gameUpdate);

    glutSwapBuffers();

}

void Update()
{
    if (gameUpdate > 0) glutPostRedisplay();
}

void Initialize() // runs at startup
{
    // graphics setup

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // adjust tile size //

    tileSizeX = windowX / 8;
    tileSizeY = windowY / 8;

    // load sprites //

    textures[WP_PIECE] = load_texture("sprites\\wp.png");
    textures[WN_PIECE] = load_texture("sprites\\wn.png");
    textures[WB_PIECE] = load_texture("sprites\\wb.png");
    textures[WR_PIECE] = load_texture("sprites\\wr.png");
    textures[WQ_PIECE] = load_texture("sprites\\wq.png");
    textures[WK_PIECE] = load_texture("sprites\\wk.png");

    textures[BP_PIECE] = load_texture("sprites\\bp.png");
    textures[BN_PIECE] = load_texture("sprites\\bn.png");
    textures[BB_PIECE] = load_texture("sprites\\bb.png");
    textures[BR_PIECE] = load_texture("sprites\\br.png");
    textures[BQ_PIECE] = load_texture("sprites\\bq.png");
    textures[BK_PIECE] = load_texture("sprites\\bk.png");

}

void Resize(int newX, int newY) //runs when the window is resized
{


    windowX = newX;
    windowY = newY;

    tileSizeX = windowX / 8;
    tileSizeY = windowY / 8;

    //gluOrtho2D(0, windowX, windowY, 0);
}

void Mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        //move_piece(12, 28);
        gameUpdate = 1;
    }
}

void MouseMove(int x, int y)
{
    // round positions to the nearest 8 multiple

    int roundedX = (x / tileSizeX) * tileSizeX;
    int roundedY = (y / tileSizeY) * tileSizeY;

    int pieceX = roundedX / tileSizeX;
    int pieceY = roundedY / tileSizeY;

    int newHoveringPiece = pieceX + (8 * pieceY);

    if (newHoveringPiece != hoveringPiece)
    {
        hoveringPiece = newHoveringPiece;
        gameUpdate = 1;
    }
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

    Initialize();

    glutDisplayFunc(Display);
    glutIdleFunc(Update);
    glutMouseFunc(Mouse);
    glutPassiveMotionFunc(MouseMove);
    glutReshapeFunc(Resize);

    glutMainLoop();

    return 0;
}
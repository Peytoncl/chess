#include <GL/glut.h>

typedef struct RGB { int r; int g; int b; } RGB;

RGB darkRGB = (RGB){98, 65, 48};
RGB lightRGB = (RGB){225, 215, 180};

extern int windowX;
extern int windowY;

extern int tileSizeX;
extern int tileSizeY;

void Update();
void Display();
void Initialize();
#define STB_IMAGE_IMPLEMENTATION
#include "../headers/STB/stb_image.h"

#include "../headers/image.h"

GLuint load_texture(const char* filename)
{
    int width, height, channels;
    unsigned char* data = stbi_load(filename, &width, &height, &channels, STBI_rgb_alpha);

    if (!data) 
    {
        printf("could not read data of %s\n", filename);

        return 0;
    }

    GLuint textureId;
    glGenTextures(1, &textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
   
    stbi_image_free(data);
    
    return textureId;
}
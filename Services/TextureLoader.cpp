#include "Headers/TextureLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb/stb_image.h"
#include <GL/glew.h>

void loadImage(const char* imageFilePath) {
    int width, height, bpp;
    unsigned char* imgData = stbi_load(imageFilePath, &width, &height, &bpp, 4);

    glTexImage2D(GL_TEXTURE_2D,
        0,                  //level
        GL_RGBA,            //internal format
        width,              //width
        height,             //height
        0,                  //border
        GL_RGBA,            //data format
        GL_UNSIGNED_BYTE,   //data type
        imgData);           //data
    stbi_image_free(imgData);
    stbi_set_flip_vertically_on_load(true);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
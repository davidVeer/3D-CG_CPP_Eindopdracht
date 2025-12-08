#include "Headers/Texture.h"


#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb/stb_image.h"

Texture::Texture(const std::string & fileName)
{
    int width, height, bpp;

    stbi_set_flip_vertically_on_load(true);
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    unsigned char* imgData = stbi_load(fileName.c_str(), &width, &height, &bpp, 4);
    
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
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, id);
}

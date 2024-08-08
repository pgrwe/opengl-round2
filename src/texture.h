#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include "stb_image.h"
#include <iostream>

class Texture
{
    public:  
        GLuint ID;
        Texture(const char* data);
        void bind();
        void unbind();
        void activate();
    private:
        void setDefaultWrapAndFilter();
};


#endif
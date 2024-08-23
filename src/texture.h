#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include "stb_image.h"
#include <iostream>

class Texture
{
    public:  
        GLuint ID;
        std::string type;
        std::string path;
        Texture(const char* data);
        Texture(const char* path, const std::string& directory);

        void bind();
        void unbind();
        void activate();
    private:
        void setDefaultWrapAndFilter();
};


#endif
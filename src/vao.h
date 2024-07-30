#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>

class VAO {
    public:
        GLuint ID;
        // Generates VAO 
        VAO(); 
        
        void linkVBO(); // vertex attribute stuff
        void bind(); 
        void unbind();
        void dispose();
};

#endif
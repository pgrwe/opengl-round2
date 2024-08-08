#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>
#include "vbo.h"

// Vertex Array Object: Stores the state of vertex attribute (normals, uv coords, color, etc) configurations
class VAO {
    public:
        GLuint ID;
        // Generates VAO with ID
        VAO(); 
        
        // Links a VBO to the VAO - generating and enabling a vertex attribute pointer
        void linkAttrib(VBO& VBO, GLuint layout, unsigned int size, unsigned int stride, void* pointer); // vertex attribute stuff

        void bind(); 
        void unbind();
        void dispose();
};

#endif
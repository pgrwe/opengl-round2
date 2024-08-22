#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>

// Vertex Buffer Object: Stores a large number of vertices in GPU's memory 
class VBO 
{ 
    public:
        GLuint ID;
        // Generates VBO with ID
        VBO();
        // Generates VBO with ID and sets buffer data
        VBO(GLsizeiptr size, GLfloat* vertices);

        // Sets VBO buffer data
        void setBufferData(GLsizeiptr size, GLfloat* vertices);
        // Make this VBO current target
        void bind();
        // Remove this VBO current target (assigns current target to 0)
        void unbind();
        // Delete the VBO
        void dispose();
};

#endif
#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>

// Vertex Buffer Object: Stores a large number of vertices in GPU's memory 
class VBO 
{ 
    public:
        GLuint ID;
        VBO();
        VBO(GLsizeiptr size, GLfloat* vertices);

        void setBufferData(GLsizeiptr size, GLfloat* vertices);
        void bind();
        void unbind();
        void dispose();
};

#endif
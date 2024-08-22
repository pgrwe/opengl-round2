#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>

// Element Buffer Object: Stores indices of what vertices to draw
class EBO
{
    public:
        GLuint ID;
        // Generates EBO with ID
        EBO();
        // Generates EBO with ID and sets buffer data
        EBO(GLsizeiptr size, GLuint* indices);

        // Sets EBO buffer data
        void setBufferData(GLsizeiptr size, GLuint* indices);
        // Makes bound EBO current target 
        void bind();
        // Removes referenced EBO as target
        void unbind();
        // Deletes this buffer
        void dispose(); 
};


#endif 
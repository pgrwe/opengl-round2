#include "vao.h"

VAO::VAO()
{
    glGenVertexArrays(1, &ID);
}

void VAO::linkAttrib(VBO& VBO, GLuint layout, unsigned int size, unsigned int stride, void* pointer)
{
    VBO.bind();
    /* Parameter Breakdown
    1st: specifices vertex attribute to configure (currently only position)
    2nd: size of vertex attribute, vec3 so 3 values
    3rd: data type of the attribute
    4th: decide to normalize based on data type
    5th: stride - distance between contiguous vertex attributes
    6th: offset - where the start of the attribute data is located in the buffer 
    vertex attribute 0 is now associated with the vertex data from the currently bound VBO
    */
    glVertexAttribPointer(layout, size, GL_FLOAT, GL_FALSE, stride, pointer);
    glEnableVertexAttribArray(layout);
    VBO.unbind();
}

void VAO::bind()
{
    glBindVertexArray(ID);
    
}

void VAO::unbind()
{
    glBindVertexArray(0);
}

void VAO::dispose()
{
    glDeleteVertexArrays(1, &ID);
}
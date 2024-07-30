#ifndef SHADERS_H
#define SHADERS_H

#include <glad/glad.h>
#include <cerrno>
#include <string>

std::string get_file_contents(const char * filename);

class Shader
{
    public:
        GLuint ID;
        Shader(const char* vFile, const char* fFile);
        void activate();
        void dispose();

    private:
        int debugAllShaders(GLuint& vertexShader, GLuint& fragmentShader);
        int debugFragmentShader(GLuint& fragmentShader);
        int debugVertexShader(GLuint& vertexShader);
        int debugShaderProgram(); // uses ID of current Shader object
        // May be public later?
        void loadFragmentShader(const char* fFile);
        void loadVertexShader(const char* vFile);
};

#endif
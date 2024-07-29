#ifndef SHADERS_H
#define SHADERS_H

#include <glad/glad.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char * filename);

class Shader
{
    public:
        GLuint shaderProgramID;
        Shader(const char *vertexFile, const char *fragmentFile);

        // void loadFragmentShader();
        // void loadVertexShader();
        void activate();
        void dispose();

    private:
        int debug(GLuint& vertexShader, GLuint& fragmentShader);
};

#endif
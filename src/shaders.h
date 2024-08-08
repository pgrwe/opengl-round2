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
        // Wrapper for glUseProgram
        void activate();
        // Wrapper for glDeleteProgram
        void dispose();

        // Utility uniform functions
        // Set 1 bool uniform
        void set1Bool(const std::string &name, bool value) const;  
        // Set 1 int uniform
        void set1Int(const std::string &name, int value) const;   
        // Set 1 float uniform
        void set1Float(const std::string &name, float value) const;

    private:
        int debugAllShaders(GLuint& vertexShader, GLuint& fragmentShader);
        int debugFragmentShader(GLuint& fragmentShader);
        int debugVertexShader(GLuint& vertexShader);
        int debugShaderProgram(); // uses ID of current Shader object
        // May be public later?
        GLuint loadFragmentShader(const char* fFile);
        GLuint loadVertexShader(const char* vFile);
};

#endif

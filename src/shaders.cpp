#include "shaders.h"
#include <fstream>
#include <ios>
#include <string>

// Reads a text file and outputs a string with everything in the text file
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char* vFile, const char* fFile)
{
    std::string vertexShaderCode = get_file_contents(vFile);
    std::string fragmentShaderCode = get_file_contents(fFile);

    // Debug
    // std::cout << vertexShaderCode << std::endl;
    // std::cout << fragmentShaderCode << std::endl;

    // Convert std::string to c style character arrays
    const char* vertexSource = vertexShaderCode.c_str();
    const char* fragmentSource = fragmentShaderCode.c_str();

    // Shaders
    GLuint vertexShader, fragmentShader;
    shaderProgramID = glCreateProgram(); // links shaders to be used when issuing render calls

    // Create the vertex shader    
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Reference to the source code for the vertex shader
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    // Compile the vertex shader
    glCompileShader(vertexShader);

    // Create the fragment shader    
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Reference to the source code for the fragment shader
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    // Compile the fragment shader
    glCompileShader(fragmentShader);


    // Attach vertex and fragment shaders to the shader program
    glAttachShader(shaderProgramID, vertexShader);
    glAttachShader(shaderProgramID, fragmentShader);
    // Link the compiled shaders
    glLinkProgram(shaderProgramID);

    debug(vertexShader,fragmentShader);

    // Since compilation and linking is complete, delete shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::activate()
{
    glUseProgram(shaderProgramID);
}

void Shader::dispose()
{
    glDeleteProgram(shaderProgramID);
}

int Shader::debug(GLuint& vertexShader, GLuint& fragmentShader)
{
    // Shader Debug
    int fragSuccess, vertSuccess, shdrpgrmSuccess;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertSuccess);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragSuccess);
    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &shdrpgrmSuccess);

    if (!fragSuccess)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        return -1;
    }

    if (!vertSuccess)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return -1;
    }

    if (!shdrpgrmSuccess)
    {
        glGetProgramInfoLog(shaderProgramID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return -1;
    }
    return 0;
}

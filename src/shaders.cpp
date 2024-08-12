#include "shaders.h"

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
    throw std::runtime_error("Failed to open file: " + std::string(filename));
}

Shader::Shader(const char* vFile, const char* fFile)
{
    // Shaders
    GLuint vertexShader, fragmentShader;
    ID = glCreateProgram(); // links shaders to be used when issuing render calls

    fragmentShader = loadFragmentShader(fFile);
    vertexShader = loadVertexShader(vFile);

    // Link the compiled shaders
    glLinkProgram(ID);

    debugAllShaders(vertexShader, fragmentShader);

    // Since compilation and linking is complete, delete shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

GLuint Shader::loadFragmentShader(const char* fFile)
{
    std::string fragmentShaderCode = get_file_contents(fFile);
    const char* fragmentSource = fragmentShaderCode.c_str();

    // Create the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Reference to the source code for the fragment shader
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    // Compile the fragment shader
    glCompileShader(fragmentShader);
    glAttachShader(ID, fragmentShader);
    return fragmentShader;
}

GLuint Shader::loadVertexShader(const char* vFile)
{
    std::string vertexShaderCode = get_file_contents(vFile);
    const char* vertexSource = vertexShaderCode.c_str();

    // Create the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Reference to the source code for the fragment shader
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    // Compile the fragment shader
    glCompileShader(vertexShader);
    glAttachShader(ID, vertexShader);
    return vertexShader;
}

// Same as use() in learnopengl
void Shader::activate()
{
    glUseProgram(ID);
}

void Shader::dispose()
{
    glDeleteProgram(ID);
}

// Uniform Functions

void Shader::set1Bool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::set1Int(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::set1Float(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMat4fv(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}


// Debug Functions

int Shader::debugAllShaders(GLuint& vertexShader, GLuint& fragmentShader)
{
    debugVertexShader(vertexShader);
    debugFragmentShader(fragmentShader);
    debugShaderProgram();
    return 0;
}

int Shader::debugFragmentShader(GLuint& fragmentShader)
{
    int fragSuccess;
    char infoLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragSuccess);

    if (!fragSuccess)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        return -1;
    }

    return 0;
}

int Shader::debugVertexShader(GLuint& vertexShader)
{
    int vertSuccess;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertSuccess);

    if (!vertSuccess)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        return -1;
    }

    return 0;
}

int Shader::debugShaderProgram()
{
    int shdrpgrmSuccess;
    char infoLog[512];
    glGetProgramiv(ID, GL_LINK_STATUS, &shdrpgrmSuccess);

    if (!shdrpgrmSuccess)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return -1;
    }

    return 0;
}

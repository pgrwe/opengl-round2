#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <numeric>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);  
void processInput(GLFWwindow *window);

// Move to .vert file
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.5f, 0.7f);\n"
    "}\0";


int main() 
{
    float triangleVertices[] = {
    0.5f,  0.5f, 0.0f,  // top right
    0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
    };  

    unsigned int indices[] = {
        0, 1, 3, // first tri
        1, 2, 3 // second tri
    };

    /* Buffers:
    A buffer in OpenGL is, at its core, an object that manages a certain piece of GPU memory and nothing more. 
    We give meaning to a buffer when binding it to a specific buffer target. 
    A buffer is only a vertex array buffer when we bind it to GL_ARRAY_BUFFER, but we could just as easily bind it to GL_ELEMENT_ARRAY_BUFFER. 
    OpenGL internally stores a reference to the buffer per target and, based on the target, processes the buffer differently. 
    */ 
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    unsigned int width = 800;
    unsigned int height = 600;

    GLFWwindow * window = glfwCreateWindow(width, height, "opengl-round2", NULL, NULL);
    if (window == NULL) 
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLAD to use OpenGL functions
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

    // Shaders
    GLuint vertexShader, fragmentShader;
    GLuint shaderProgram = glCreateProgram(); // links shaders to be used when issuing render calls

    // Create the vertex shader    
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Reference to the source code for the shader
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // Compile the shader
    glCompileShader(vertexShader);

    // Same idea applies to fragment shader    
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Attach vertex and fragment shaders to the shader program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // Link the compiled shaders
    glLinkProgram(shaderProgram);

    // Since compilation and linking is complete, delete shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Shader compilation debug stuff
    int fragSuccess, vertSuccess, shdrpgrmSuccess;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertSuccess);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragSuccess);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &shdrpgrmSuccess);

    if (!fragSuccess)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    if (!vertSuccess)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    if (!shdrpgrmSuccess)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    
    // OpenGL Objects
    GLuint VBO; // Vertex Buffer Object: Stores a large number of vertices in GPU's memory 
    GLuint VAO; // Vertex Array Object: Stores the state of vertex attribute (normals, uv coords, color, etc) configurations
    GLuint EBO; // Element Buffer Object: Stores indices of what vertices to draw

    // Binding: making an object the current target for subsequent operations

    // Create VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create VBO
    glGenBuffers(1, &VBO); 
    glBindBuffer(GL_ARRAY_BUFFER, VBO); 
    // Copy triangleVertices data into currently bound buffer (VBO)
    // GL_STATIC_DRAW ensures the gpu will place the data from the bound buffer into memory that allows for faster reads (and no writes?)
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

    // Create EBO
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    /* Parameter Breakdown
    1st: specifices vertex attribute to configure (currently only position)
    2nd: size of vertex attribute, vec3 so 3 values
    3rd: data type of the attribute
    4th: decide to normalize based on data type
    5th: stride - distance between contiguous vertex attributes
    6th: offset - where the start of the attribute data is located in the buffer 
    vertex attribute 0 is now associated with the vertex data from the currently bound VBO
    */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // Enable the vertex attribute 
    glEnableVertexAttribArray(0);

    // Main Game Loop
    while (!glfwWindowShouldClose(window)) 
    {
        // Handle Input
        processInput(window);

        // Rendering Commands 
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // State setting function 
        glClear(GL_COLOR_BUFFER_BIT); // State using function

        // This can be before glClear (unsure if will cause undefined behavior)
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        // This needs to be after glClear for anything actually to be drawn
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // Swap Buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if(glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        std::cout << "WIREFRAME MODE" << std::endl;
    }

    if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        std::cout  << "FILL MODE" << std::endl;
    }    
}

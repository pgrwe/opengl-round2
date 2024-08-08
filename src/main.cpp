#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "shaders.h"
#include "texture.h"
#include "vbo.h"
#include "vao.h"
#include "ebo.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);  
void processInput(GLFWwindow* window, float& mixValue);

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

int main() 
{
    GLfloat rectVertices[] = {

    // Top right
    // Position               
    0.5f,  0.5f, 0.0f,  
    // Colors and alpha
    1.0f, 0.0f, 0.0f,  1.0f,
    // Texture Coords
    1.0f, 1.0f,

    // Bottom right
    // Position               
    0.5f, -0.5f, 0.0f,  
    // Colors and alpha
    0.0f, 1.0f, 0.0f,1.0f,
    // Texture Coords
    1.0f, 0.0f,

    // Bottom left
    // Position               
    -0.5f, -0.5f, 0.0f, 
    // Colors and alpha
    0.0f, 0.0f, 1.0f,1.0f,
    // Texture Coords
    0.0f, 0.0f,

    // Top left 
    // Position               
    -0.5f,  0.5f, 0.0f, 
    // Colors and alpha
    0.5f, 0.0f, 0.5f,1.0f,
    // Texture Coords
    0.0f, 1.0f,
    };  

    // GLfloat rectVertices[] = {
    // // position            
    // 0.5f,  0.5f, 0.0f, 
    // 0.5f, -0.5f, 0.0f, 
    // -0.5f, -0.5f, 0.0f,
    // -0.5f,  0.5f, 0.0f,
    // };  
    

    GLfloat triforceVertices[] = {
    -0.5f, -0.5f, 0.0f, // bottom left
    0.0f, -0.5f, 0.0f, // bottom middle
    0.5f,  -0.5f, 0.0f,  // bottom right
    -0.25f,  0.0f, 0.0f,  // middle left
    0.25f,  0.0f, 0.0f,  // middle right
    0.0f, 0.5f, 0.0f, // top
    };

    unsigned int rectIndices[] = {
        0, 1, 3, // first tri
        1, 2, 3 // second tri
    };

    unsigned int triforceIndices[] = {
        0, 3, 1,
        1, 2, 4,
        4, 5, 3,  
    };

    // PROJECT SETUP START
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "opengl-round2", NULL, NULL);
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

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  
    // PROJECT SETUP END

    

    // Load in and create textures
    Texture texture1("resources/container.jpg");
    Texture texture2("resources/real.png");

    // Load in and compile shaders
    Shader shaderProgram("src/shaders/default.vert", "src/shaders/default.frag");

    /* Buffers:
    A buffer in OpenGL is, at its core, an object that manages a certain piece of GPU memory and nothing more. 
    We give meaning to a buffer when binding it to a specific buffer target. 
    A buffer is only a vertex array buffer when we bind it to GL_ARRAY_BUFFER, but we could just as easily bind it to GL_ELEMENT_ARRAY_BUFFER. 
    OpenGL internally stores a reference to the buffer per target and, based on the target, processes the buffer differently. 
    */ 
 
    // VBO vbo1(sizeof(rectVertices), rectVertices); 
    // EBO ebo1(sizeof(rectIndices), rectIndices); 
    VBO vbo1(sizeof(rectVertices), rectVertices); 
    EBO ebo1(sizeof(rectIndices), rectIndices); 
    VAO vao1; 
    vao1.bind();

    // Stride should always be = num values * size of values
    int stride = 9 * sizeof(float);
    // Vertex Attributes:
    // Position
    vao1.linkAttrib(vbo1, 0, 3, stride, (void*) 0);    
    // Color
    vao1.linkAttrib(vbo1, 1, 4, stride, (void*) (3 * sizeof(float)));   
    // Texture Coordinates
    vao1.linkAttrib(vbo1, 2, 2, stride, (void*) (7 * sizeof(float)));

    int elementCount = (sizeof(rectIndices)/sizeof(rectIndices[0]));

    float timeValue;    
    float mixValue = 0.2;
    float value;    

    // Main Game Loop
    while (!glfwWindowShouldClose(window)) 
    {

        // Handle Input
        // Is there a better way to handle input variable then by reference?
        processInput(window, mixValue);

        // Rendering Commands 
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // State setting function 
        glClear(GL_COLOR_BUFFER_BIT); // State using function

        // Shaders

        // timeValue = glfwGetTime();
        // value = (sin(timeValue) / 2.0f) + 0.5f;
        // int vertexColorLocation = glGetUniformLocation(shaderProgram.ID, "uniColor");
        // glUniform4f(vertexColorLocation, 0.2f, 0.2f, value, 1.0f);
        // shaderProgram.set1Float("shift", value);
        glActiveTexture(GL_TEXTURE0);
        texture1.bind();
        glActiveTexture(GL_TEXTURE1);
        texture2.bind();
        
        shaderProgram.activate();
        shaderProgram.set1Int("texture1", 0);
        shaderProgram.set1Int("texture2", 1);
        shaderProgram.set1Float("mixValue", mixValue);

        vao1.bind();
        ebo1.bind();
        glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, 0);

        // Swap Buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    vao1.dispose();    
    vbo1.dispose();    
    ebo1.dispose();    
    shaderProgram.dispose();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

void processInput(GLFWwindow* window, float& mixValue)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if(glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        // std::cout  << "WIREFRAME MODE" << std::endl;
    }

    if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        // std::cout  << "FILL MODE" << std::endl;
    }    
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        mixValue += 0.001f; // change this value accordingly (might be too slow or too fast based on system hardware)
        if(mixValue >= 1.0f)
            mixValue = 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        mixValue -= 0.001f; // change this value accordingly (might be too slow or too fast based on system hardware)
        if (mixValue <= 0.0f)
            mixValue = 0.0f;
    }
}

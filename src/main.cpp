#include <cmath>
#include <glad/glad.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <glm/trigonometric.hpp>
#include <iostream>

#include "shaders.h"
#include "texture.h"
#include "vbo.h"
#include "vao.h"
#include "ebo.h"


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Handle window resizing 
void framebuffer_size_callback(GLFWwindow* window, int width, int height);  
// Handle user inputs
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


    float testVertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        glm::vec3( 2.0f,  5.0f, -15.0f), 
        glm::vec3(-1.5f, -2.2f, -2.5f),  
        glm::vec3(-3.8f, -2.0f, -12.3f),  
        glm::vec3( 2.4f, -0.4f, -3.5f),  
        glm::vec3(-1.7f,  3.0f, -7.5f),  
        glm::vec3( 1.3f, -2.0f, -2.5f),  
        glm::vec3( 1.5f,  2.0f, -2.5f), 
        glm::vec3( 1.5f,  0.2f, -1.5f), 
        glm::vec3(-1.3f,  1.0f, -1.5f)  
    };


    GLfloat cubeVertices[] = {		// COLORs
    -0.5f,  0.5f, 0.5f,
    0.8f, 0.3f, 0.02f, 1.0f,// Upper left front
    1.0f, 1.0f,

    -0.5f,  0.5f,-0.5f,  
    0.8f, 0.3f, 0.02f, 1.0f, // Upper left back
    1.0f, 0.0f,

    0.5f,  0.5f,-0.5f,	
    0.8f, 0.3f, 0.02f, 1.0f, // Upper right back
    0.0f, 0.0f,

    0.5f,  0.5f, 0.5f,  
    0.8f, 0.3f, 0.02f, 1.0f, // Upper right front
    0.0f, 1.0f,

    -0.5f,  -0.5f, 0.5f,
    0.8f, 0.3f, 0.02f,  1.0f,// Lower left front
    1.0f, 1.0f,

    -0.5f,  -0.5f,-0.5f, 
    0.8f, 0.3f, 0.02f,1.0f, // Lower left back
    1.0f, 0.0f,

    0.5f,  -0.5f,-0.5f,
    0.8f, 0.3f, 0.02f, 1.0f, // Lower right back
    0.0f, 0.0f,

    0.5f,  -0.5f, 0.5f,
    0.8f, 0.3f, 0.02f, 1.0f, // Lower right front
    0.0f, 1.0f,
    };

    GLuint cubeIndices[] = {
        0, 3, 4,
        3, 7, 4,
        3, 2, 7,
        2, 7, 6,
        2, 1, 6,
        5, 1, 6,
        1, 0, 4,
        0, 4, 5,
        1, 2, 0,
        0, 2, 3,
        4, 5, 6,
        6, 7, 4
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
    Texture texture2("resources/borpa.jpg");

    // Load in and compile shaders
    Shader shaderProgram("src/shaders/default.vert", "src/shaders/default.frag");

    /* Buffers:
    A buffer in OpenGL is, at its core, an object that manages a certain piece of GPU memory and nothing more. 
    We give meaning to a buffer when binding it to a specific buffer target. 
    A buffer is only a vertex array buffer when we bind it to GL_ARRAY_BUFFER, but we could just as easily bind it to GL_ELEMENT_ARRAY_BUFFER. 
    OpenGL internally stores a reference to the buffer per target and, based on the target, processes the buffer differently. 
    */ 
 
    VBO vbo1(sizeof(testVertices), testVertices); 
    // EBO ebo1(sizeof(cubeIndices), cubeIndices); 
    VAO vao1; 
    vao1.bind();

    // Stride should always be = total values in vertex attributes * size of values
    int stride = 5 * sizeof(float);
    // Vertex Attributes:
    // Position
    vao1.linkAttrib(vbo1, 0, 3, stride, (void*) 0);    
    // Color
    // vao1.linkAttrib(vbo1, 1, 4, stride, (void*) (3 * sizeof(float)));   
    // Texture Coordinates
    vao1.linkAttrib(vbo1, 1, 2, stride, (void*) (3 * sizeof(float)));

    int elementCount = (sizeof(cubeVertices)/sizeof(cubeIndices[0]));

    float timeValue;    
    float mixValue = 0.2;

    glEnable(GL_DEPTH_TEST);  

    // Main Game Loop
    while (!glfwWindowShouldClose(window)) 
    {
        timeValue = glfwGetTime();

        // Transformation Matrices
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);


        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 
        projection = glm::perspective(glm::radians(45.0f), (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT, 0.1f, 100.0f);

        // Handle Input
        processInput(window, mixValue);

        // Rendering Commands 
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // State setting function 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // State using function

        // Textures
        glActiveTexture(GL_TEXTURE0);
        texture1.bind();
        glActiveTexture(GL_TEXTURE1);
        texture2.bind();
        
        // Uniforms
        shaderProgram.activate();
        shaderProgram.set1Int("texture1", 0);
        shaderProgram.set1Int("texture2", 1);
        shaderProgram.set1Float("mixValue", mixValue);

        shaderProgram.setMat4fv("view", view);
        shaderProgram.setMat4fv("projection", projection);

        // Binding
        vao1.bind();
        // ebo1.bind();
        // Draw Calls
        // glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, 0);
        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, timeValue * i / 4 + 2, glm::vec3(1.0f, 0.3f, 0.5f));
            shaderProgram.setMat4fv("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // Swap Buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    vao1.dispose();    
    vbo1.dispose();    
    // ebo1.dispose();    
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

    // For playing with the mixing of textures
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        mixValue += 0.01f; 
        if(mixValue >= 1.0f)
            mixValue = 1.0f;
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        mixValue -= 0.01f; 
        if (mixValue <= 0.0f)
            mixValue = 0.0f;
    }
}

#include "shaders.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "vbo.h"
#include "vao.h"
#include "ebo.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);  
void processInput(GLFWwindow* window);



int main() 
{
    GLfloat rectVertices[] = {
    0.5f,  0.5f, 0.0f,  // top right
    0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
    };  

    GLfloat triforceVertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f,  0.5f, 0.0f  
    };

    unsigned int indices[] = {
        0, 1, 3, // first tri
        1, 2, 3 // second tri
    };

    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    unsigned int width = 800;
    unsigned int height = 600;

    GLFWwindow* window = glfwCreateWindow(width, height, "opengl-round2", NULL, NULL);
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

    Shader shaderProgram("src/shaders/vertex.glsl", "src/shaders/fragment.glsl");

    /* Buffers:
    A buffer in OpenGL is, at its core, an object that manages a certain piece of GPU memory and nothing more. 
    We give meaning to a buffer when binding it to a specific buffer target. 
    A buffer is only a vertex array buffer when we bind it to GL_ARRAY_BUFFER, but we could just as easily bind it to GL_ELEMENT_ARRAY_BUFFER. 
    OpenGL internally stores a reference to the buffer per target and, based on the target, processes the buffer differently. 
    */ 
 
    // OpenGL Objects
    VBO vbo1(sizeof(rectVertices), rectVertices); 
    EBO ebo1(sizeof(indices), indices); 
    VAO vao1; 
    vao1.bind();
    vao1.linkVBO(vbo1, 0);

    // Main Game Loop
    while (!glfwWindowShouldClose(window)) 
    {
        // Handle Input
        processInput(window);

        // Rendering Commands 
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // State setting function 
        glClear(GL_COLOR_BUFFER_BIT); // State using function

        shaderProgram.activate();
        // This can be before glClear (unsure if will cause undefined behavior)
        vao1.bind();
        // This needs to be after glClear for anything actually to be drawn
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo1.ID);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glDrawArrays(GL_TRIANGLES, 0, 3);  

        // Swap Buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

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

void processInput(GLFWwindow* window)
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
}

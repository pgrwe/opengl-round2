#include <cmath>
#include <filesystem>
#include <glad/glad.h>
#include <glm.hpp>
#include <ext/vector_float3.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <trigonometric.hpp>
#include <iostream>

#include "data.h"
#include "camera.h"
#include "shaders.h"
#include "model.h"
#include "texture.h"
#include "vbo.h"
#include "vao.h"
#include "ebo.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = WINDOW_WIDTH / 2.0f;
float lastY = WINDOW_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

float mixValue = 0.2f;

int main()
{
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
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
    // PROJECT SETUP END

    float lastX = 400, lastY = 300;

    // Load in and create textures
    // Texture texture1("resources/container.jpg");
    // Texture texture2("resources/borpa.jpg");

    // Load in and compile shaders
    Shader shaderProgram("src/shaders/default.vert", "src/shaders/default.frag");

    Model modelData("resources/objects/backpack/backpack.obj");

    /* Buffers:
    A buffer in OpenGL is, at its core, an object that manages a certain piece of GPU memory and nothing more.
    We give meaning to a buffer when binding it to a specific buffer target.
    A buffer is only a vertex array buffer when we bind it to GL_ARRAY_BUFFER, but we could just as easily bind it to GL_ELEMENT_ARRAY_BUFFER.
    OpenGL internally stores a reference to the buffer per target and, based on the target, processes the buffer differently.
    */

    // VBO vbo1(sizeof(testVertices), testVertices);
    // // EBO ebo1(sizeof(cubeIndices), cubeIndices);
    // VAO vao1;
    // vao1.bind();

    // // Stride should always be = total values in vertex attributes * size of values
    // int stride = 5 * sizeof(float);
    // // Vertex Attributes:
    // // Position
    // vao1.linkAttrib(vbo1, 0, 3, stride, (void*) 0);
    // // Color
    // // vao1.linkAttrib(vbo1, 1, 4, stride, (void*) (3 * sizeof(float)));
    // // Texture Coordinates
    // vao1.linkAttrib(vbo1, 1, 2, stride, (void*) (3 * sizeof(float)));

    // For using ebo
    // int elementCount = (sizeof(cubeVertices)/sizeof(cubeIndices[0]));

    deltaTime = 0.0f;

    float lastFrame = 0.0f;
    float currentFrame;

    // Z buffer
    glEnable(GL_DEPTH_TEST);
    // Main Game Loop
    while (!glfwWindowShouldClose(window))
    {
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Transformation Matrices
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();

        // Handle Input
        processInput(window);

        // Rendering Commands
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // State setting function
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // State using function

        // Render loaded models

        // Uniforms
        shaderProgram.activate();
        shaderProgram.setMat4fv("view", view);
        shaderProgram.setMat4fv("projection", projection);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        shaderProgram.setMat4fv("model", model);
        modelData.draw(shaderProgram);

        // Swap Buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    // vao1.dispose();
    // vbo1.dispose();
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

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void processInput(GLFWwindow* window)
{
    const float cameraSpeed = 2.5f * deltaTime;

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

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

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

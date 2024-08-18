#ifndef DATA_H
#define DATA_H

#include <glad/glad.h>
#include <glm.hpp>

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

#endif
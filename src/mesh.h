#include <glm.hpp>
#include <glad/glad.h>
#include <string>
#include <vector>
#include "shaders.h"
#include "texture.h"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};


class Mesh 
{
    public:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
        void draw(Shader &shader);

    private:
        VAO vao;
        VBO vbo;
        EBO ebo;
        void setupMesh();
};
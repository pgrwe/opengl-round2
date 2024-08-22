#include "mesh.h"
#include <cstddef>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    setupMesh();
}

void Mesh::setupMesh()
{
    vao.bind();
    vbo.bind();
    vbo.setBufferData(sizeof(Vertex) * vertices.size(), (GLfloat*) &vertices[0]);
    ebo.bind();
    ebo.setBufferData(sizeof(GLuint) * indices.size(), (GLuint*) &indices[0]);

    vao.linkAttrib(vbo, 0, 3, sizeof(Vertex), (void*) 0);
    vao.linkAttrib(vbo, 1, 3, sizeof(Vertex), (void*) offsetof(Vertex, Normal));
    vao.linkAttrib(vbo, 2, 2, sizeof(Vertex), (void*) offsetof(Vertex, TexCoords));

    vao.unbind();
}

void Mesh::draw(Shader &shader)
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    for(unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = textures[i].type;
        if(name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if(name == "texture_specular")
            number = std::to_string(specularNr++);

        shader.set1Int(("material." + name + number).c_str(), i);
        textures[i].bind();
    }

    vao.bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    vao.unbind();
}
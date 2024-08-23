#version 330 core
// vertex position variable aPos has the attribute position 0
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

// out vec4 vertexColor;
out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
 
void main()
{
   // vertexColor = aColor;
   texCoord = aTexCoord;
   gl_Position = projection * view * model * vec4(aPos, 1.0);
}

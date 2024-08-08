#version 330 core
// vertex position variable aPos has the attribute position 0
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;

// output color to fragment shader
out vec4 vertexColor;
out vec2 texCoord;
 
void main()
{
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
   vertexColor = aColor;
   texCoord = aTexCoord;
}

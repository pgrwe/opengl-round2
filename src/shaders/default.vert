#version 330 core
// vertex position variable aPos has the attribute position 0
layout (location = 0) in vec3 aPos;

// output color to fragment shader
out vec4 vertexColor;
 
void main()
{
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
   vertexColor = vec4(0.5, 0.6, 0.4, 1.0);
}

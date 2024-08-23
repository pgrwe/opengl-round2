#version 330 core
out vec4 FragColor;

// input from vertex shader
// in vec4 vertexColor; 
in vec2 texCoord;

uniform sampler2D texture_diffuse1;

void main()
{
   FragColor = texture(texture_diffuse1, texCoord);
}

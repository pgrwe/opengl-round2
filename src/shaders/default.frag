#version 330 core
out vec4 FragColor;

uniform vec4 uniColor;
// input from vertex shader
in vec4 vertexColor; 

void main()
{
   FragColor = uniColor;
}

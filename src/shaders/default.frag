#version 330 core
out vec4 FragColor;

// input from vertex shader
// in vec4 vertexColor; 
in vec2 texCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixValue;

void main()
{
   FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), mixValue);
}

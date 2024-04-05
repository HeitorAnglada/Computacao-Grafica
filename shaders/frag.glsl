#version 460 core

in vec3 v_vertexColors;

out vec4 FragColor;

uniform float u_ModelMatrix; // uniform variable
uniform mat4 u_Projection;

void main()
{
   FragColor = vec4(v_vertexColors.r, v_vertexColors.g, v_vertexColors.b, 1.0f);
}

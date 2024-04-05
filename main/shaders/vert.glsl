#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 vertexColors;

uniform float u_offset; // uniform variable

out vec3 v_vertexColors;

void main()
{
    v_vertexColors = vertexColors;

    gl_Position = vec4(aPos.x, aPos.y + u_offset, aPos.z, 1.0f);
}
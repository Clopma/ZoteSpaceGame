#version 330
in vec3 aPosition;

out vec4 lineColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 color;

void main()
{
    gl_Position = projection * view * model * vec4(aPosition, 1.0);
    lineColor = color;
}
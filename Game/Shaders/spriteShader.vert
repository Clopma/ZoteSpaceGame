#version 330
in vec3 aPosition;

out vec4 spriteColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPosition, 1.0);
    spriteColor = vec4(0.0, 1.0, 0.0, 1.0); //green
}
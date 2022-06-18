#version 330
in vec3 aPosition;
layout(location = 1) in vec2 tex;

out vec4 spriteColor;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPosition, 1.0);
    spriteColor = vec4(1.0, 1.0, 1.0, 1.0);

    TexCoord = tex;
}
#version 330
in vec3 aPosition;
layout(location = 1) in vec2 tex;

out vec4 spriteFragColor;
out vec2 TexCoord;
out float hasTexture;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float spriteHasTexture;
uniform vec4 spriteColor;


void main()
{
    gl_Position = projection * view * model * vec4(aPosition, 1.0);
    spriteFragColor = spriteColor;
    TexCoord = tex;
    hasTexture = spriteHasTexture;
}
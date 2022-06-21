#version 330

in vec4 spriteFragColor;
in vec2 TexCoord;
in float hasTexture;

out vec4 FragColor;

uniform sampler2D theTexture;

void main()
{
    vec4 textureColor = texture(theTexture, TexCoord);

    if (hasTexture != 0.0)
        FragColor = textureColor * spriteFragColor;
    else
        FragColor = spriteFragColor;
}
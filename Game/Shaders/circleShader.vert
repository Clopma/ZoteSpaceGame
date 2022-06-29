#version 330
in vec3 aPosition;

out vec3 circleColor;
out vec2 fragCoord;
out vec3 iResolution;
out float thickness;
out float fade;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 u_Resolution;
uniform vec4 u_circleColor;
uniform float u_circleThickness;
uniform float u_circleFade;

void main()
{
    gl_Position = projection * view * model * vec4(aPosition, 1.0);
    
    circleColor = vec3(u_circleColor.x, u_circleColor.y, u_circleColor.z);
    iResolution = u_Resolution;
    thickness = u_circleThickness;
    fade = u_circleFade;

    fragCoord = vec2(aPosition.x, aPosition.y);
    
}
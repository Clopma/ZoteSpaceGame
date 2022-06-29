#version 330

in vec3 circleColor;
in vec2 fragCoord;
in vec3 iResolution;
in float thickness;
in float fade;

out vec4 fragColor;

void main()
{   
    // -1 -> 1 local space, adjusted for aspect ratio
    vec2 uv = fragCoord / iResolution.xy * 2.0 - 1.0;
    float aspect = iResolution.x / iResolution.y;
    uv.x *= aspect;
    
    // Calculate distance and fill circle with white
    float distance = 1.0 - length(uv);
    vec3 color = vec3(smoothstep(0.0, fade, distance));
    color *= vec3(smoothstep(thickness + fade, thickness, distance));

    // Set output color
    fragColor = vec4(color, 1.0);
    fragColor.rgb *= circleColor;

    //fragColor = vec4(circleColor, 1.0);
}
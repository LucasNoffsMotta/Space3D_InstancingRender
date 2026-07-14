#version 330 core

in vec3 fColor;
in vec3 position;
out vec4 FragColor;

uniform float time;
vec2 tileSize = vec2(0.5f, 0.5f);


void main()
{
    vec2 uv = fColor.xy / tileSize.xy;
    vec3 color = 0.5 + 0.5 * cos(time + uv.xyx + vec3(0, 2, 4));
    
    float d = length(uv - 0.5);
    color *= sin(d * 10.0 - time * 5.0);
    color.x += 0.4f * (position.x / 0.01);
    color.y += 0.4f * (position.y / 0.01);
    color.z += 0.4f * (position.z / 0.01);
	FragColor = vec4(color, 1.0f);
}
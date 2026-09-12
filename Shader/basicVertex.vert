#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 fColor;
out vec3 position;
out vec3 FragPos;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;
uniform vec3 color;

void main()
{
    gl_Position = projection * view * model * vec4(aPos , 1.0);
    fColor = aColor + color;
    position = gl_Position.xyz;
    FragPos = vec3(model * vec4(aPos, 1));
}  
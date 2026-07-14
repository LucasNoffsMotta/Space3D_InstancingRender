#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 fColor;

uniform vec3 offsets[100];
uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;
uniform vec3 color;

void main()
{
    vec3 offset = offsets[gl_InstanceID];
    gl_Position = projection * view * model * vec4(aPos + offset, 1.0);
    fColor = aColor;
}  
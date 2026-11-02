#version 330 core
out vec4 FragColor;

in vec3 vsColor;

void main()
{
    FragColor = vec4(vsColor, 1.0);
}  
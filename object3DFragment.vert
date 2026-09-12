#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec3 aNormal;
layout (location = 4) in vec2 aTexCoord;


out vec3 fColor;
out vec3 position;
out vec3 FragPos;
out vec3 Normal;
out vec2 texCoord;


uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;
uniform vec3 color;

void main()
{
    gl_Position = projection * view * model * vec4(aPos , 1.0);
    fColor = aColor + color;
    position = gl_Position.xyz;
    Normal = mat3(transpose(inverse(model))) * aNormal;  
    FragPos = vec3(model * vec4(aPos, 1));
    texCoord = aTexCoord;
}  
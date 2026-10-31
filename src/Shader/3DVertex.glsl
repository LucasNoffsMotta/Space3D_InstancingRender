#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

layout (std140) uniform Matrices
{
                       //base alignment          //aligned offset
    mat4 projection;   //16                      0 
                       //16                      16
                       //16                      32
                       //16                      48

    mat4 view;         //16                      64
                       //16                      80
                       //16                      96
                       //16                      112
};

out vec3 position;
out vec3 FragPos;
out vec3 Normal;
out vec2 texCoord;


//uniform mat4 view;
//uniform mat4 projection;
uniform mat4 model;

void main()
{
    Normal = mat3(transpose(inverse(model))) * aNormal;  
    FragPos = vec3(model * vec4(aPos, 1));
    texCoord = aTexCoord;
    gl_Position = projection * view * model * vec4(aPos , 1.0);
    position = gl_Position.xyz;
    gl_PointSize = gl_Position.z;    
}  
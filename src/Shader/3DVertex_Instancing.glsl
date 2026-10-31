#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexPos;
layout (location = 3) in mat4 instanceModel;

out vec3 position;
out vec3 FragPos;
out vec3 Normal;
out vec2 texCoord;

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


void main()
{
	gl_Position = projection * view * instanceModel * vec4(aPos, 1.0f);
	position = gl_Position.xyz;
	Normal = mat3(transpose(inverse(instanceModel))) * aNormal;  
    FragPos = vec3(instanceModel * vec4(aPos, 1));
	texCoord = aTexPos;
}


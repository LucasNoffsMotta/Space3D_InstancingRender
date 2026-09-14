#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec3 aNormal;
layout (location = 4) in vec2 aTexPos;
layout (location = 5) in mat4 instanceModel;

out vec3 fColor;
out vec3 Normal;
out vec3 FragPos;
out vec2 texCoord;

uniform mat4 view;
uniform mat4 projection;
uniform vec3 color;


void main()
{
    FragPos = vec3(instanceModel * vec4(aPos, 1));
	gl_Position = projection * view * instanceModel * vec4(aPos, 1.0f);
	fColor = aColor + color;
	Normal = mat3(transpose(inverse(instanceModel))) * aNormal;  
	texCoord = aTexPos;
}


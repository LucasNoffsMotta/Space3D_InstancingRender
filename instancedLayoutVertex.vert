#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec3 aColor;
layout (location = 3) in mat4 instanceModel;

out vec3 fColor;

uniform mat4 view;
uniform mat4 projection;
uniform vec3 color;


void main()
{
	gl_Position = projection * view * instanceModel * vec4(aPos, 1.0f);
	fColor = aColor + color;
}


#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexPos;
layout (location = 3) in mat4 instanceModel;

out VS_OUT
{
     vec3 position;
     vec3 FragPos;
     vec3 FragmentShader_Normal;
     vec4 GeometryShader_normal;
     vec2 texCoord;
         mat4 View;
} vs_out;


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
	vs_out.position = gl_Position.xyz;
	vs_out.FragmentShader_Normal = mat3(transpose(inverse(instanceModel))) * aNormal;  
    vs_out.FragPos = vec3(instanceModel * vec4(aPos, 1));
	vs_out.texCoord = aTexPos;
}


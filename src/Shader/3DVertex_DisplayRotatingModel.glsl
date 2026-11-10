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

out VS_OUT
{
     vec3 position;
     vec3 FragPos;
     vec3 FragmentShader_Normal;
     vec4 GeometryShader_normal;
     vec2 texCoord;
         mat4 View;
} vs_out;


uniform mat4 fixedView;
uniform mat4 model;

void main()
{
    vs_out.texCoord = aTexCoord;
    gl_Position = projection *  fixedView * model * vec4(aPos , 1.0); 
}  
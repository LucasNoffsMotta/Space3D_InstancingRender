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
} vs_out;


uniform mat4 model;

void main()
{
    vs_out.FragmentShader_Normal = mat3(transpose(inverse(model))) * aNormal;
    vs_out.FragPos = vec3(model * vec4(aPos, 1));
    vs_out.texCoord = aTexCoord;

    mat4 normalMatrix = mat4(mat3(transpose(inverse(model))));
    vs_out.GeometryShader_normal = normalize(projection * view * normalMatrix * vec4(aNormal,0.f));

    gl_Position = projection * view * model * vec4(aPos , 1.0);
    vs_out.position = gl_Position.xyz;
    gl_PointSize = gl_Position.z;    
}  
#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

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
    mat3 viewWithoutTranslation = mat3(view);
    mat4 correctedview = mat4(viewWithoutTranslation);
    TexCoords = aPos;
    vec4 pos = projection * correctedview * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
}  
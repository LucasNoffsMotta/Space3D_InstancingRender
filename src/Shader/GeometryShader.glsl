#version 330 core
layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

in VS_OUT {
     vec3 position;
     vec3 FragPos;
     vec3 FragmentShader_Normal;
     vec4 GeometryShader_normal;
     vec2 texCoord;
} gs_in[];

out vec3 vsColor;

const float MAGNITUDE = 0.4;
  
  
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


void GenerateLine(int index, vec3 color)
{
    vsColor = color;
    gl_Position = gl_in[index].gl_Position; 
    EmitVertex();

    vsColor = color;
    gl_Position = (gl_in[index].gl_Position + 
                                vec4(gs_in[index].GeometryShader_normal) * MAGNITUDE);
    EmitVertex();
    EndPrimitive();
}

void main()
{
    GenerateLine(0, vec3(1, 0, 0)); // first vertex normal
    GenerateLine(1, vec3(0, 1, 0)); // second vertex normal
    GenerateLine(2,  vec3(0, 0, 1)); // third vertex normal
}  
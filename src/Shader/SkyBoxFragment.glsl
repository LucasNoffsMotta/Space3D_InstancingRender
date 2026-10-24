#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

struct Material
{
    samplerCube texture_diffuse1;
};

uniform Material material;

void main()
{    
    //FragColor = vec4(1,0,0,1);
    FragColor = texture(material.texture_diffuse1, TexCoords);
}
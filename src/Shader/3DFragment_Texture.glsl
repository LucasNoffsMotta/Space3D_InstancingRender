#version 330 core

struct Material {
    float shininess;
	float ior;
	sampler2D texture_diffuse1;
    sampler2D texture_diffuse2;
	sampler2D texture_diffuse3;
    sampler2D texture_specular1;
	sampler2D texture_specular2;
	samplerCube skybox; 
	vec4 color;
	bool useColor;
}; 

uniform Material material;
uniform int hasTexture;

in VS_OUT
{
     vec3 position;
     vec3 FragPos;
     vec3 FragmentShader_Normal;
     vec4 GeometryShader_normal;
     vec2 texCoord;
     mat4 View;
} fs_in;

out vec4 FragColor;

void main()
{
    if (!material.useColor)
    {
          FragColor = vec4(texture(material.texture_diffuse1, fs_in.texCoord));
    }

    else
    {
          FragColor = material.color;
    }
}
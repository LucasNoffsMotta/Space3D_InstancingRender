#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

struct DirLight
{
	vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform DirLight dirLight[1];

struct Material
{
    samplerCube skybox;
};

uniform Material material;


vec4 GetDirLight(DirLight light, vec4 diffuseColor)
{
    vec3 increasedAmbientLight = light.ambient + vec3(0.1, 0.1, 0.1);
	return vec4(increasedAmbientLight * diffuseColor.xyz, 1.f); 
}

void main()
{    
    vec4 diffColor = texture(material.skybox, TexCoords);
    FragColor = GetDirLight(dirLight[0], diffColor);
    //FragColor = texture(material.skybox, TexCoords);
}
#version 330 core



struct Material {
    sampler2D  diffuse;
    sampler2D  specular;
    float shininess;
}; 
  
uniform Material material;

struct SpotLight {
	vec3 position;
	vec3 direction;
	vec3 color;
	float outerCutoff;
	float innerCutoff;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	float constant;
    float linear;
    float quadratic;	
};

struct DirLight
{
	vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	vec3 color;
};

struct PointLight
{
	vec3 position;
	vec3 color;
		
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	float constant;
    float linear;
    float quadratic;	
};

#define MAX_POINTLIGHTS  4

uniform PointLight pointLight[MAX_POINTLIGHTS];
uniform SpotLight spotLight;
uniform DirLight dirLight;
uniform vec3 viewPos;

in vec3 FragPos;
in vec3 fColor;
in vec3 position;
in vec3 Normal;
in vec2 texCoord;
out vec4 FragColor;



vec3 GetDirLight(DirLight light, vec3 Normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(Normal, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, Normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	vec3 ambient = light.ambient *  light.color * vec3(texture(material.diffuse, texCoord)); 
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoord));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoord));
	return ambient + diffuse + specular;
}

vec3 GetPointLight(PointLight light, vec3 Normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightToFragmentDirection = normalize(light.position - FragPos);
	float diff = max(dot(Normal, lightToFragmentDirection), 0.0);

	vec3 reflectDir = reflect(-lightToFragmentDirection, Normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	float dist = length(light.position - FragPos);
	float atenuation = 1.0 / (light.constant + light.linear * dist +  light.quadratic * (dist * dist)); 

	vec3 ambient = light.ambient * light.color * vec3(texture(material.diffuse, texCoord));
	vec3 diffuse = light.diffuse * diff *  vec3(texture(material.diffuse, texCoord));
	vec3 specular = light.specular * spec *  vec3(texture(material.specular, texCoord));

	ambient *= atenuation;
	diffuse *= atenuation;
	specular *= atenuation;

	return ambient + diffuse + specular;
}


vec3 GetSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightToFragmentDirection = normalize(light.position - FragPos);
	float diff = max(dot(normal, lightToFragmentDirection), 0.0);

	vec3 reflectDir = reflect(-lightToFragmentDirection, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	float dist = length(light.position - FragPos);
	float atenuation = 1.0 / (light.constant + light.linear * dist +  light.quadratic * (dist * dist)); 

	float theta = dot(lightToFragmentDirection, normalize(-light.direction));
	float epsilon = light.innerCutoff - light.outerCutoff;
	float intensity = clamp((theta - light.outerCutoff) / epsilon, 0.0, 1.0);

	vec3 ambient = light.ambient * light.color * vec3(texture(material.diffuse, texCoord));
	vec3 diffuse = light.diffuse * diff *  vec3(texture(material.diffuse, texCoord));
	vec3 specular = light.specular * spec *  vec3(texture(material.specular, texCoord));

	ambient *= atenuation * intensity;
	diffuse *= atenuation * intensity;
	specular *= atenuation * intensity;

	return ambient + diffuse + specular;
}



void main()
{
	vec3 normal = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = GetDirLight(dirLight, normal, viewDir);
	result += GetSpotLight(spotLight, normal, FragPos, viewDir);

	for (int i = 0; i < MAX_POINTLIGHTS; i++)
	{
			result += GetPointLight(pointLight[i], normal, FragPos, viewDir);
	}

	FragColor = vec4(result, 1);
}
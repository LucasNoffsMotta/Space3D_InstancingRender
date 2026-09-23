#version 330 core



struct Material {
    float shininess;
	sampler2D texture_diffuse1;
    sampler2D texture_diffuse2;
	sampler2D texture_diffuse3;
    sampler2D texture_specular1;
	sampler2D texture_specular2;
}; 
  
uniform Material material;

struct SpotLight {
	vec3 position;
	vec3 direction;
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
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	float constant;
    float linear;
    float quadratic;	
};

#define MAX_POINTLIGHTS  10

uniform PointLight pointLight[MAX_POINTLIGHTS];
uniform SpotLight spotLight[MAX_POINTLIGHTS];
uniform DirLight dirLight[MAX_POINTLIGHTS];
uniform vec3 viewPos;

in vec3 FragPos;
in vec3 position;
in vec3 Normal;
in vec2 texCoord;
out vec4 FragColor;

float near = 0.1;
float far = 6000;

float LinearizeDepth(float depth)
{
	 float z = depth * 2.0 - 1.0; // back to NDC 
	 return (2.0 * near * far) / (far + near - z * (far - near));
}

vec3 GetDirLight(DirLight light, vec3 Normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(Normal, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, Normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	vec3 ambient = light.ambient *  light.color * vec3(texture(material.texture_diffuse1, texCoord)); 
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse1, texCoord));
	vec3 specular = light.specular * spec * vec3(texture(material.texture_specular1, texCoord));
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

	vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1, texCoord));
	vec3 diffuse = light.diffuse * diff *  vec3(texture(material.texture_diffuse1, texCoord));
	vec3 specular = light.specular * spec *  vec3(texture(material.texture_specular1, texCoord));

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

	vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1, texCoord));
	vec3 diffuse = light.diffuse * diff *  vec3(texture(material.texture_diffuse1, texCoord));
	vec3 specular = light.specular * spec *  vec3(texture(material.texture_specular1, texCoord));

	ambient *= atenuation * intensity;
	diffuse *= atenuation * intensity;
	specular *= atenuation * intensity;

	return ambient + diffuse + specular;
}



void main()
{
	vec3 normal = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
    vec3 result = vec3(0);


	for (int i = 0; i < MAX_POINTLIGHTS; i++)
	{
			result += GetDirLight(dirLight[i], normal, viewDir);
			result += GetPointLight(pointLight[i], normal, FragPos, viewDir);
			result += GetSpotLight(spotLight[i], normal, FragPos, viewDir);
	}




	//For depth test:
	float depth = LinearizeDepth(gl_FragCoord.z) / far; // divide by far for demonstration
    //FragColor = vec4(vec3(depth), 1.0);
	FragColor = vec4(result, depth);
	//FragColor = vec4(texCoord, 0.0, 1.0);
}
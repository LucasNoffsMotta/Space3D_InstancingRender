#version 330 core


struct RenderMode {
     int DebugMode;
	 int DepthTestMode;
	 int LightsOff;
	 int Full_LightsAndReflection;
};

uniform RenderMode rm;

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
uniform int hasTexture;
uniform int HasReflectionTexture;


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


vec3 GetDirLight(DirLight light, vec3 Normal, vec3 viewDir, vec4 diffuseColor, vec3 specularColor)
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(Normal, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, Normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	if (!material.useColor) {

		ambient = light.ambient * diffuseColor.xyz; 
		diffuse = light.diffuse * diff *  diffuseColor.xyz;
		specular = light.specular * spec * specularColor;
	}

	else {
		
		ambient = light.ambient * material.color.rgb; 
		diffuse = light.diffuse * diff *  material.color.rgb;
		specular = light.specular * spec * material.color.rgb;
	}

	return ambient + diffuse + specular;
}

vec3 GetPointLight(PointLight light, vec3 Normal, vec3 fragPos, vec3 viewDir, vec4 diffuseColor, vec3 specularColor)
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 lightToFragmentDirection = normalize(light.position - FragPos);
	float diff = max(dot(Normal, lightToFragmentDirection), 0.0);

	vec3 reflectDir = reflect(-lightToFragmentDirection, Normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	float dist = length(light.position - FragPos);
	float atenuation = 1.0 / (light.constant + light.linear * dist +  light.quadratic * (dist * dist)); 

	if (!material.useColor) {
		
		ambient = light.ambient * diffuseColor.xyz;
		diffuse = light.diffuse * diff * diffuseColor.xyz;
		specular = light.specular * spec * specularColor;
	}

	else {
		ambient = light.ambient * material.color.rgb; 
		diffuse = light.diffuse * diff *  material.color.rgb;
		specular = light.specular * spec * material.color.rgb;
	}

	ambient *= atenuation;
	diffuse *= atenuation;
	specular *= atenuation;

	return ambient + diffuse + specular;
}


vec3 GetSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir,  vec4 diffuseColor, vec3 specularColor)
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 lightToFragmentDirection = normalize(light.position - FragPos);
	float diff = max(dot(normal, lightToFragmentDirection), 0.0);

	vec3 reflectDir = reflect(-lightToFragmentDirection, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	float dist = length(light.position - FragPos);
	float atenuation = 1.0 / (light.constant + light.linear * dist +  light.quadratic * (dist * dist)); 

	float theta = dot(lightToFragmentDirection, normalize(-light.direction));
	float epsilon = light.innerCutoff - light.outerCutoff;
	float intensity = clamp((theta - light.outerCutoff) / epsilon, 0.0, 1.0);

	if (!material.useColor) {
		ambient = light.ambient * diffuseColor.xyz;
		diffuse = light.diffuse * diff * diffuseColor.xyz;
		specular = light.specular * spec * specularColor;
	}
	 
	 else {
		ambient = light.ambient *  material.color.rgb; 
		diffuse = light.diffuse * diff *  material.color.rgb;
		specular = light.specular * spec * material.color.rgb;
	}

	ambient *= atenuation * intensity;
	diffuse *= atenuation * intensity;
	specular *= atenuation * intensity;

	return ambient + diffuse + specular;
}

float GetFinalAlphaValue(vec4 diffuseColor, Material material)
{
	if (hasTexture == 1)
	{
		return diffuseColor.a;
	}

	else
	{
		return material.color.a;
	}
}


vec3 GetFullLitColorResult(vec4 diffuseColor)
{
	vec3 normal = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 result = vec3(0);
	vec3 specularColor = vec3(texture(material.texture_specular1, texCoord));

	for (int i = 0; i < MAX_POINTLIGHTS; i++)
	{
		result += GetDirLight(dirLight[i], normal, viewDir, diffuseColor, specularColor);
		result += GetPointLight(pointLight[i], normal, FragPos, viewDir, diffuseColor, specularColor);
		result += GetSpotLight(spotLight[i], normal, FragPos, viewDir, diffuseColor, specularColor);
	}

	return result;
}


void main()
{
	//Turn On Debug Mode
	if (rm.DebugMode == 1)
	{
		FragColor =  vec4(texCoord, 0.0, 1.0);
		return;
	}

	//Turn On Depth Test Mode
	if (rm.DepthTestMode == 1)
	{
		float depth = LinearizeDepth(gl_FragCoord.z) / far; 
		FragColor = vec4(vec3(depth), 1.0);
		return;
	}

	//Discard fragmets
	vec4 diffuseColor = vec4(texture(material.texture_diffuse1, texCoord));

	if (diffuseColor.a < 0.1)
	{
		discard;
	}

	//Turn Off lit mode
	if (rm.LightsOff == 1)
	{
		if (!material.useColor) {
			FragColor =  vec4(texture(material.texture_diffuse1, texCoord));
		}

		else
		{
			FragColor =  vec4(material.color);
		}

		return;
	}

	if (rm.Full_LightsAndReflection == 1 && HasReflectionTexture == 1) {
		vec3 I = normalize(position - viewPos);
		vec3 R = reflect(I, normalize(Normal));
		vec4 reflectionColor =  vec4(texture(material.skybox, R).rgb, 1.0);
		FragColor = mix(vec4(GetFullLitColorResult(diffuseColor), GetFinalAlphaValue(diffuseColor, material)), reflectionColor, 0.5);
		return;
	}

	else if (rm.Full_LightsAndReflection == 1 && HasReflectionTexture == 0)
	{	
		FragColor = vec4(GetFullLitColorResult(diffuseColor), GetFinalAlphaValue(diffuseColor, material));
	}
}
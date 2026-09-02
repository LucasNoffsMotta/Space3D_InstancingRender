#version 330 core

in vec3 FragPos;
in vec3 fColor;
in vec3 position;
in vec3 Normal;
out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 lightDirection;
uniform float cutOff;


void main()
{
	float lightStrength;
    vec3 lightDir = normalize(lightPos - FragPos);
	float theta = dot(lightDir, normalize(-lightDirection));

	if (theta > cutOff)
	{
		lightStrength = dot(lightDir, Normal);
	}

	else
	{
	   lightStrength = 0;
	}

	lightStrength = pow(lightStrength, 50.0);
	lightStrength = clamp(lightStrength, 0.0, 1.0);
	vec3 result = fColor.rgb * lightStrength;
	FragColor = vec4(result, 1);
}
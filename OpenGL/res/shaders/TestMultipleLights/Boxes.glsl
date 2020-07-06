#shader vertex
#version 330 core
layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_TexCoord;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

void main()
{
	TexCoord = a_TexCoord;
	Normal = mat3(transpose(inverse(u_Model))) * a_Normal;
	FragPos = vec3(u_Model * vec4(a_Pos, 1.0f));

	gl_Position = u_Proj * u_View * vec4(FragPos, 1.0f);
}

#shader fragment
#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

struct DirLight
{
	vec3 Direction;
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
};

struct PointLight
{
	vec3 Pos;
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
	float Kc, Kl, Kq;
};

struct SpotLight
{
	vec3 Pos;
	vec3 LightDir;
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
	float Kc, Kl, Kq;
	float CutOff, OutCutOff;
};

struct MaterialMap
{
	sampler2D Diffuse;
	sampler2D Specular;
	float Shininess;
};

uniform DirLight u_DirLight;
uniform PointLight u_PointLight[4];
uniform SpotLight u_SpotLight;
uniform MaterialMap u_Map;
uniform vec3 u_CamPos;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.Direction);

	//Ambient
	vec3 ambient = light.Ambient * texture(u_Map.Diffuse, TexCoord).rgb;

	//Diffuse
	float diff = max(dot(lightDir, normal), 0.0f);
	vec3 diffuse = diff * light.Diffuse * texture(u_Map.Diffuse, TexCoord).rgb;

	//Specular
	vec3 reflection = reflect(-lightDir, normal);
	float spec = pow(max(dot(reflection, viewDir), 0.0f), u_Map.Shininess);
	vec3 specular = spec * light.Specular * texture(u_Map.Specular, TexCoord).rgb;

	return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.Pos - fragPos);

	//Ambient
	vec3 ambient = light.Ambient * texture(u_Map.Diffuse, TexCoord).rgb;

	//Diffuse
	float diff = max(dot(lightDir, normal), 0.0f);
	vec3 diffuse = diff * light.Diffuse * texture(u_Map.Diffuse, TexCoord).rgb;

	//specular
	vec3 reflection = reflect(-lightDir, normal);
	float spec = pow(max(dot(reflection, viewDir), 0.0f), u_Map.Shininess);
	vec3 specular = spec * light.Specular * texture(u_Map.Specular, TexCoord).rgb;

	//Attenuation
	float d = length(light.Pos - fragPos);
	float attenuation = 1.0f / (light.Kc + light.Kl*d + light.Kq*d*d);
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}


vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.Pos - fragPos);

	//Ambient
	vec3 ambient = light.Ambient * texture(u_Map.Diffuse, TexCoord).rgb;

	//Diffuse
	float diff = max(dot(lightDir, normal), 0.0f);
	vec3 diffuse = diff * light.Diffuse * texture(u_Map.Diffuse, TexCoord).rgb;

	//Sepcular
	vec3 reflection = reflect(-lightDir, normal);
	float spec = pow(max(dot(reflection, viewDir), 0.0f), u_Map.Shininess);
	vec3 specular = spec * light.Specular * texture(u_Map.Specular, TexCoord).rgb;

	//Attenuation
	float d = length(light.Pos - fragPos);
	float attenuation = 1.0f / (light.Kc + light.Kl*d + light.Kq*d*d);

	//Intensity
	float theta = dot(lightDir, normalize(-light.LightDir));
	float epsilon = light.CutOff - light.OutCutOff;
	float intensity = clamp((theta - light.OutCutOff) / epsilon, 0.0f, 1.0f);

	ambient *= attenuation * intensity;
	diffuse *= attenuation * intensity;
	specular *= attenuation * intensity;

	return (ambient + diffuse + specular);
}

void main()
{
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(u_CamPos - FragPos);

	vec3 result = CalcDirLight(u_DirLight, norm, viewDir);
	for (int i = 0; i < 4; i++)
		result += CalcPointLight(u_PointLight[i], norm, FragPos, viewDir);

	result += CalcSpotLight(u_SpotLight, norm, FragPos, viewDir);
	FragColor = vec4(result, 1.0f);
}
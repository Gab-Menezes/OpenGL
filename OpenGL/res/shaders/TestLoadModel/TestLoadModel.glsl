#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;

void main()
{
    TexCoords = aTexCoords;
	FragPos = vec3(u_Model * vec4(aPos, 1.0f));
	Normal = mat3(transpose(inverse(u_Model))) * aNormal;

    gl_Position = u_Proj * u_View * vec4(FragPos, 1.0f);
}

#shader fragment
#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

struct PointLight
{
	vec3 Pos, Ambient, Diffuse, Specular;
	float Kc, Kl, Kq;
};

struct Model
{
	sampler2D Texture_Diffuse1;
	sampler2D Texture_Specular1;
	float Shininess;
};

uniform Model u_Map;
uniform PointLight u_Light;
uniform vec3 u_CamPos;

void main()
{    
    vec3 diffMap = texture(u_Map.Texture_Diffuse1, TexCoords).rgb;
	vec3 specMap = texture(u_Map.Texture_Specular1, TexCoords).rgb;
	vec3 norm = normalize(Normal);

	//Ambient
	vec3 ambient = diffMap * u_Light.Ambient;

	//Diffuse
	vec3 lightDir = normalize(u_Light.Pos - FragPos);
	float diff = max(dot(lightDir, norm), 0.0);
	vec3 diffuse = diff * diffMap * u_Light.Diffuse;

	//Specular
	vec3 viewDir = normalize(u_CamPos - FragPos);
	vec3 reflection = reflect(-lightDir, norm);
	float spec = pow(max(dot(reflection, viewDir), 0.0f), u_Map.Shininess);
	vec3 specular = spec * specMap * u_Light.Specular;

	//attenuation
	float d = length(u_Light.Pos - FragPos);
	float attenuation = 1.0f / (u_Light.Kc + u_Light.Kl*d + u_Light.Kq*d*d);

	vec3 result = attenuation * (ambient + diffuse + specular);


	FragColor = vec4(result, 1.0f);
}
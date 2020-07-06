#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 Normal;
out vec3 FragPos;//Position of the fragment relative to the world
out vec2 TexCoord;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;

void main()
{
	FragPos = vec3(u_Model * vec4(aPos, 1.0f));//normal matrix * normals -> acts like the model matrix to the normals
	Normal = mat3(transpose(inverse(u_Model))) * aNormal;
	TexCoord = aTexCoord;

	gl_Position = u_Proj * u_View * vec4(FragPos, 1.0f);
}

#shader fragment
#version 330 core
out vec4 FragColor;

struct Material 
{
	sampler2D Diffuse;//usuly diffuse = ambient
	sampler2D Specular;
	float Shininess;
};

struct Light 
{
	vec3 Pos;

	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform vec3 u_CamPos;
uniform Material u_Map;
uniform Light u_Light;
	
void main()
{
	vec3 DiffMap = texture(u_Map.Diffuse, TexCoord).rgb;
	vec3 SpecMap = texture(u_Map.Specular, TexCoord).rgb;


	// ambient
    vec3 ambient = u_Light.Ambient * DiffMap;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(u_Light.Pos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = u_Light.Diffuse * (diff * DiffMap);
    
    // specular
    vec3 viewDir = normalize(u_CamPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Map.Shininess);
    vec3 specular = u_Light.Specular * (spec * SpecMap);  
        
	vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
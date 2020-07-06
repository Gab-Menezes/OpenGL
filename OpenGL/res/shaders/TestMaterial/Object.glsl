#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 Normal;
out vec3 FragPos;//Position of the fragment relative to the world

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;

void main()
{
	FragPos = vec3(u_Model * vec4(aPos, 1.0f));//normal matrix * normals -> acts like the model matrix to the normals
	Normal = mat3(transpose(inverse(u_Model))) * aNormal;

	gl_Position = u_Proj * u_View * vec4(FragPos, 1.0f);
}

#shader fragment
#version 330 core
out vec4 FragColor;

struct Material 
{
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
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

uniform vec3 u_CamPos;
uniform Material u_Material;
uniform Light u_Light;
	
void main()
{
	// ambient
    vec3 ambient = u_Light.Ambient * u_Material.Ambient;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(u_Light.Pos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = u_Light.Diffuse * (diff * u_Material.Diffuse);
    
    // specular
    vec3 viewDir = normalize(u_CamPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.Shininess);
    vec3 specular = u_Light.Specular * (spec * u_Material.Specular);  
        
	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result, 1.0);
}
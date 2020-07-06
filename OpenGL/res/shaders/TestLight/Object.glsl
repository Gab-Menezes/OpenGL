#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;

out vec3 Normal;
out vec3 FragPos;//Position of the fragment relative to the world

void main()
{
	//normal matrix * normals -> acts like the model matrix to the normals
	FragPos = vec3(u_Model * vec4(aPos, 1.0f)); 
	Normal = mat3(transpose(inverse(u_Model))) * aNormal;

	gl_Position = u_Proj * u_View * vec4(FragPos, 1.0f);
}

#shader fragment
#version 330 core
in vec3 Normal;
in vec3 FragPos;

uniform vec4 u_ColorObj;
uniform vec4 u_ColorLight;
uniform vec3 u_LightPos;
uniform vec3 u_CamPos;

uniform float u_AmbientStrength;
uniform float u_DiffuseStrength;
uniform float u_SpecularStrength;
uniform int u_SpecularShininess;
	
out vec4 FragColor;

void main()
{
	//ambient light
	float ambientStrength = u_AmbientStrength;
	vec4 ambient = u_ColorLight * ambientStrength;

	//diffuse light
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(u_LightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec4 diffuse = diff * u_ColorLight;

	//specular light
	float specularStrength = u_SpecularStrength;
	vec3 viewDir = normalize(u_CamPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_SpecularShininess);
	vec4 specular = specularStrength * spec * u_ColorLight;

	/*phong lighting*/
	FragColor = u_ColorObj * (ambient + diffuse + specular);
}
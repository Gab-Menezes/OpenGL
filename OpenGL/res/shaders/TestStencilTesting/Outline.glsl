#shader vertex
#version 330 core
layout (location = 0) in vec3 a_Pos;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;

void main()
{
	gl_Position = u_Proj * u_View * u_Model * vec4(a_Pos, 1.0f);
}

#shader fragment
#version 330 core

out vec4 FragColor;

void main()
{
	FragColor = vec4(0.04, 0.28, 0.26, 1.0);
}
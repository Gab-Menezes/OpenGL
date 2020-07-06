#shader vertex
#version 330 core
layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec2 a_TexCoord;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;

out vec2 TexCoord;

void main()
{
	gl_Position = u_Proj * u_View * u_Model * vec4(a_Pos, 1.0f);
	TexCoord = a_TexCoord;
}

#shader fragment
#version 330 core
uniform sampler2D u_Texture;

in vec2 TexCoord;

out vec4 FragColor;

void main()
{
	FragColor = texture(u_Texture, TexCoord);
}
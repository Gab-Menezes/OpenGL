#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;

out vec2 TexCoord;

void main()
{
	gl_Position = u_Proj * u_View * u_Model * vec4(aPos, 1.0);
	TexCoord = aTexCoord;
}

#shader fragment
#version 330 core
in vec2 TexCoord;

uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;

out vec4 FragColor;

void main()
{
	FragColor = mix(texture(u_Texture1, TexCoord), texture(u_Texture2, TexCoord), 0.2);
}
#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

void main()
{
	TexCoord = aTexCoord;
	gl_Position = vec4(aPos, 1.0);
}

#shader fragment
#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D u_Texture;

void main()
{
	vec3 color = vec3(texture(u_Texture, TexCoord));
	float gray = (2*color.r + 3*color.g + color.b)/6.0;
	FragColor = vec4(vec3(gray), 1.0);

//	float cLinear = (0.2126*color.r + 0.7152*color.g + 0.0722*color.b);
//	float cSRGB = 1.0;
//	if (cLinear <= 0.0031308)
//	{
//		cSRGB = 12.92 * cLinear;
//	}
//	else
//	{
//		cSRGB = 1.055 * pow(cLinear, 1/2.4) - 0.055;
//	}

	//FragColor = vec4(vec3(cSRGB), 1.0);
}
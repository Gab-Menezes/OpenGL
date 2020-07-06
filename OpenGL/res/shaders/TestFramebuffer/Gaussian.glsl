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
uniform float u_OffsetH, u_OffsetV;
uniform int u_Vertical;

void main()
{
	float kernel[11] = float[]
	(
		0.0093,	  0.028002, 0.065984,	
		0.121703, 0.175713,	0.198596,
		0.175713, 0.121703,	0.065984,
		0.028002, 0.0093
	);

	float GaussianGray = 0.0;
	for(int i = -5; i <= 5; i++)
	{
		vec2 coordOffset;
		if(u_Vertical == 1)
			coordOffset = vec2(0.0, u_OffsetV*i);
		else
			coordOffset = vec2(u_OffsetH*i, 0.0);

		//r==g==b -> gray scale
		float pixelGray = vec3(texture(u_Texture, TexCoord.st + coordOffset)).r;
		GaussianGray += pixelGray * kernel[i+5];
	}
	FragColor = vec4(vec3(GaussianGray), 1.0);
}
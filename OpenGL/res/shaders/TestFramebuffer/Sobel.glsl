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

void main()
{
	vec2 offsets[9] = vec2[](
        vec2(-u_OffsetH,  u_OffsetV), // top-left
        vec2( 0.0f,       u_OffsetV), // top-center
        vec2( u_OffsetH,  u_OffsetV), // top-right
        vec2(-u_OffsetH,  0.0f),      // center-left
        vec2( 0.0f,       0.0f),      // center-center
        vec2( u_OffsetH,  0.0f),      // center-right
        vec2(-u_OffsetH, -u_OffsetV), // bottom-left
        vec2( 0.0f,      -u_OffsetV), // bottom-center
        vec2( u_OffsetH, -u_OffsetV)  // bottom-right    
    );

	float kernelX[9] = float[]
	(
		1, 0, -1,
		2, 0, -2,
		1, 0, -1
	);

	float kernelY[9] = float[]
	(
		 1,  2,  1,
		 0,  0,  0,
		-1, -2, -1
	);

	vec3 pixels[9];
    for(int i = 0; i < 9; i++)
    {
		pixels[i] = vec3(texture(u_Texture, TexCoord.st + offsets[i]));
		//pixels.r == pixels.g ==  pixels.b -> gray scale
    }

	float gx = 0.0, gy = 0.0;
    for(int i = 0; i < 9; i++)
	{
		gx += pixels[i].r * kernelX[i];
		gy += pixels[i].r * kernelY[i]; 
	}
	float g = sqrt(gx*gx + gy*gy);

	FragColor = vec4(vec3(g), 1.0);
}
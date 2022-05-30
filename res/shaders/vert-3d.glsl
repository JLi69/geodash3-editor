#version 430

//Perspective and model view matrix
uniform mat4 u_PerspectiveMat,
			 u_ModelViewMat;

//Input of the position
layout(location = 0) in vec4 pos;
//Input of texture coordinate
layout(location = 1) in vec2 texCoord;
//Output texture coordinate for fragment shader
out vec2 o_texCoord;
layout(binding = 0) uniform sampler2D samp;

//location in 3D space
out vec4 fragPos;

//Shading
out float o_Shading;

void main()
{
	gl_Position = u_PerspectiveMat * u_ModelViewMat * pos;

	fragPos = pos;

	//Set the texture coordinate for fragment
	o_texCoord = texCoord;

	if(pos.y == 1.0)
		o_Shading = 0.5;
	else if(pos.y == -1.0)
		o_Shading = 1.0;
}

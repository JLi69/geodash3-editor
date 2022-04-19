#version 430

//Perspective and model view matrix
uniform mat4 u_PerspectiveMat,
			 u_ModelViewMat;

//Input of the position
layout(location = 0) in vec4 pos;

//location in 3D space
out vec4 fragPos;

void main()
{
	gl_Position = u_PerspectiveMat * u_ModelViewMat * pos;

	fragPos = pos;
}

#version 430

uniform vec4 u_Color;
out vec4 o_Color;

//Fragment location in 3D space
in vec4 fragPos;

void main()
{
	o_Color = u_Color;

	//Outline the cube
	if(abs(fragPos.x) > 0.95 && abs(fragPos.y) > 0.95 ||
		abs(fragPos.y) > 0.95 && abs(fragPos.z) > 0.95 ||
		abs(fragPos.x) > 0.95 && abs(fragPos.z) > 0.95)
		o_Color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

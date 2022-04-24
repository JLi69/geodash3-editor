#version 430

//Color that gets passed into the shader
uniform vec4 u_Color;

//Color to be outputted
out vec4 o_Color;

//location of the fragment in 3D space
in vec4 fragPos;

void main()
{
	o_Color = u_Color;

	//Outline the pyramid
	if(abs(fragPos.x) > 0.95 && abs(fragPos.y) > 0.9 ||
		abs(fragPos.y) > 0.95 && abs(fragPos.z) > 0.9 ||
		abs(fragPos.x) > 0.95 && abs(fragPos.z) > 0.9)
		o_Color = vec4(0.0f, 0.0f, 0.0f, 1.0f);

	if(fragPos.x + 0.5 + fragPos.z + 0.5 <= fragPos.y + 0.1 &&
		fragPos.x + 0.5 + fragPos.z + 0.5 >= fragPos.y - 0.1 ||

		-fragPos.x + 0.5 + fragPos.z + 0.5 <= fragPos.y + 0.1 &&
		-fragPos.x + 0.5 + fragPos.z + 0.5 >= fragPos.y - 0.1 ||
		
		fragPos.x + 0.5 - fragPos.z + 0.5 <= fragPos.y + 0.1 &&
		fragPos.x + 0.5 - fragPos.z + 0.5 >= fragPos.y - 0.1 ||

		-fragPos.x + 0.5 - fragPos.z + 0.5 <= fragPos.y + 0.1 &&
		-fragPos.x + 0.5 - fragPos.z + 0.5 >= fragPos.y - 0.1) 
		o_Color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

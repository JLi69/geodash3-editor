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

	if(fragPos.x + 0.5 + fragPos.z + 0.5 <= fragPos.y + 0.5 &&
		fragPos.x + 0.5 + fragPos.z + 0.5 >= fragPos.y - 0.5 ||

		-fragPos.x + 0.5 + fragPos.z + 0.5 <= fragPos.y + 0.5 &&
		-fragPos.x + 0.5 + fragPos.z + 0.5 >= fragPos.y - 0.5 ||
		
		fragPos.x + 0.5 - fragPos.z + 0.5 <= fragPos.y + 0.5 &&
		fragPos.x + 0.5 - fragPos.z + 0.5 >= fragPos.y - 0.5 ||

		-fragPos.x + 0.5 - fragPos.z + 0.5 <= fragPos.y + 0.5 &&
		-fragPos.x + 0.5 - fragPos.z + 0.5 >= fragPos.y - 0.5) 
		o_Color *= 0.5;
}

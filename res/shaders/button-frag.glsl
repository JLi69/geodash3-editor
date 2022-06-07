#version 430

out vec4 o_Color;

//Fragment location in 3D space
in vec4 fragPos;

//Whether the button is hovered over
uniform bool u_hovering;

//Texture coordinate
in vec2 o_texCoord;

layout(binding = 0) uniform sampler2D samp;

void main()
{
	o_Color = texture(samp, o_texCoord);

	//Make the button brighter	
	if(u_hovering)
		o_Color += vec4(0.5, 0.5, 0.5, 0.0);
}

#define INCLUDE_INIT
#include <GLFW/glfw3.h>

namespace Geodash3
{
	//Cube mesh
	const float cubeVerts[108] = 
	{
		 -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
		 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
		 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		 -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		 -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
		 -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
		 -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,
		 -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f
	};

	//Pyramid mesh	
	const float pyramidVerts[54] =
	{ 
		-1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, // front face
		1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, // right face
		1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, // back face
		-1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, // left face
		-1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, // base – left front
		1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f // base – right back
	};

	//Rectangle mesh
	const float rect[18] = 
	{
		-1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,

		1.0f, -1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f
	};

	//Texture coordinates for a cube
	const float texCubeCoords[72] = 
	{
		 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,

		 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		 
		 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		 
		 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		 
		 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		 
		 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f 
	};

	//Texture coordinates for cube but top face and bottom face are different
	const float texCubeCoordsTop[72] = 
	{
		0.5f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f,

		0.5f, 0.0f, 0.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f,
		 
		0.5f, 0.0f, 0.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f,
		 
		0.5f, 0.0f, 0.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f,
		 
		1.0f, 1.0f, 1.0f, 0.0f, 0.5f, 0.0f,
		0.5f, 0.0f, 0.5f, 1.0f, 1.0f, 1.0f,
		 
		0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.5f, 0.0f, 0.5f, 1.0f	
	};

	//Texture coordinates for a pyramid
	const float texPyrCoords[36] =
	{
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f, //top and right faces
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f, //back and left faces
		0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,		1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f //base triangles	
	};

	//Texture coordinates for a rectangle
	const float texRectCoords[] = 
	{
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,

		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f
	};

	//Initialize variables
	void init(GLFWwindow *&win, const char *title, GLFWwindowsizefun onWindowResize);
}

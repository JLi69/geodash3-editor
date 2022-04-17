#include "GetOpenGLError.h"
#include <glad/glad.h>
#include <iostream>

bool checkOpenGLError()
{
	bool foundErr = false;
	int glErr = glGetError();
	//Keep printing out errors until there are any left
	while(glErr != GL_NO_ERROR)
	{
		std::cout << "OpenGL error: " << glErr << '\n';
		foundErr = true;
		glErr = glGetError();
	}
	return foundErr;
}

#ifndef INCLUDE_GLAD
#include <glad/glad.h>
#endif

#define GL_CALL(x) x; checkOpenGLError()

//This function will check for any OpenGL errors and then report them
bool checkOpenGLError();

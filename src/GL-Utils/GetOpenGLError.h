#include <glad/glad.h>

#define GL_CALL(x) x; checkOpenGLError()

//This function will check for any OpenGL errors and then report them
bool checkOpenGLError();

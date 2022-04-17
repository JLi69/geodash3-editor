#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "src/GL-Utils/Shader.h"
#include "src/GL-Utils/VertexBufferObj.h"
#include "src/GL-Utils/GetOpenGLError.h"

int main()
{
	//Initialize glfw
	if(!glfwInit())
		return -1;	

	//Initialize the window
	GLFWwindow* glWindow;
	glWindow = glfwCreateWindow(1920, 1080, "Geodash 3D", NULL, NULL);
	if(!glWindow)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(glWindow);

	//Initialize glad
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return -1;

	//Test triangle
	float testtri[6] = 
	{
		0.0f, 0.5f,
		-0.5f, -0.5f,
		0.5f, -0.5f
	};

	GL_CALL(VertexBufferObj vbo = VertexBufferObj());
	GL_CALL(vbo.Data(testtri, sizeof(testtri), 2));
	GL_CALL(vbo.Enable());

	GL_CALL(Shader sh = Shader("res/shaders/basic-vert.glsl", "res/shaders/basic-frag.glsl"));
	GL_CALL(glUseProgram(sh.GetId()));
	GL_CALL(int loc = sh.GetUniformLocation("u_Color"));

	while(!glfwWindowShouldClose(glWindow))
	{
		GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

		GL_CALL(glUniform4f(loc, 0.0f, 1.0f, 0.0f, 1.0f));
		GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 3));

		glfwSwapBuffers(glWindow);
		glfwPollEvents();
	}

	glfwTerminate();
}

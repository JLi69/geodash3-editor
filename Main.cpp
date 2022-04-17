#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "src/GL-Utils/Shader.h"
#include "src/GL-Utils/VertexBufferObj.h"
#include "src/GL-Utils/GetOpenGLError.h"
#include "src/Init/init.h"

int main()
{
	//Initialize the window
	GLFWwindow *glWindow;
	Geodash3::init(glWindow, "Geodash 3D");

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

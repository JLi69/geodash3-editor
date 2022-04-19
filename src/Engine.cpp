#include "Engine.h"

//Main loop
void Geodash3::Engine::Run()
{
	//Test triangle
	float testcube[108] = 
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

	GL_CALL(VertexBufferObj vbo = VertexBufferObj());
	GL_CALL(vbo.Data(testcube, sizeof(testcube), 3));
	GL_CALL(vbo.Enable());

	GL_CALL(Shader sh = Shader("res/shaders/vert-3d.glsl", "res/shaders/basic-frag.glsl"));
	GL_CALL(glUseProgram(sh.GetId()));
	GL_CALL(int loc = sh.GetUniformLocation("u_Color"));
	GL_CALL(int pLoc = sh.GetUniformLocation("u_PerspectiveMat"));
	GL_CALL(int mvLoc = sh.GetUniformLocation("u_ModelViewMat"));

	GL_CALL(glUniform4f(loc, 0.0f, 1.0f, 0.0f, 1.0f));
	GL_CALL(glUniformMatrix4fv(pLoc, 1, false, glm::value_ptr(perspectiveMat)));
	
	glm::mat4 mv = rotationMatrix * viewMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.5f, -6.0f));

	GL_CALL(glUniformMatrix4fv(mvLoc, 1, false, glm::value_ptr(mv)));

	GL_CALL(glClearColor(0.0f, 0.8f, 1.0f, 1.0f));

	GL_CALL(glEnable(GL_DEPTH_TEST));
	GL_CALL(glDepthFunc(GL_LEQUAL));

	float theta = 0.0f;

	while(!glfwWindowShouldClose(gameWindow))
	{
		this->Display();

		theta -= 1.0f;
		rotationMatrix = glm::rotate(glm::mat4(1.0f), theta * 3.14159f / 180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		mv = rotationMatrix * viewMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.5f, -6.0f));
		GL_CALL(glUniformMatrix4fv(mvLoc, 1, false, glm::value_ptr(mv)));
	}

	glfwTerminate();
}

//Constructor
Geodash3::Engine::Engine()
{
	//When the window gets resized, do this
	auto onWinResizeFunc = [](GLFWwindow *win, int newWidth, int newHeight)
	{
		glViewport(0, 0, newWidth, newHeight);	
	};

	//Initialize everything
	Geodash3::init(this->gameWindow, "Geodash 3D", onWinResizeFunc);
}

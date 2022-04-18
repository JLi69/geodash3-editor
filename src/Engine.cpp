#include "Engine.h"

//Main loop
void Geodash3::Engine::Run()
{
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

	GL_CALL(glUniform4f(loc, 0.0f, 1.0f, 0.0f, 1.0f));

	while(!glfwWindowShouldClose(gameWindow))
	{
		this->Display();	
	}

	glfwTerminate();
}

//Constructor
Geodash3::Engine::Engine()
{
	//When the window changes size, do this
	auto onWinResize = [](GLFWwindow* win, int newWidth, int newHeight)
	{
		//perspectiveMat = glm::perspective(FOV, (float)newHeight / (float)newWidth, 0.1f, 1000.0f);
		glViewport(0, 0, newWidth, newHeight);
	};

	//Initialize everything
	Geodash3::init(gameWindow, "Geodash 3D", onWinResize);

	
}

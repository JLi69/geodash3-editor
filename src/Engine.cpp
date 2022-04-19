#include "Engine.h"

//Main loop
void Geodash3::Engine::Run()
{		
	GL_CALL(m_cube.Enable());

	GL_CALL(glUseProgram(m_basic3D.GetId()));
	GL_CALL(int loc = m_basic3D.GetUniformLocation("u_Color"));
	GL_CALL(int pLoc = m_basic3D.GetUniformLocation("u_PerspectiveMat"));
	GL_CALL(int mvLoc = m_basic3D.GetUniformLocation("u_ModelViewMat"));

	GL_CALL(glUniform4f(loc, 0.0f, 1.0f, 0.0f, 1.0f));
	GL_CALL(glUniformMatrix4fv(pLoc, 1, false, glm::value_ptr(m_perspectiveMat)));
	
	glm::mat4 mv = m_rotationMatrix * m_viewMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -3.0f, -6.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(4.0f, 1.0f, 1000.0f));

	GL_CALL(glUniformMatrix4fv(mvLoc, 1, false, glm::value_ptr(mv)));

	//Set the background color of the window
	GL_CALL(glClearColor(0.0f, 0.8f, 1.0f, 1.0f));
	//Enable the depth test
	GL_CALL(glEnable(GL_DEPTH_TEST));
	GL_CALL(glDepthFunc(GL_LEQUAL));

	while(!glfwWindowShouldClose(m_gameWindow))
	{
		this->m_Display();
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
	Geodash3::init(this->m_gameWindow, "Geodash 3D", onWinResizeFunc);

	//Set up the vertex buffers
	GL_CALL(m_cube.GenBuffer());
	GL_CALL(m_cube.Data(&Geodash3::cubeVerts[0], sizeof(Geodash3::cubeVerts), 3));

	//Set up the shaders
	m_basic3D.CreateShader("res/shaders/vert-3d.glsl", "res/shaders/basic-frag.glsl");
}

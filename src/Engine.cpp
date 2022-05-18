#include "Engine.h"
#include <chrono>
#include <iostream>
#include <fstream>

//Main loop
void Geodash3::Engine::Run()
{
	//Set the background color of the window
	GL_CALL(glClearColor(0.0f, 0.8f, 1.0f, 1.0f));
	//Enable the depth test
	GL_CALL(glEnable(GL_DEPTH_TEST));
	GL_CALL(glDepthFunc(GL_LEQUAL));
	GL_CALL(glEnable(GL_CULL_FACE));

	float avgFPS = 0.0f, //Average frames per second 
		  frameCount = 0.0f; //Number of frames passed

	while(!glfwWindowShouldClose(m_gameWindow))
	{
		//Begin of frame
		std::chrono::time_point<std::chrono::system_clock> begin = std::chrono::system_clock::now();
		this->m_Display();
		this->m_Update();
		//Output frames per second
		std::cout << "Frames Per Second: " << 1.0f / this->m_secondsToDrawFrame << '\n';
		//End of frame
		std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
		//Calculate number of seconds to draw the frame
		std::chrono::duration<float> timePassed = end - begin;
		this->m_secondsToDrawFrame = timePassed.count();
		
		//Calculate the average FPS
		frameCount++;
		if(frameCount != 1.0f)
			avgFPS *= ((frameCount - 1.0f) / (frameCount));
		avgFPS += (1.0f / this->m_secondsToDrawFrame) / frameCount;
	}

	//Output the average FPS in the game
	std::cout << "-----------------------------------\n";
	std::cout << "Average Frames Per Second: " << avgFPS << '\n';

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
	Geodash3::init(this->m_gameWindow, "Geodash 3D Level Editor", onWinResizeFunc);	

	//Set up the vertex buffers
	//Cube	
	GL_CALL(m_cube.GenBuffer());
	GL_CALL(m_cube.Data(&Geodash3::cubeVerts[0], sizeof(Geodash3::cubeVerts), 3));
	//Pyramid
	GL_CALL(m_pyramid.GenBuffer());
	GL_CALL(m_pyramid.Data(&Geodash3::pyramidVerts[0], sizeof(Geodash3::pyramidVerts), 3));

	//Set up the shaders
	GL_CALL(m_basicPyramid3D.CreateShader("res/shaders/vert-3d.glsl", "res/shaders/pyramid-frag.glsl"));
	GL_CALL(m_basic3D.CreateShader("res/shaders/vert-3d.glsl", "res/shaders/basic-frag.glsl"));
	GL_CALL(m_white.CreateShader("res/shaders/vert-3d.glsl", "res/shaders/white.glsl"));

	//Set up key input
	glfwSetWindowUserPointer(this->m_gameWindow, this);
	auto keyInputFunc = [](GLFWwindow* win, int key, int scancode, int action, int mods)
	{
		static_cast<Engine*>(glfwGetWindowUserPointer(win))->m_HandleKeyInput(win, key, scancode, action, mods);
	};
	glfwSetKeyCallback(m_gameWindow, keyInputFunc);

	//Set up the camera
	this->m_camera.position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_camera.movement = glm::vec3(0.0f, 0.0f, 0.0f);

	//Hide cursor
	glfwSetInputMode(this->m_gameWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwGetCursorPos(this->m_gameWindow, &this->m_mouseX, &this->m_mouseY);

	//TEST - DELETE LATER
	this->m_level.blocks.push_back(Geodash3::Block(glm::vec3(-0.75f, -1.75f, -4.0f)));
}

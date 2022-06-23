#include "Engine.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

//Main loop
void Geodash3::Engine::Run()
{
	//Set the background color of the window
	GL_CALL(glClearColor(0.0f, 0.8f, 1.0f, 1.0f));
	//Enable the depth test
	GL_CALL(glEnable(GL_DEPTH_TEST));
	GL_CALL(glDepthFunc(GL_LEQUAL));
	GL_CALL(glEnable(GL_CULL_FACE));

	GL_CALL(glEnable(GL_BLEND));
	GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	float avgFPS = 0.0f, //Average frames per second 
		  frameCount = 0.0f; //Number of frames passed

	while(!glfwWindowShouldClose(m_gameWindow))
	{
		//Begin of frame
		std::chrono::time_point<std::chrono::system_clock> begin = std::chrono::system_clock::now();
		this->m_Display();
		this->m_Update();
		//Output frames per second
		//std::cout << "Frames Per Second: " << 1.0f / this->m_secondsToDrawFrame << '\n';
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
		//Preserve the aspect ratio
		if((float)newWidth < (float)newHeight * 1920.0f / 1080.0f)
		{			
			GL_CALL(glViewport(0, newHeight / 2 - int(float(newWidth) * 1080.0f / 1920.0f * 0.5f), newWidth, int(float(newWidth) * 1080.0f / 1920.0f)));
		}	
		else
		{	
			GL_CALL(glViewport(newWidth / 2 - int(float(newHeight) * 1920.0f / 1080.0f * 0.5f), 0, int(float(newHeight) * 1920.0f / 1080.0f), newHeight));	
		}

		//Fill up whole screen if maximized
		if(glfwGetWindowAttrib(win, GLFW_MAXIMIZED))
		{
			GL_CALL(glViewport(0, 0, newWidth, newHeight));
		}	
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
	//Rectangle
	GL_CALL(m_rect.GenBuffer());
	GL_CALL(m_rect.Data(&Geodash3::rect[0], sizeof(Geodash3::rect), 3));

	//Set up the shaders
	GL_CALL(m_basicPyramid3D.CreateShader("res/shaders/vert-3d.glsl", "res/shaders/pyramid-frag.glsl"));
	GL_CALL(m_basic3D.CreateShader("res/shaders/vert-3d.glsl", "res/shaders/basic-frag.glsl"));
	GL_CALL(m_white.CreateShader("res/shaders/vert-3d.glsl", "res/shaders/white.glsl"));
	GL_CALL(m_button.CreateShader("res/shaders/vert-3d.glsl", "res/shaders/button-frag.glsl"));
	
	//Set up the textures
	GL_CALL(m_ground = TextureObj("res/textures/ground.png"));
	GL_CALL(m_blocks[0] = TextureObj("res/textures/block1.png"));
	GL_CALL(m_blocks[1] = TextureObj("res/textures/block2.png"));	
	GL_CALL(m_blocks[2] = TextureObj("res/textures/block3.png"));	
	GL_CALL(m_spike = TextureObj("res/textures/spike.png"));
	GL_CALL(m_crosshair = TextureObj("res/textures/crosshair.png"));
	GL_CALL(m_pauseScreen = TextureObj("res/textures/pause.png"));
	GL_CALL(m_helpScreen = TextureObj("res/textures/geodash3-editor-credits.png"));

	//Set up the texture coordinates
	//Cube texture coordinates	
	GL_CALL(m_cubeCoords.GenBuffer());
	GL_CALL(m_cubeCoords.Data(&Geodash3::texCubeCoords[0], sizeof(Geodash3::texCubeCoords), 2));
	//Cube texture coordinates	
	GL_CALL(m_cubeCoordsTop.GenBuffer());
	GL_CALL(m_cubeCoordsTop.Data(&Geodash3::texCubeCoordsTop[0], sizeof(Geodash3::texCubeCoordsTop), 2));	
	//Pyramid texture coordinates	
	GL_CALL(m_pyrCoords.GenBuffer());
	GL_CALL(m_pyrCoords.Data(&Geodash3::texPyrCoords[0], sizeof(Geodash3::texPyrCoords), 2));
	//Rectangle texture coordinates
	GL_CALL(m_rectCoords.GenBuffer());
	GL_CALL(m_rectCoords.Data(&Geodash3::texRectCoords[0], sizeof(Geodash3::texRectCoords), 2));

	//Set up the buttons
	//Save button
	this->m_saveButton = Geodash3::Button([this]() { this->Write(); }, glm::vec2(0.0f, -0.005f), glm::vec2(0.15f * 0.11f, 0.06f * 0.11f));
	GL_CALL(this->m_saveButton.SetButtonTex("res/textures/savebutton.png"));
	//Save & quit button	
	this->m_saveQuitButton = Geodash3::Button([this]() { this->Write(); glfwTerminate(); exit(0); }, glm::vec2(0.0f, -0.02f), glm::vec2(0.15f * 0.11f, 0.06f * 0.11f));
	GL_CALL(this->m_saveQuitButton.SetButtonTex("res/textures/save-and-quitbutton.png"));	
	//Button to pull up the help screen
	
	//Display the help function
	this->m_helpButton = Geodash3::Button([this](){ this->m_help = true; }, glm::vec2(0.0f, -0.035f), glm::vec2(0.15f * 0.11f, 0.06f * 0.11f));
	GL_CALL(this->m_helpButton.SetButtonTex("res/textures/helpbutton.png"));

	//Set up the user input
	//Set up key input
	glfwSetWindowUserPointer(this->m_gameWindow, this);
	auto keyInputFunc = [](GLFWwindow* win, int key, int scancode, int action, int mods)
	{
		static_cast<Engine*>(glfwGetWindowUserPointer(win))->m_HandleKeyInput(win, key, scancode, action, mods);
	};
	glfwSetKeyCallback(m_gameWindow, keyInputFunc);
	//Set up mouse input
	auto mouseInputFunc = [](GLFWwindow* win, int button, int action, int mods)
	{
		static_cast<Engine*>(glfwGetWindowUserPointer(win))->m_HandleMouseInput(win, button, action, mods);
	};
	glfwSetMouseButtonCallback(this->m_gameWindow, mouseInputFunc);
	//Set up scroll input
	auto scrollInputFunc = [](GLFWwindow* win, double xoffset, double yoffset)
	{
		static_cast<Engine*>(glfwGetWindowUserPointer(win))->m_HandleScrollInput(win, xoffset, yoffset);	
	};
	glfwSetScrollCallback(this->m_gameWindow, scrollInputFunc);

	//Set up the camera
	this->m_camera.position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_camera.movement = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_camera.rotation = glm::vec3(0.0f, 0.0f, 0.0f);

	//Hide cursor
	glfwSetCursorPos(this->m_gameWindow, 0.0f, 0.0f);
	glfwGetCursorPos(this->m_gameWindow, &this->m_mouseX, &this->m_mouseY);
	glfwSetInputMode(this->m_gameWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//Generate a random path for the file
	std::stringstream randPath;	
	srand(time(NULL)); //Generate seed
	randPath << "custom-";	
	for(int i = 0; i < 16; i++)
		randPath << (char)(rand() % ((int)('z' - 'a') + 1) + (int)'a');
	randPath << ".lvl";

	this->m_path = randPath.str();
	
	//test
	std::cout << randPath.str() << '\n';
}

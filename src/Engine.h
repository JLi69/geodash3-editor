#define INCLUDE_GLAD
#include <glad/glad.h>

#include "Init/init.h"
#include "GL-Utils/GetOpenGLError.h"
#include "GL-Utils/Shader.h"
#include "GL-Utils/VertexBufferObj.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GameObject/Player.h"
#include "Level/level.h"

#include <vector>

//Field of vision of the camera = 60 degrees
#define FOV 55.0f

namespace Geodash3
{
	class Engine
	{
		//Use this matrix to convert 3D coordinates into 2D
		glm::mat4 m_perspectiveMat = glm::perspective(FOV * 3.14159f / 180.0f, 1920.0f / 1080.0f, 0.1f, 1000.0f);
		//Use this matrix to translate the models
		//to the camera position
		glm::mat4 m_viewMatrix = glm::mat4(1.0f);
		//Use this matrix to rotate the models
		//to the camera rotation
		glm::mat4 m_rotationMatrix = glm::rotate(glm::mat4(1.0f), 0.0f * 3.14159f / 180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		//Preallocated model view matrix
		glm::mat4 m_modelViewMat;

		//Game window
		GLFWwindow *m_gameWindow;

		//Vertex buffers
		VertexBufferObj m_cube = VertexBufferObj(), //Cube object
						m_pyramid = VertexBufferObj(); //Pyramid Object
		//Shaders
		Shader m_basic3D, //Basic cube shader
			   m_basicPyramid3D; //Basic pyramid shader

		//Game objects
		//Player object
		Geodash3::Player m_playerCube = Geodash3::Player(glm::vec3(0.0f, -1.8f, -4.5f));
		//Level
		int m_currentLevel = 0;
		std::vector<Geodash3::Level> m_levels; //All the levels
		std::vector<Geodash3::Level> m_resetLevels; //When you want to reset a level,
													//set it equal to the corresponding level
													//in this vector

		//Number of seconds to draw the frame
		float m_secondsToDrawFrame = 1.0f;

		//Handle key input
		void m_HandleKeyInput(GLFWwindow* win, int key, int scancode, int action, int mods);

		//Render game objects onto the screen
		void m_Display();
		//Update the game objects
		void m_Update();
	public:
		//Run the main game loop
		void Run();

		//Constructor
		Engine();
	};
}

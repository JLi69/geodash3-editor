#define INCLUDE_GLAD
#include <glad/glad.h>

#include "Init/init.h"
#include "GL-Utils/GetOpenGLError.h"
#include "GL-Utils/Shader.h"
#include "GL-Utils/VertexBufferObj.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Level/level.h"

#include <vector>

//Field of vision of the camera = 60 degrees
#define FOV 55.0f

namespace Geodash3
{
	enum class Mode
	{
		NORMAL,
		EDIT,
		DESTROY
	};

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

		Geodash3::Mode m_editMode = Geodash3::Mode::NORMAL;
		//Camera
		Geodash3::GameObject m_camera;
		float m_cameraRotationSpeed = 0.0f,
			  m_cameraPitchSpeed = 0.0f;	
		//Mouse position
		double m_mouseX, m_mouseY;
		//Highlighted cube
		glm::vec3 highlighted;

		//Game window
		GLFWwindow *m_gameWindow;

		//Vertex buffers
		VertexBufferObj m_cube = VertexBufferObj(), //Cube object
						m_pyramid = VertexBufferObj(); //Pyramid Object
		//Shaders
		Shader m_basic3D, //Basic cube shader
			   m_basicPyramid3D, //Basic pyramid shader
			   m_white; //Just color a model white

		//Game objects
		//Level
		int m_currentLevel = 0;
		Geodash3::Level m_level; //Level being edited

		//Number of seconds to draw the frame
		float m_secondsToDrawFrame = 1.0f;

		//Handle key input
		void m_HandleKeyInput(GLFWwindow* win, int key, int scancode, int action, int mods);
		
		//Handle mouse input
		void m_HandleMouseInput(GLFWwindow* win, int button, int action, int mods);

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

#define INCLUDE_GLAD
#include <glad/glad.h>

#include "Init/init.h"
#include "GL-Utils/GetOpenGLError.h"
#include "GL-Utils/Shader.h"
#include "GL-Utils/VertexBufferObj.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

//Field of vision of the camera = 60 degrees
#define FOV 60.0f

namespace Geodash3
{
	class Engine
	{
		//Use this matrix to convert 3D coordinates into 2D
		glm::mat4 perspectiveMat = glm::perspective(FOV, 1920.0f / 1080.0f, 0.1f, 1000.0f);

		//Use this matrix to translate the models
		//to the camera position
		glm::mat4 viewMatrix = glm::mat4(1.0f);
		//Use this matrix to rotate the models
		//to the camera rotation
		glm::mat4 rotationMatrix = glm::mat4(1.0f);

		//Game window
		GLFWwindow *gameWindow;

		//Render game objects onto the screen
		void Display();
	public:
		//Run the main game loop
		void Run();

		//Constructor
		Engine();
	};
}

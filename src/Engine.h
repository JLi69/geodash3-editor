#define INCLUDE_GLAD
#include <glad/glad.h>

#include "GL-Utils/GetOpenGLError.h"
#include "GL-Utils/Shader.h"
#include "GL-Utils/VertexBufferObj.h"
#include "GL-Utils/Texture-Utils/TextureObj.h"
#include "GL-Utils/Texture-Utils/TextureCoords.h"
#include "Button/Button.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Level/level.h"

#include <vector>

//Field of vision of the camera = 60 degrees
#define FOV 55.0f

//Block types
#define BLOCK1 0
#define BLOCK2 1
#define BLOCK3 2
#define BLOCK4 3
#define SPIKE 4

namespace Geodash3
{
	enum class Mode
	{
		NORMAL,
		EDIT	
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
		//Current edit mode
		Geodash3::Mode m_editMode = Geodash3::Mode::NORMAL;
		//Camera
		Geodash3::GameObject m_camera;
		float m_cameraRotationSpeed = 0.0f,
			  m_cameraPitchSpeed = 0.0f;	
		//Mouse position
		double m_mouseX = 0.0f, m_mouseY = 0.0f;
		//Highlighted cube
		glm::vec3 m_highlighted;

		//Game window
		GLFWwindow *m_gameWindow;

		//Buttons
		Geodash3::Button m_helpButton,
						 m_saveButton,
						 m_saveQuitButton;

		//Vertex buffers
		VertexBufferObj m_cube = VertexBufferObj(), //Cube object
						m_pyramid = VertexBufferObj(), //Pyramid Object
						m_rect = VertexBufferObj(); //Rectangle object 	
		//Textures
		TextureObj m_ground, 
				   m_blocks[4],
				   m_spike,
				   m_crosshair,
				   m_pauseScreen,
				   m_helpScreen;
		//Texture coordinates
		TextureCoords m_cubeCoords,
					  m_cubeCoordsTop,
					  m_pyrCoords,
					  m_rectCoords;	
		//Shaders
		Shader m_basic3D, //Basic cube shader
			   m_basicPyramid3D, //Basic pyramid shader
			   m_white, //Just color a model white
			   m_button; //Button shader

		//Game objects
		//Level	
		Geodash3::Level m_level; //Level being edited
	
		float m_secondsToDrawFrame = 1.0f, //Number of seconds to draw the frame
			  m_previewRotation = 0.0f; //Rotation of a preview block
		//Editor is paused
		bool m_paused = false, 
			 m_help = false; //On help screen

		//Handle key input
		void m_HandleKeyInput(GLFWwindow* win, int key, int scancode, int action, int mods);	
		//Handle mouse input	
		//Store which mouse button is currently being held
		std::map<int, bool> mouseHold;	
		void m_HandleMouseInput(GLFWwindow* win, int button, int action, int mods);
		//Handle mouse scroll
		int m_currentBlockType = BLOCK1;
		void m_HandleScrollInput(GLFWwindow* win, double xoffset, double yoffset);
		//Handle window resizing
		void m_OnWindowResize(GLFWwindow *win, int newWidth, int newHeight);	

		//Save and open files
		std::string m_path; //Path to the save file

		//Render game objects onto the screen
		void m_Display();
		//Update the game objects
		void m_Update();
	public:
		//Run the main game loop
		void Run();

		bool Read(std::string path); //Read from a save file
									 //returns true if successful,
									 //false if otherwise
		void Write(); //Save level to file

		//Constructor
		Engine();
	};
}

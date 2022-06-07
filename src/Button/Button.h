#ifndef TEXTUREOBJ_INCLUDE
#include "../GL-Utils/Texture-Utils/TextureObj.h"
#endif
#include <functional>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <GLFW/glfw3.h>
#include <string>

namespace Geodash3
{
	class Button
	{
		//Button texture
		TextureObj m_buttonTex;
	
		//Function to activate when the button is clicked
		std::function<void()> m_onClick;

		//Dimensions of the button
		glm::vec2 m_dimensions;
		//Position of the button
		glm::vec2 m_position; 
	
	public:
		//Run the onclick function
		void Click();

		//Check if the button is being hovered over
		bool MouseHovering(GLFWwindow *win, double mouseX, double mouseY);	

		//Set the button texture
		void SetButtonTex(std::string texPath);
		//Activate the button texture
		void ActivateButtonTex();
	
		//Set the model view matrix for the position
		//and scale of the button
		void SetModelViewMat(glm::mat4 &modelViewMat);
	
		//Constructor
		Button(std::function<void()> clickFunc, glm::vec2 position, glm::vec2 dimensions);
		//Default constructor
		Button();
	};
}

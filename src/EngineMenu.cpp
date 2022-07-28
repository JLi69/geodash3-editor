#include "Engine.h"
#include <fstream>
#include <iostream>

void Geodash3::Engine::Menu()
{	
	//Get the list of paths to the file levels
	std::ifstream pathListFile("saves/path-list.txt");
	//close the file if the file does not exist
	if(!pathListFile.is_open())
	{	
		std::cout << "Failed to open path list file!\n";	
		pathListFile.close();
	}
	//Read the list
	m_levelPaths.push_back(m_path);
	std::string path;
	while(std::getline(pathListFile, path))
		m_levelPaths.push_back(path);	
	pathListFile.close();

	//for debug purposes, output file names
	//for(auto path : m_levelPaths) 
	//	std::cout << path << '\n';

	this->m_menu = true;	
	glfwSetInputMode(this->m_gameWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	//Set the background color of the window
	GL_CALL(glClearColor(0.0f, 0.8f, 1.0f, 1.0f));
	//Enable the depth test
	GL_CALL(glEnable(GL_DEPTH_TEST));
	GL_CALL(glDepthFunc(GL_LEQUAL));
	GL_CALL(glEnable(GL_CULL_FACE));

	GL_CALL(glEnable(GL_BLEND));
	GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	
	//Draw the menu screen	
	while(!glfwWindowShouldClose(this->m_gameWindow) && this->m_menu)
	{
		//Clear the screen	
		GL_CALL(glClear(GL_COLOR_BUFFER_BIT));				
		GL_CALL(glClear(GL_DEPTH_BUFFER_BIT));
		
		GL_CALL(m_cube.Enable());
		GL_CALL(m_cubeCoords.Enable());	
		GL_CALL(glUseProgram(m_basic3D.GetId()));	
		GL_CALL(glFrontFace(GL_CW));	
		GL_CALL(glUniformMatrix4fv(m_basic3D.GetUniformLocation("u_PerspectiveMat"), 1, false, glm::value_ptr(m_perspectiveMat)));

		//Draw the ground
		GL_CALL(m_ground.ActivateTexture(GL_TEXTURE0));
		m_modelViewMat = m_rotationMatrix *
						 m_viewMatrix * 
						 glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -3.0f, -6.0f) + glm::vec3(0.0f, 0.0f, 0.0f)) * 
						 glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1000.0f));
		GL_CALL(glUniformMatrix4fv(m_basic3D.GetUniformLocation("u_ModelViewMat"), 1, false, glm::value_ptr(m_modelViewMat)));	
		GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 36));	

		//Draw the level
		//Display the block
		GL_CALL(this->m_cubeCoordsTop.Enable());
		static short int s_currentBlockType = -1;
		for(auto block : this->m_level.blocks)
		{
			if((block.position.x + this->m_camera.position.x) * (block.position.x + this->m_camera.position.x) +
				(block.position.y + this->m_camera.position.y) * (block.position.y + this->m_camera.position.y) +
				(block.position.z + this->m_camera.position.z) * (block.position.z + this->m_camera.position.z) > 64.0f * 64.0f)
				continue;	

			//Don't change the texture of the previous texture was different
			if(block.blockType != s_currentBlockType)
			{
				s_currentBlockType = block.blockType;
				GL_CALL(m_blocks[block.blockType].ActivateTexture(GL_TEXTURE0));
			}	
	
			m_modelViewMat = m_rotationMatrix *	
							m_viewMatrix * 
							glm::translate(glm::mat4(1.0f), block.position + glm::vec3(0.0f, 0.0f, 0.0f)) *
							glm::scale(glm::mat4(1.0f), block.dimensions) *
							glm::rotate(glm::mat4(1.0f), block.rotation.z, glm::vec3(0.0f, 0.0f, 1.0f)) *
							glm::rotate(glm::mat4(1.0f), block.rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)) *
							glm::rotate(glm::mat4(1.0f), block.rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
			GL_CALL(glUniformMatrix4fv(m_basic3D.GetUniformLocation("u_ModelViewMat"), 1, false, glm::value_ptr(m_modelViewMat)));	
		
			GL_CALL(glUniform4f(m_basic3D.GetUniformLocation("u_Color"), 0.6f, 0.6f, 0.6f, 1.0f));
			GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 36));
		}
		s_currentBlockType = -1;

		//Display the spikes
		GL_CALL(m_pyrCoords.Enable());
		GL_CALL(m_spike.ActivateTexture(GL_TEXTURE0));
		GL_CALL(glFrontFace(GL_CCW));
		GL_CALL(this->m_pyramid.Enable());
		GL_CALL(glUseProgram(m_basicPyramid3D.GetId()));
		GL_CALL(glUniformMatrix4fv(m_basicPyramid3D.GetUniformLocation("u_PerspectiveMat"), 1, false, glm::value_ptr(this->m_perspectiveMat)));

		for(auto spike : this->m_level.spikes)
		{
			if((spike.position.x + this->m_camera.position.x) * (spike.position.x + this->m_camera.position.x) +
				(spike.position.y + this->m_camera.position.y) * (spike.position.y + this->m_camera.position.y) +
				(spike.position.z + this->m_camera.position.z) * (spike.position.z + this->m_camera.position.z) > 64.0f * 64.0f)
				continue;

			m_modelViewMat = m_rotationMatrix * 
							 m_viewMatrix *
							 glm::translate(glm::mat4(1.0f), spike.position + glm::vec3(0.0f, 0.0f, 0.0f)) *
							 glm::scale(glm::mat4(1.0f), spike.dimensions) *
							 glm::rotate(glm::mat4(1.0f), spike.rotation.z, glm::vec3(0.0f, 0.0f, 1.0f)) *
							 glm::rotate(glm::mat4(1.0f), spike.rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)) *
							 glm::rotate(glm::mat4(1.0f), spike.rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
			GL_CALL(glUniformMatrix4fv(m_basicPyramid3D.GetUniformLocation("u_ModelViewMat"), 1, false, glm::value_ptr(m_modelViewMat)));
			GL_CALL(glUniform4f(m_basicPyramid3D.GetUniformLocation("u_Color"), 1.0f, 0.0f, 0.0f, 1.0f));
			GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 18));
		}

		GL_CALL(glFrontFace(GL_CW));

		//Draw the buttons
		GL_CALL(m_rectCoords.Enable());
		GL_CALL(m_rect.Enable());
		GL_CALL(glUseProgram(m_button.GetId()));
		GL_CALL(glUniformMatrix4fv(m_button.GetUniformLocation("u_PerspectiveMat"), 1, false, glm::value_ptr(this->m_perspectiveMat)));
		//Edit button	
		GL_CALL(m_editButton.ActivateButtonTex());
		GL_CALL(m_editButton.SetModelViewMat(this->m_modelViewMat));
		GL_CALL(glUniformMatrix4fv(m_button.GetUniformLocation("u_ModelViewMat"), 1, false, glm::value_ptr(this->m_modelViewMat)));
		GL_CALL(glUniform1i(m_button.GetUniformLocation("u_hovering"), this->m_editButton.MouseHovering(this->m_gameWindow, this->m_mouseX, this->m_mouseY)));
		GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 6));
		//Prev/Next buttons
		GL_CALL(m_prevButton.ActivateButtonTex());
		GL_CALL(m_prevButton.SetModelViewMat(this->m_modelViewMat));
		GL_CALL(glUniformMatrix4fv(m_button.GetUniformLocation("u_ModelViewMat"), 1, false, glm::value_ptr(this->m_modelViewMat)));
		GL_CALL(glUniform1i(m_button.GetUniformLocation("u_hovering"), this->m_prevButton.MouseHovering(this->m_gameWindow, this->m_mouseX, this->m_mouseY)));
		GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 6));
		
		GL_CALL(m_nextButton.ActivateButtonTex());
		GL_CALL(m_nextButton.SetModelViewMat(this->m_modelViewMat));
		GL_CALL(glUniformMatrix4fv(m_button.GetUniformLocation("u_ModelViewMat"), 1, false, glm::value_ptr(this->m_modelViewMat)));
		GL_CALL(glUniform1i(m_button.GetUniformLocation("u_hovering"), this->m_nextButton.MouseHovering(this->m_gameWindow, this->m_mouseX, this->m_mouseY)));
		GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 6));

		glfwGetCursorPos(this->m_gameWindow, &this->m_mouseX, &this->m_mouseY);
		glfwSwapBuffers(this->m_gameWindow);
		glfwPollEvents();	
	}	

	//Hide the mouse
	glfwSetInputMode(this->m_gameWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

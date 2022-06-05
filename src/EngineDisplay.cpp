#include "Engine.h"

#include <iostream>

void Geodash3::Engine::m_Display()
{
	//Clear the depth buffer bit and the screen
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
	GL_CALL(glClear(GL_DEPTH_BUFFER_BIT));

	GL_CALL(m_cube.Enable());
	GL_CALL(glUseProgram(m_basic3D.GetId()));

	//Draw the ground
	GL_CALL(m_cubeCoords.Enable());
	GL_CALL(m_ground.ActivateTexture(GL_TEXTURE0));
	GL_CALL(glFrontFace(GL_CW));
	GL_CALL(glUniformMatrix4fv(m_basic3D.GetUniformLocation("u_PerspectiveMat"), 1, false, glm::value_ptr(m_perspectiveMat)));
	m_modelViewMat = m_rotationMatrix *
					 glm::rotate(glm::mat4(1.0f), -this->m_camera.rotation.x, glm::vec3(1.0f, 0.0f, 0.0f)) * 
					 glm::rotate(glm::mat4(1.0f), this->m_camera.rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)) *	
					 glm::translate(glm::mat4(1.0f), this->m_camera.position) *
					 m_viewMatrix * 
					 glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -3.0f, -6.0f)) * 
					 glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1000.0f));
	GL_CALL(glUniformMatrix4fv(m_basic3D.GetUniformLocation("u_ModelViewMat"), 1, false, glm::value_ptr(m_modelViewMat)));
	//[GROUND WILL BE TEXTURED] - DELETE LATER!!!
	GL_CALL(glUniform4f(m_basic3D.GetUniformLocation("u_Color"), 0.0f, 1.0f, 0.0f, 1.0f));
	GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 36));	

	//Display the block	
	for(auto block : this->m_level.blocks)
	{
		GL_CALL(m_blocks[block.blockType].ActivateTexture(GL_TEXTURE0));
		
		m_modelViewMat = m_rotationMatrix *
						 glm::rotate(glm::mat4(1.0f), -this->m_camera.rotation.x, glm::vec3(1.0f, 0.0f, 0.0f)) * 
						 glm::rotate(glm::mat4(1.0f), this->m_camera.rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)) * 
						 glm::translate(glm::mat4(1.0f), this->m_camera.position) *
						 m_viewMatrix * 
						 glm::translate(glm::mat4(1.0f), block.position) *
						 glm::scale(glm::mat4(1.0f), block.dimensions) *
						 glm::rotate(glm::mat4(1.0f), block.rotation.z, glm::vec3(0.0f, 0.0f, 1.0f)) *
						 glm::rotate(glm::mat4(1.0f), block.rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)) *
						 glm::rotate(glm::mat4(1.0f), block.rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		GL_CALL(glUniformMatrix4fv(m_basic3D.GetUniformLocation("u_ModelViewMat"), 1, false, glm::value_ptr(m_modelViewMat)));	
		
		GL_CALL(glUniform4f(m_basic3D.GetUniformLocation("u_Color"), 0.6f, 0.6f, 0.6f, 1.0f));
		GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 36));
	}

	//Display the spikes
	GL_CALL(m_pyrCoords.Enable());
	GL_CALL(m_spike.ActivateTexture(GL_TEXTURE0));
	GL_CALL(glFrontFace(GL_CCW));
	GL_CALL(this->m_pyramid.Enable());
	GL_CALL(glUseProgram(m_basicPyramid3D.GetId()));
	GL_CALL(glUniformMatrix4fv(m_basicPyramid3D.GetUniformLocation("u_PerspectiveMat"), 1, false, glm::value_ptr(this->m_perspectiveMat)));

	for(auto spike : this->m_level.spikes)
	{
		m_modelViewMat = m_rotationMatrix *
						 glm::rotate(glm::mat4(1.0f), -this->m_camera.rotation.x, glm::vec3(1.0f, 0.0f, 0.0f)) * 
						 glm::rotate(glm::mat4(1.0f), this->m_camera.rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)) * 
						 glm::translate(glm::mat4(1.0f), this->m_camera.position) *
						 m_viewMatrix *
						 glm::translate(glm::mat4(1.0f), spike.position) *
						 glm::scale(glm::mat4(1.0f), spike.dimensions) *
						 glm::rotate(glm::mat4(1.0f), spike.rotation.z, glm::vec3(0.0f, 0.0f, 1.0f)) *
						 glm::rotate(glm::mat4(1.0f), spike.rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)) *
						 glm::rotate(glm::mat4(1.0f), spike.rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		GL_CALL(glUniformMatrix4fv(m_basicPyramid3D.GetUniformLocation("u_ModelViewMat"), 1, false, glm::value_ptr(m_modelViewMat)));
		GL_CALL(glUniform4f(m_basicPyramid3D.GetUniformLocation("u_Color"), 1.0f, 0.0f, 0.0f, 1.0f));
		GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 18));
	}


	//Display the highlighted block
	if(this->m_editMode != Geodash3::Mode::NORMAL)
	{
		GL_CALL(glUseProgram(m_white.GetId()));	
		GL_CALL(glUniformMatrix4fv(m_white.GetUniformLocation("u_PerspectiveMat"), 1, false, glm::value_ptr(m_perspectiveMat)));	
		m_modelViewMat = m_rotationMatrix *
				   		 glm::rotate(glm::mat4(1.0f), -this->m_camera.rotation.x, glm::vec3(1.0f, 0.0f, 0.0f)) * 
				   		 glm::rotate(glm::mat4(1.0f), this->m_camera.rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)) * 
				   		 glm::translate(glm::mat4(1.0f), this->m_camera.position) *
				   		 glm::translate(glm::mat4(1.0f), -this->m_highlighted) *
				   		 m_viewMatrix *  
				  		 glm::scale(glm::mat4(1.0f), glm::vec3(0.25f, 0.25f, 0.25f));
		GL_CALL(glUniformMatrix4fv(m_white.GetUniformLocation("u_ModelViewMat"), 1, false, glm::value_ptr(m_modelViewMat)));		
		GL_CALL(glFrontFace(GL_CW));
		GL_CALL(this->m_cube.Enable());
		GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 36));	
	}

	//Display the preview block
	m_modelViewMat = glm::translate(glm::mat4(1.0f), glm::vec3(-0.085f, -0.045f, -0.12f)) *
					 glm::rotate(glm::mat4(1.0f), this->m_previewRotation, glm::vec3(0.0f, 1.0f, 0.0f)) *  
					 m_viewMatrix * 
				  	 glm::scale(glm::mat4(1.0f), glm::vec3(0.005f, 0.005f, 0.005f));
	
	if(this->m_currentBlockType != SPIKE)
	{
		GL_CALL(this->m_cubeCoords.Enable());
		GL_CALL(this->m_blocks[this->m_currentBlockType].ActivateTexture(GL_TEXTURE0));

		GL_CALL(glFrontFace(GL_CW));
		GL_CALL(this->m_cube.Enable());
		GL_CALL(glUseProgram(m_basic3D.GetId()));
		GL_CALL(glUniform4f(m_basic3D.GetUniformLocation("u_Color"), 0.6f, 0.6f, 0.6f, 1.0f));
		GL_CALL(glUniformMatrix4fv(m_basic3D.GetUniformLocation("u_ModelViewMat"), 1, false, glm::value_ptr(m_modelViewMat)));
		GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 36));
	}
	else if(this->m_currentBlockType == SPIKE)
	{
		GL_CALL(glFrontFace(GL_CCW));
		GL_CALL(this->m_pyramid.Enable());
		GL_CALL(glUseProgram(m_basicPyramid3D.GetId()));	
		GL_CALL(glUniform4f(m_basic3D.GetUniformLocation("u_Color"), 1.0f, 0.0f, 0.0f, 1.0f));	
		GL_CALL(glUniformMatrix4fv(m_basicPyramid3D.GetUniformLocation("u_ModelViewMat"), 1, false, glm::value_ptr(m_modelViewMat)));
		GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 18));
	}

	//Draw the crosshair
	GL_CALL(glFrontFace(GL_CW));
	GL_CALL(this->m_crosshair.ActivateTexture(GL_TEXTURE0));
	GL_CALL(glUseProgram(this->m_basic3D.GetId()));
	GL_CALL(this->m_rectCoords.Enable());
	m_modelViewMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.12f)) *  
					 glm::scale(glm::mat4(1.0f), glm::vec3(0.0015f, 0.0015f, 1.0f));
	GL_CALL(glUniformMatrix4fv(m_basic3D.GetUniformLocation("u_ModelViewMat"), 1, false, glm::value_ptr(m_modelViewMat)));
	GL_CALL(this->m_rect.Enable());
	GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 6));

	//GLFW stuff
	glfwSwapBuffers(m_gameWindow);
	glfwPollEvents();
}

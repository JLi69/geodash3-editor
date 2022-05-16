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
	GL_CALL(glFrontFace(GL_CW));
	GL_CALL(glUniformMatrix4fv(m_basic3D.GetUniformLocation("u_PerspectiveMat"), 1, false, glm::value_ptr(m_perspectiveMat)));
	m_modelViewMat = m_rotationMatrix * m_viewMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -3.0f, -6.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1000.0f));
	GL_CALL(glUniformMatrix4fv(m_basic3D.GetUniformLocation("u_ModelViewMat"), 1, false, glm::value_ptr(m_modelViewMat)));
	//[GROUND WILL BE TEXTURED] - DELETE LATER!!!
	GL_CALL(glUniform4f(m_basic3D.GetUniformLocation("u_Color"), 0.0f, 1.0f, 0.0f, 1.0f));
	GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 36));
	
	//Display the block	
	for(auto block : this->m_level.blocks)
	{
		m_modelViewMat = m_rotationMatrix * 
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
	GL_CALL(glFrontFace(GL_CCW));
	GL_CALL(this->m_pyramid.Enable());
	GL_CALL(glUseProgram(m_basicPyramid3D.GetId()));
	GL_CALL(glUniformMatrix4fv(m_basicPyramid3D.GetUniformLocation("u_PerspectiveMat"), 1, false, glm::value_ptr(this->m_perspectiveMat)));

	for(auto spike : this->m_level.spikes)
	{
		m_modelViewMat = m_rotationMatrix *
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

	//GLFW stuff
	glfwSwapBuffers(m_gameWindow);
	glfwPollEvents();
}

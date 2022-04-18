#Minimum version of cmake required to compile
cmake_minimum_required(VERSION 3.10)

#Name of project
project(geodash3)

#Create the executable
add_executable(
	${PROJECT_NAME} #Name of executable

	#Files to compile
	${PROJECT_SOURCE_DIR}/Main.cpp
	${PROJECT_SOURCE_DIR}/glad.c

	#OpenGL utilities
	${PROJECT_SOURCE_DIR}/src/GL-Utils/Shader.cpp
	${PROJECT_SOURCE_DIR}/src/GL-Utils/VertexBufferObj.cpp
	${PROJECT_SOURCE_DIR}/src/GL-Utils/GetOpenGLError.cpp

	#init
	${PROJECT_SOURCE_DIR}/src/Init/init.cpp

	#Engine
	${PROJECT_SOURCE_DIR}/src/Engine.cpp
	${PROJECT_SOURCE_DIR}/src/EngineDisplay.cpp
)

#Libraries to link with the project
target_link_libraries(${PROJECT_NAME} GL dl glfw SOIL) 

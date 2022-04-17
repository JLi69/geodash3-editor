#include "Shader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <glad/glad.h>

unsigned int Shader::GetId()
{
	return this->id;
}

int Shader::GetUniformLocation(std::string uniformName)
{
	return glGetUniformLocation(this->id, uniformName.c_str());	
}

void Shader::PrintShaderLog(unsigned int shader)
{
	int len, chWritten;
	char* msg;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
	//Houston, we've got a problem
	if(len > 0)
	{
		msg = new char[len];
		
		glGetShaderInfoLog(shader, len, &chWritten, &msg[0]);
		//Output the error message
		std::cout << "Shader info log: " << msg << '\n';

		delete msg;
	}
}

void Shader::PrintProgramLog(unsigned int program)
{
	int len, chWritten;
	char* msg;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
	//Something went wrong
	if(len > 0)
	{
		msg = new char[len];

		glGetShaderInfoLog(program, len, &chWritten, &msg[0]);
		//Ouptut the error message
		std::cout << "Program info log: " << msg << '\n';

		delete msg;
	}
}

bool Shader::ReadFile(std::string path, std::string &src)
{
	std::ifstream file(path);

	//Failed to open file
	if(!file.is_open())
	{
		std::cout << "Error: failed to open file: " << path << '\n';
		return false; //Failed to open file
	}

	std::stringstream contents; //Contents of the file
	std::string line; //Current line of the file
	while(std::getline(file, line))
		contents << line << '\n';	

	src = contents.str();

	file.close();
	return true; //Succeeded in opening the file
}

unsigned int Shader::CreateProgram(std::string &vert, std::string &frag)
{
	unsigned int programId;

	programId = glCreateProgram();
	
	unsigned int vertShader, fragShader;
	vertShader = glCreateShader(GL_VERTEX_SHADER);
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	//Pointers to the start of the source code
	const char *vertSrcBegin = vert.c_str();
	const char *fragSrcBegin = frag.c_str();

	//Get the source of the shaders
	glShaderSource(vertShader, 1, &vertSrcBegin, nullptr);
	glShaderSource(fragShader, 1, &fragSrcBegin, nullptr);

	//Compile the shaders
	//Compile the vertex shader
	glCompileShader(vertShader);
	//Check for any errors in the compilation of the vertex shader
	int vertCompileStatus;
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &vertCompileStatus);
	if(vertCompileStatus != 1)
	{
		std::cout << "Vertex shader failed to compile!\n";
		Shader::PrintShaderLog(vertShader);
	}
	//Compile the fragment shader 
	glCompileShader(fragShader);
	//Check for any errors in the compilation of the fragment shader
	int fragCompileStatus;
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &fragCompileStatus);
	if(fragCompileStatus != 1)
	{
		std::cout << "Fragment shader failed to compile!\n";
		Shader::PrintShaderLog(fragShader);
	}

	//Attach the shaders to the program
	glAttachShader(programId, vertShader);
	glAttachShader(programId, fragShader);

	//Link and validate the program
	glLinkProgram(programId);
	glValidateProgram(programId);

	//Output any linking errors
	int linkStatus;
	glGetProgramiv(programId, GL_LINK_STATUS, &linkStatus);
	if(linkStatus != 1)
	{
		std::cout << "Program failed to link!\n";
		Shader::PrintProgramLog(programId);
	}

	glDetachShader(programId, vertShader);
	glDetachShader(programId, fragShader);

	return programId;
}

Shader::Shader(std::string vertShaderPath, std::string fragShaderPath)
{
	std::string vertSrc, fragSrc;
	Shader::ReadFile(vertShaderPath, vertSrc);
	Shader::ReadFile(fragShaderPath, fragSrc);

	this->id = Shader::CreateProgram(vertSrc, fragSrc);
}

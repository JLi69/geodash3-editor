#include <string>

class Shader
{
	//Id of the shader program
	unsigned int id;

	//Print any errors for a shader
	static void PrintShaderLog(unsigned int shader);
	//Print any errors for a program
	static void PrintProgramLog(unsigned int program);
	
	//Read a shader src file
	//path = location of the shader source file
	//src = where to store the source code of the file
	//function has one return value: 
	// - true = sucessfully opened file
	// - false = failed to open file
	static bool ReadFile(std::string path, std::string &src);

	//Create a basic shader program
	//vert = vertex shader source code
	//frag = fragment shader source code
	static unsigned int CreateProgram(std::string &vert, std::string &frag);
public:
	//Get the id of the program
	unsigned int GetId();

	//Get the location of a uniform in the program
	int GetUniformLocation(std::string uniformName);

	//Constructor
	Shader(std::string vertShaderPath, std::string fragShaderPath);
};

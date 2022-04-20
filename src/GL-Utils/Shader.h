#include <string>
#include <map>

class Shader
{
	//Id of the shader program
	unsigned int m_id;

	//Store the uniforms of the shader in a map
	std::map<std::string, int> m_uniforms;

	//Print any errors for a shader
	static void m_PrintShaderLog(unsigned int shader);
	//Print any errors for a program
	static void m_PrintProgramLog(unsigned int program);
	
	//Read a shader src file
	//path = location of the shader source file
	//src = where to store the source code of the file
	//function has one return value: 
	// - true = sucessfully opened file
	// - false = failed to open file
	static bool m_ReadFile(std::string path, std::string &src);

	//Create a basic shader program
	//vert = vertex shader source code
	//frag = fragment shader source code
	static unsigned int m_CreateProgram(std::string &vert, std::string &frag);
public:
	//Get the id of the program
	unsigned int GetId();

	//Get the location of a uniform in the program
	int GetUniformLocation(std::string uniformName);

	//Create a shader
	void CreateShader(std::string vertShaderPath, std::string fragShaderPath);
};

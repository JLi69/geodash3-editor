#include "src/Engine.h"
#include <iostream>
#include <cstdlib>

int main(int argc, char *argv[])
{
	Geodash3::Engine gameEngine = Geodash3::Engine();

	switch(argc)
	{
	//No arguments
	case 1:
		gameEngine.Menu();	
		gameEngine.Run();
		break;
	//One argument: the name of the file that the program will
	//output the level contents into
	case 2:
		gameEngine.Read(argv[1]);
		gameEngine.Run();
		break;
	//Invalid argument count
	default:
		std::cout << "Invalid argument count!\n";
		exit(-1);
		break;
	}
}

#include <vector>
#include "../GameObject/Block.h"
#include "../GameObject/Spike.h"

#include <string>

namespace Geodash3
{
	struct Level
	{
		float levelEnd;
		std::vector<Geodash3::Block> blocks;
		std::vector<Geodash3::Spike> spikes;
	};

	//Load a level from a file
	Geodash3::Level LoadLevel(std::string levelFilePath, bool &success);
}

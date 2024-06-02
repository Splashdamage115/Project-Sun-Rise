#include "LevelLoader.h"
#include "DEBUG.h"

std::vector<int> LevelLoader::readFileToBuffer()
{
	std::ifstream input(".\\ASSETS\\DATA\\Map.std", std::ios::binary);

	if (input.good())
	{
		// copies all data into buffer
		std::string buffer(std::istreambuf_iterator<char>(input), {});

		std::vector<int> tileNum;

		std::string holder;
		for (size_t i = 0; i < buffer.size(); i++)
		{
			holder = "";
			if (buffer.at(i) == '0')
			{
				break;
			}
			while (buffer.at(i) != ' ')
			{
				holder += buffer.at(i);
				i++;
			}
			tileNum.push_back(std::stoi(holder));
		}

		for (size_t i = 0; i < tileNum.size(); i++)
		{
			DEBUG_MSG(tileNum.at(i));
		}
		input.close();
		return tileNum;
	}
	else
	{
		DEBUG_MSG("FAILED TO OPEN MAP.STD");
		exit(2);
	}
}

void LevelLoader::writeLevelToFile(std::vector<int> t_level)
{
	std::ofstream output(".\\ASSETS\\DATA\\Map.std", std::ios::binary);

	if (output.good())
	{
		for (auto i : t_level)
		{
			output << i << ' ';
		}
		output << '0';
		output.close();
	}
	else
	{
		DEBUG_MSG("FAILED TO WRITE TO MAP.STD");
		exit(2);
	}
}



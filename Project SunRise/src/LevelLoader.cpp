#include "LevelLoader.h"
#include "DEBUG.h"

template<typename T>void LevelLoader::skipLines(int t_amtToSkip, T& t_file)
{
	t_file.seekg(std::ios::beg);

	if (t_amtToSkip <= 0)
	{
		std::cout << "ERROR, LINE VALUE INCORRECT\n";

		t_file.close();
		exit(1);
	}
	for (unsigned int i = 0; i < t_amtToSkip - 1; i++)
	{
		t_file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	t_file.seekg(t_file.tellg());
}

std::vector<int> LevelLoader::readFileToBuffer(int t_lineToRead)
{
	std::ifstream input(".\\ASSETS\\DATA\\Map.std", std::ios::binary);

	skipLines(t_lineToRead, input);

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

		/*for (size_t i = 0; i < tileNum.size(); i++)
		{
			DEBUG_MSG(tileNum.at(i));
		}*/
		input.close();
		return tileNum;
	}
	else
	{
		DEBUG_MSG("FAILED TO OPEN MAP.STD");
		exit(2);
	}
}

void LevelLoader::writeLevelToFile(std::vector<int> t_level, int t_lineToWrite)
{
	std::fstream output(".\\ASSETS\\DATA\\Map.std", std::ios::in | std::ios::out);

	if (output.good())
	{
		skipLines(t_lineToWrite, output);
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

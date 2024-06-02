#ifndef LEVEL_LOADER_H
#define LEVEL_LOADER_H

#include <fstream>
#include <iterator>
#include <vector>
#include <string>

class LevelLoader
{
public:
	std::vector<int> readFileToBuffer();
	void writeLevelToFile(std::vector<int> t_level);
private:

};

#endif // !LEVEL_LOADER_H

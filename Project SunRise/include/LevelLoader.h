#ifndef LEVEL_LOADER_H
#define LEVEL_LOADER_H

#include <fstream>
#include <iterator>
#include <vector>
#include <string>

class LevelLoader
{
public:
	template<typename T>void skipLines(int t_amtToSkip, T& t_file);
	std::vector<int> readFileToBuffer(int t_lineToRead);
	void writeLevelToFile(std::vector<int> t_level, int t_lineToWrite);
private:

};

#endif // !LEVEL_LOADER_H

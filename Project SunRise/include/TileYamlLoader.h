#ifndef TILE_YAML_LOADER_H
#define TILE_YAML_LOADER_H

#include <vector>
#include <fstream>
#include <iostream>
#include "yaml-cpp\yaml.h"
#include "Globals.h"
#include "TileHolder.h"

class TileyamlLoader
{
public:
	static void loadSettings(std::string t_loadFileName, std::vector<TileType>& t_tiles);
};

#endif // !TILE_YAML_LOADER_H
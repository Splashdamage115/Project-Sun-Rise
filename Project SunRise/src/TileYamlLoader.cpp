#include "TileYamlLoader.h"
#include "DEBUG.h"

// read
void operator >> (const YAML::Node& t_node, std::vector<TileType>& t_tiles)
{
	for (unsigned i = 0; i < t_node.size(); ++i)
	{
		TileType newTile;
		sf::Texture newTileTexture;
		if (!newTileTexture.loadFromFile(t_node[i]["file"].as<std::string>()))
		{
			DEBUG_MSG("COULDNT LOAD TILE TEXTURE\n");
			exit(1);
		}
		newTile.tileTexture = newTileTexture;
		t_tiles.push_back(newTile);
	}
}


/// <summary>
/// @brief try to load the settings data
///    this can be used as a simple template for more yaml loading
/// </summary>
/// <param name="t_loadFileName">files name</param>
/// <param name="t_settings">settings data struct</param>
void TileyamlLoader::loadSettings(std::string t_loadFileName, std::vector<TileType>& t_tiles)
{
	std::string filename = ".\\ASSETS\\DATA\\" + t_loadFileName + ".yaml";

	try
	{
		YAML::Node baseNode = YAML::LoadFile(filename);
		if (baseNode.IsNull())
		{
			std::string message("File: " + filename + " not found");
			throw std::exception(message.c_str());
		}
		baseNode >> t_tiles;
	}
	catch (YAML::ParserException& e)
	{
		std::string message(e.what());
		message = "YAML Parser Error: " + message;
		throw std::exception(message.c_str());
	}
	catch (std::exception& e)
	{
		std::string message(e.what());
		message = "Unexpected Error: " + message;
		throw std::exception(message.c_str());
	}
}

#include "TileLookupTable.h"
#include "TileYamlLoader.h"

TileType& TileLookupTable::getNumber(int t_numToGet)
{
	return m_tiles.at(t_numToGet);
}

TileLookupTable::TileLookupTable()
{
	TileyamlLoader::loadSettings("TileSheet", m_tiles);
}

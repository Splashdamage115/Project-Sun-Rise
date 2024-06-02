#include "TileLookupTable.h"
#include "TileYamlLoader.h"

TileType& TileLookupTable::getNumber(int t_numToGet)
{
	if (t_numToGet > m_tiles.size() - 1)
		return m_tiles.at(0);
	return m_tiles.at(t_numToGet);
}

TileLookupTable::TileLookupTable()
{
	TileyamlLoader::loadSettings("TileSheet", m_tiles);
}

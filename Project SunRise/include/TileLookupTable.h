#ifndef TILE_LOOKUP_TABLE_CPP
#define TILE_LOOKUP_TABLE_CPP

#include <SFML/Graphics.hpp>
#include "TileHolder.h"

class TileLookupTable
{
public:
    // simple setup for singleton  pattern
    static TileLookupTable& getInstance()
    {
        static TileLookupTable instance;
        return instance;
    }

    // DELETE FUNCTIONS TO AVOID MORE INSTANCES
    TileLookupTable(TileLookupTable const&) = delete;
    void operator=(TileLookupTable const&) = delete;
    // !

    TileType& getNumber(int t_numToGet);

private:
	TileLookupTable(); // Constructor

    std::vector<TileType> m_tiles;
};

#endif // !TILE_LOOKUP_TABLE_CPP

#include "LevelMap.h"

/*
when making a map remdper:
0 = empty space, 1 = blocked/occupied space
*/

LevelMap::LevelMap(int map[MAP_HEIGHT][MAP_WIDTH])
{
	//Allocated memory for the level map
	m_map = new int* [MAP_HEIGHT];
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		m_map[i] = new int[MAP_WIDTH];
	}

	//populate the array
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		for (unsigned int j = 0; j < MAP_WIDTH; j++)
		{
			m_map[i][j] = map[i][j];
		}
	}
}

LevelMap::~LevelMap()
{
	//delete all elements of the array
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		delete[] m_map[i];
	}
	delete[]m_map;
}

int LevelMap::GetTileAt(unsigned int h, unsigned int w)
{
	if (h < MAP_HEIGHT && w < MAP_WIDTH)
	{
		return m_map[h][w];
	}
	return 0;
}

int LevelMap::ChangeTileAt(unsigned int row, unsigned int column, unsigned int new_value)
{
	m_map[row][column] = new_value;
	return true;
}

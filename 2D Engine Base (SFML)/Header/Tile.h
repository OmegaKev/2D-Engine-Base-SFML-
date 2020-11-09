#pragma once
#include <SFML/Graphics.hpp>
#include "TileSet.h"



// This class is designed to hold a pointer to a tile reference and any unique properties.
class Tile
{
private:
	TileReference* container;
	sf::Vertex* quad;
	//TODO: Object Attachment
public:
	Tile(TileSet &ts, int tile_index);
	Tile(TileReference& tile);
	TileReference& get();
	void setVertexPointer(sf::Vertex* quad);
};
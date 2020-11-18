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
	Tile(TileSet &ts, int tile_index, sf::Vertex *quad);
	Tile(TileReference& tile, sf::Vertex* quad);
	TileReference& get();
	void setVertexPointer(sf::Vertex* quad);
	sf::Vertex*& getVertexPointer();
	void updateFrame();
	std::string to_string() const;
};
#pragma once
#include <SFML/Graphics.hpp>
#include "TileSet.h"

// This class is designed to hold a pointer to a tile reference and any unique properties.
class Tile
{
private:
	TileReference* container;		// Container Tile
	sf::Vertex* quad;				// Pointer to Quad
	sf::Uint64 instance_value = -1;
	//TODO: Object Attachment
	void updateFrame();			// Update the frame if needed
public:
	Tile(TileSet &ts, int tile_index, sf::Vertex *quad);
	Tile(TileReference& tile, sf::Vertex* quad);
	TileReference& get();
	void setVertexPointer(sf::Vertex* quad);
	sf::Vertex*& getVertexPointer();
	std::string to_string() const;
};
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "TileReference.h"

class TileSet
{
private:
	sf::String tileset_name;
	sf::String file_location;
	sf::Vector2u tile_size;
	std::vector<TileReference> t_ref;
public:
	TileSet(sf::String name, sf::String file_location, sf::Vector2u tile_size);
	sf::String getName();
	sf::String getFileLocation();
	sf::Vector2u getTileSize();
	TileReference& getTile(int index);
	void addTile(TileReference* tile);
};
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
	std::vector<std::shared_ptr<TileReference>> t_ref;	// Holds a list of dynamically allocated tiles
	std::vector<std::shared_ptr<TileReference>> at_ref;	// Holds a list of dynamically allocated animation tiles
public:
	TileSet(sf::String name, sf::String file_location, sf::Vector2u tile_size);
	virtual ~TileSet() { };
	sf::String getName();
	sf::String getFileLocation();
	sf::Vector2u getTileSize();
	std::shared_ptr<TileReference>& getTile(int index);
	void addTile(TileReference* tile);
	void updateAnimatedTiles(const sf::Time &elapsed);
};
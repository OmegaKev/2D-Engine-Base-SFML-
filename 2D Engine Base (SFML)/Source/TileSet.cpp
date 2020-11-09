#include "TileSet.h"

TileSet::TileSet(sf::String name, sf::String file_location, sf::Vector2u tile_size)
{
	this->tileset_name = name;
	this->file_location = file_location;
	this->tile_size = tile_size;
}

// Returns the file location string
sf::String TileSet::getFileLocation()
{
	return this->file_location;
}

// Returns the name of the tileset
sf::String TileSet::getName()
{
	return this->tileset_name;
}

// Returns the tile size as an unsigned integer pair
sf::Vector2u TileSet::getTileSize()
{
	return this->tile_size;
}

// Returns a reference to the tile at the index
TileReference& TileSet::getTile(int index)
{
	return this->t_ref.at(index);
}

void TileSet::addTile(TileReference* tile)
{
	this->t_ref.push_back(*tile);
}
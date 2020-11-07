#include "Tile.h"

TileReference::TileReference(sf::String name, sf::Vector2i graphic_location)
{
	this->name = name;
	this->graphic_location = graphic_location;
}

sf::Vector2i TileReference::get()
{
	return this->graphic_location;
}
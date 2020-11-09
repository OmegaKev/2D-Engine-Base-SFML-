#include "TileReference.h"

TileReference::TileReference(sf::String name, sf::Vector2i graphic_location)
{
	this->name = name;
	this->graphic_location = graphic_location;
}

sf::String TileReference::getName()
{
	return this->name;
}

sf::Vector2i TileReference::get()
{
	return this->graphic_location;
}

std::string TileReference::to_string() const
{
	return std::string(this->name + " (" + std::to_string(this->graphic_location.x) + ", " + std::to_string(this->graphic_location.y) + ")");
}
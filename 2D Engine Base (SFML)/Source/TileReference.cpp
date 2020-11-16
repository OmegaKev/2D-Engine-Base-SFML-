#include "TileReference.h"

TileReference::TileReference(sf::String name, sf::Vector2i graphic_location, const sf::Vector2u& tile_size)
{
	this->name = name;
	this->graphic_location = graphic_location;
	this->texCoord.push_back(std::vector<sf::Vector2f>(4));
	this->setTexCoords(tile_size);
}

sf::String TileReference::getName() const
{
	return this->name;
}

sf::Vector2i TileReference::get() const
{
	return this->graphic_location;
}

std::string TileReference::to_string() const
{
	return std::string(this->name + " (" + std::to_string(this->graphic_location.x) + ", " + std::to_string(this->graphic_location.y) + ")");
}

void TileReference::setTexCoords(const int index, const sf::Vector2u &tile_size)
{
	// Map graphic coordinates to tu and tv
	int tu = this->graphic_location.x;
	int tv = this->graphic_location.y;

	// Set the texture coordinates for the 4 points of the quad
	this->texCoord[index].at(0) = sf::Vector2f(tu * tile_size.x, tv * tile_size.y);
	this->texCoord[index].at(1) = sf::Vector2f((tu + 1) * tile_size.x, tv * tile_size.y);
	this->texCoord[index].at(2) = sf::Vector2f((tu + 1) * tile_size.x, (tv + 1) * tile_size.y);
	this->texCoord[index].at(3) = sf::Vector2f(tu * tile_size.x, (tv + 1) * tile_size.y);
}

// setTexCoords only have 1 set of coordinates for the base class
void TileReference::setTexCoords(const sf::Vector2u& tile_size)
{
	this->setTexCoords(0, tile_size);
}

std::vector<sf::Vector2f>& TileReference::getTexCoords(const int index)
{
	return this->texCoord[index];
}

std::vector<sf::Vector2f>& TileReference::getTexCoords()
{
	return this->getTexCoords(0);
}
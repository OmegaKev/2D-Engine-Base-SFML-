#include "Tile.h"

Tile::Tile(TileSet &ts, int tile_index)
{
	this->container = &ts.getTile(tile_index);
}

Tile::Tile(TileReference& tile)
{
	this->container = &tile;
}

TileReference& Tile::get()
{
	return *this->container;
}

void Tile::setVertexPointer(sf::Vertex* quad)
{
	this->quad = quad;
}

std::string Tile::to_string() const
{
	return std::string("( " + std::to_string(this->quad->position.x) + ", " + std::to_string(this->quad->position.y) + "): ");
}
#include "Tile.h"

Tile::Tile(TileSet& ts, int tile_index, sf::Vertex* quad)
{
	Tile(*ts.getTile(tile_index), quad);
}

Tile::Tile(TileReference& tile, sf::Vertex *quad)
{
	this->container = &tile;
	this->setVertexPointer(quad);
}

TileReference& Tile::get()
{
	return *this->container;
}

void Tile::setVertexPointer(sf::Vertex* quad)
{
	this->quad = quad;
}

sf::Vertex *& Tile::getVertexPointer()
{
	return this->quad;
}

void Tile::updateFrame()
{
	this->quad->texCoords = this->container->getTexCoords().at(0);
}

std::string Tile::to_string() const
{
	return std::string("( " + std::to_string(this->quad->position.x) + ", " + std::to_string(this->quad->position.y) + "): ");
}
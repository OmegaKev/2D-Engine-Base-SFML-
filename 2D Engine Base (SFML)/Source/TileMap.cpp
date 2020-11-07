#include "TileMap.h"
#include <iostream>

TileMap::TileMap(sf::String texture_location, sf::Vector2u t_size, const int* map, sf::Vector2u m_size)
{
	// If we fail to load the texture, abort
	if (!m_tx.loadFromFile(texture_location))
	{
		this->t_size = sf::Vector2u(0, 0);
		this->m_size = sf::Vector2u(0, 0);
	}

	this->t_size = t_size;
	this->m_size = m_size;
	this->map = map;
}

void TileMap::addTile(TileReference *tile)
{
	this->t_ref.push_back(*tile);
}

bool TileMap::load()
{
	// If we failed to load the texture, abort
	if (m_tx.getNativeHandle() == 0)return false;

	// Set the vertex array to use Quads
	m_va.setPrimitiveType(sf::Quads);
	m_va.resize(m_size.x * m_size.y * 4);

	// Create our vertex array by iterating through the map
	for (int i = 0; i < m_size.x; ++i)
	{
		for (int j = 0; j < m_size.y; ++j)
		{
			int tile_index = map[i + j * m_size.x];

			// Grab the texture coordinates for the tile
			int tu = this->t_ref.at(tile_index).get().x;
			int tv = this->t_ref.at(tile_index).get().y;

			// Manipulate 1 quad at a time
			sf::Vertex * quad = &m_va[(i + j * m_size.x) * 4];
			
			setTexCoords(quad, tu, tv);

			// Set the position coordinates for the 4 points on the quad
			quad[0].position = sf::Vector2f(i * t_size.x, j * t_size.y);
			quad[1].position = sf::Vector2f((i + 1) * t_size.x, j * t_size.y);
			quad[2].position = sf::Vector2f((i + 1) * t_size.x, (j + 1) * t_size.y);
			quad[3].position = sf::Vector2f(i * t_size.x, (j + 1) * t_size.y);
		}
	}
	
	return true;
}

void TileMap::setTexCoords(sf::Vertex* quad, int tu, int tv)
{
	// Set the texture coordinates for the 4 points of the quad
	quad[0].texCoords = sf::Vector2f(tu * t_size.x, tv * t_size.y);
	quad[1].texCoords = sf::Vector2f((tu + 1) * t_size.x, tv * t_size.y);
	quad[2].texCoords = sf::Vector2f((tu + 1) * t_size.x, (tv + 1) * t_size.y);
	quad[3].texCoords = sf::Vector2f(tu * t_size.x, (tv + 1) * t_size.y);
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Apply transformations
	states.transform *= getTransform();

	// Apply the texture
	states.texture = &m_tx;

	// Draw the Vertex Array
	target.draw(m_va, states);
}

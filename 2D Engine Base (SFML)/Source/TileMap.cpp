#include "TileMap.h"
#include <iostream>

TileMap::TileMap(TileSet *ts, const int* map, sf::Vector2u m_size)
{
	// If we fail to load the texture, abort
	if (!m_tx.loadFromFile(ts->getFileLocation()))
	{
		this->m_size = sf::Vector2u(0, 0);
	}
	this->ts = ts;
	this->m_size = m_size;
	this->raw_map = map;
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
			int tile_index = raw_map[i + j * m_size.x];

			// Grab the texture coordinates for the tile
			int tu = this->ts->getTile(tile_index).get().x;
			int tv = this->ts->getTile(tile_index).get().y;

			// Manipulate 1 quad at a time
			sf::Vertex * quad = &m_va[(i + j * m_size.x) * 4];
			
			// Create the map and hold pointers to their data
			map.push_back(Tile(this->ts->getTile(tile_index)));
			map.back().setVertexPointer(quad);

			// Set Tex Coordinates and position of tiles
			setTexCoords(quad, tu, tv);
			setDefaultTilePosition(quad, i, j);
		}
	}
	
	return true;
}

void TileMap::setTexCoords(sf::Vertex* quad, const int &tu, const int &tv)
{
	// Set the texture coordinates for the 4 points of the quad
	quad[0].texCoords = sf::Vector2f(tu * ts->getTileSize().x, tv * ts->getTileSize().y);
	quad[1].texCoords = sf::Vector2f((tu + 1) * ts->getTileSize().x, tv * ts->getTileSize().y);
	quad[2].texCoords = sf::Vector2f((tu + 1) * ts->getTileSize().x, (tv + 1) * ts->getTileSize().y);
	quad[3].texCoords = sf::Vector2f(tu * ts->getTileSize().x, (tv + 1) * ts->getTileSize().y);
}

// Sets a vertex quad position based on the row and column of the map
void TileMap::setDefaultTilePosition(sf::Vertex* quad, const int& row, const int& col)
{
	// Set the position coordinates for the 4 points on the quad
	quad[0].position = sf::Vector2f(row * ts->getTileSize().x, col * ts->getTileSize().y);
	quad[1].position = sf::Vector2f((row + 1) * ts->getTileSize().x, col * ts->getTileSize().y);
	quad[2].position = sf::Vector2f((row + 1) * ts->getTileSize().x, (col + 1) * ts->getTileSize().y);
	quad[3].position = sf::Vector2f(row * ts->getTileSize().x, (col + 1) * ts->getTileSize().y);
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

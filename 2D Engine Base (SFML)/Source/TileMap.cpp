#include "TileMap.h"
#include <iostream>

// Declare Screen Size here for now
const sf::Vector2u TileMap::SCR_SIZE = sf::Vector2u(16, 16);

TileMap::TileMap(TileSet *ts, const int* map, sf::Vector2u m_size, bool map_repeat)
{
	// If we fail to load the texture, abort
	if (!m_tx.loadFromFile(ts->getFileLocation()))
	{
		this->m_size = sf::Vector2u(0, 0);
	}
	this->ts = ts;
	this->m_size = m_size;
	this->raw_map = map;
	this->repeat = map_repeat;
}

bool TileMap::load()
{
	// If we failed to load the texture, abort
	if (m_tx.getNativeHandle() == 0)return false;

	// Calculate the correct vertex size in case the map is smaller than the screen
	sf::Vector2u vert_size = sf::Vector2u(m_size.x, m_size.y);
	if (vert_size.x < SCR_SIZE.x)vert_size.x = SCR_SIZE.x;
	if (vert_size.y < SCR_SIZE.y)vert_size.y = SCR_SIZE.y;

	// Set the vertex array to use Quads
	m_va.setPrimitiveType(sf::Quads);
	m_va.resize(vert_size.x * vert_size.y * 4);

	// Create our vertex array by iterating through the map
	for (int i = 0; i < m_size.x || i < SCR_SIZE.x; ++i)
	{
		for (int j = 0; j < m_size.y || j < SCR_SIZE.y; ++j)
		{
			int tile_index = raw_map[(i % m_size.x) + (j % m_size.y) * m_size.x];
			TileReference *tile_ref = this->ts->getTile(tile_index).get();

			// Manipulate 1 quad at a time
			sf::Vertex * quad = &m_va[(i + j * m_size.x) * 4];

			// If repeat bool is off, replace repeated tile with blank tile
			if (!this->repeat && (i >= m_size.x || j >= m_size.y))
			{
				// TODO: Create unique blank tile
				tile_ref = this->ts->getTile(0).get();
				setQuadColor(quad, sf::Color::Transparent);
			}
			
			// Create the map and hold pointers to their data
			map.push_back(Tile(*tile_ref, quad));
			tile_ref->storeQuadReference(quad);

			// Set Tex Coordinates and position of tiles
			setQuadTexCoords(quad, *tile_ref);
			setQuadDefaultTilePosition(quad, i, j);
		}
	}
	
	return true;
}

void TileMap::setQuadTexCoords(sf::Vertex* quad, TileReference &t_ref)
{
	// Set the texture coordinates for the 4 points of the quad
	for (int i = 0; i < 4; i++)
		quad[i].texCoords = t_ref.getTexCoords()[i];
}

// Sets a vertex quad position based on the row and column of the map
void TileMap::setQuadDefaultTilePosition(sf::Vertex* quad, const int& row, const int& col)
{
	// Set the position coordinates for the 4 points on the quad
	quad[0].position = sf::Vector2f(row * ts->getTileSize().x, col * ts->getTileSize().y);
	quad[1].position = sf::Vector2f((row + 1) * ts->getTileSize().x, col * ts->getTileSize().y);
	quad[2].position = sf::Vector2f((row + 1) * ts->getTileSize().x, (col + 1) * ts->getTileSize().y);
	quad[3].position = sf::Vector2f(row * ts->getTileSize().x, (col + 1) * ts->getTileSize().y);
}

void TileMap::setQuadColor(sf::Vertex* quad, const sf::Color& color)
{
	// Set the texture coordinates for the 4 points of the quad
	for (int i = 0; i < 4; i++)
		quad[i].color = color;
}

sf::Uint32 TileMap::getTotalMapArea()
{
	return this->m_size.x * this->m_size.y;
}

TileSet* TileMap::getTileSet() const
{
	return this->ts;
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

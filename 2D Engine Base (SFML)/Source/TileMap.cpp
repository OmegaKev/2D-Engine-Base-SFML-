#include "TileMap.h"

bool TileMap::load(sf::String texture_location, sf::Vector2u t_size, const int* map, sf::Vector2u m_size)
{
	// If we fail to load the texture, abort
	if (!m_tx.loadFromFile(texture_location))return false;

	// Set the vertex array to use Quads
	m_va.setPrimitiveType(sf::Quads);
	m_va.resize(m_size.x * m_size.y * 4);

	// Create our vertex array by iterating through the map
	for (int i = 0; i < m_size.x; ++i)
	{
		for (int j = 0; j < m_size.y; ++j)
		{
			// TODO: Integrate Tile Class
			int tile = map[i + j * m_size.x];

			// Grab the texture coordinates for the tile
			int tu = tile % (m_tx.getSize().x / t_size.x);
			int tv = tile / (m_tx.getSize().x / t_size.x);

			// Manipulate 1 quad at a time
			sf::Vertex * quad = &m_va[(i + j * m_size.x) * 4];
			
			// Set the texture coordinates for the 4 points of the quad
			quad[0].texCoords = sf::Vector2f(tu * t_size.x, tv * t_size.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * t_size.x, tv * t_size.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * t_size.x, (tv + 1) * t_size.y);
			quad[3].texCoords = sf::Vector2f(tu * t_size.x, (tv + 1) * t_size.y);

			// Set the position coordinates for the 4 points on the quad
			quad[0].position = sf::Vector2f(i * t_size.x, j * t_size.y);
			quad[1].position = sf::Vector2f((i + 1) * t_size.x, j * t_size.y);
			quad[2].position = sf::Vector2f((i + 1) * t_size.x, (j + 1) * t_size.y);
			quad[3].position = sf::Vector2f(i * t_size.x, (j + 1) * t_size.y);
		}
	}
	
	return true;
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

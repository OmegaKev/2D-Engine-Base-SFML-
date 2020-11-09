#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Tile.h"
#include "TileSet.h"

class TileMap : public sf::Drawable, public sf::Transformable
{
private:
	sf::Texture m_tx;					// Vertex Array Texture
	sf::VertexArray m_va;				// Vertex Array Data
	const int* map;						// TEMP
	sf::Vector2u m_size;				// Size of TileMap
	TileSet *ts;						// Holds the tileset being used for this tilemap		
	bool repeat = false;				// Indicates whether the map will loop or display blank tiles past the array
	float scroll_ratio = 1.0;			// Controls how fast the tile map will scroll against movement
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setTexCoords(sf::Vertex* quad, int tu, int tv);
public:
	TileMap(TileSet *ts, const int* map, sf::Vector2u m_size);
	bool load();
};
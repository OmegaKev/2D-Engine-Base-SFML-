#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Tile.h"
#include "TileSet.h"

class TileMap : public sf::Drawable, public sf::Transformable
{
private:
	static const sf::Vector2u SCR_SIZE;
	sf::Texture m_tx;					// Vertex Array Texture
	sf::VertexArray m_va;				// Vertex Array Data
	const int* raw_map;					// Holds the array of tile by their value
	std::vector<Tile> map;				// Hold a vector array of Tiles
	sf::Vector2u m_size;				// Size of TileMap
	TileSet *ts;						// Holds the tileset being used for this tilemap		
	bool repeat = false;				// Indicates whether the map will loop or display blank tiles past the array
	float scroll_ratio = 1.0;			// Controls how fast the tile map will scroll against movement
	
	// Private Functions
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setQuadTexCoords(sf::Vertex* quad, TileReference &t_ref);
	void setQuadDefaultTilePosition(sf::Vertex* quad, const int &row, const int &col);
	void setQuadColor(sf::Vertex* quad, const sf::Color& color);
	sf::Uint32 getTotalMapArea();
public:
	TileMap(TileSet *ts, const int* map, sf::Vector2u m_size, bool map_repeat = false);
	bool load();
	TileSet* getTileSet() const;
};
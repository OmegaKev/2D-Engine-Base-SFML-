#pragma once
#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable
{
private:
	sf::Texture m_tx;			// Vertex Array Texture
	sf::VertexArray m_va;		// Vertex Array Data
	bool repeat = false;		// Indicates whether the map will loop or display blank tiles past the array
	float scroll_ratio = 1.0;	// Controls how fast the tile map will scroll against movement
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	bool load(sf::String texture_location, sf::Vector2u t_size, const int* map, sf::Vector2u m_size);
};
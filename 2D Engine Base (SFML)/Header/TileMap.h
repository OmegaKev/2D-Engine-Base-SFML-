#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Tile.h"
#include "TileSet.h"

class RawMap
{
private:
	sf::Vector2u size;			// Contains the actual size of the map data
	std::vector<int> map_data;	// Contains the map data
public:
	RawMap() {};
	virtual ~RawMap() {};
	RawMap(std::vector<int>& map, sf::Vector2u& size);
	sf::Vector2u getSize() const;
	std::vector<int>& getMapData();
	void setSize(const sf::Vector2u& size);
	void setMapData(const std::vector<int>& map_data);
};

class TileMap : public sf::Drawable, public sf::Transformable
{
private:
	static const sf::Vector2u SCR_SIZE;
	sf::Texture m_tx;					// Vertex Array Texture
	sf::VertexArray m_va;				// Vertex Array Data
	std::unique_ptr<RawMap> raw_map;	// RawMap contains the integer data of the map
	std::vector<Tile> map;				// Hold a vector array of Tiles
	sf::Vector2u m_size;				// Size of TileMap (Note: Exceeding raw map size will loopback on tilemap)
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
	TileMap(TileSet *ts, RawMap* raw_map, sf::Vector2u m_size, bool map_repeat = false);
	bool load();
	TileSet* getTileSet() const;
};
#pragma once
#include "TileMap.h"
#include <vector>

class GameMap : public sf::Drawable, public sf::Transformable
{
private:
	sf::String name = "Undefined Map";	// Name of Map
	TileMap* primary_layer;				// Pointer to primary layer (Usually 0 Layer)
	std::vector<TileMap> vec_layer;		// Holds all the Tilemap Layers
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	void addLayer(TileMap* tile_map);
	void setPrimaryLayer(TileMap &layer);
	void setMapName(sf::String name);
	bool load();
	sf::String getName();
	TileMap& getPrimaryLayer();
	TileMap& getLayerByIndex(int index);
};